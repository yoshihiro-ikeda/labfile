#include "BLGraph.hxx"

#include <vector>
#include <iostream>
// #include <cstring>
#include <time.h>

using namespace std;
using namespace SimulinkModel;
using namespace SimulinkModel::XSD;
using namespace Simulink;
using namespace Simulink::XML;

using namespace BLG;

#define FILENAME_LEN 1024
#define TMPFILENAME_LEN 64
#define MAX_HIER 100
#define TRUE	(1==1)
#define FALSE	(!TRUE)

#define W_OVERHEAD 15
#define BASE_RATE (1.0e-6)
#define CPU_MIPS (200.0e6)
#define PRECISION (1000000.0)	// unit of CPU utilization = 0.0001%

struct bltmp_alike {
    block_T::rate_optional* rate;  // rate (NULL)
    int atomic;  // pos of atomic subsystem included (-1)
};

struct bltmp_clst {
    int		level;	// hierarchy level, 0:blnode, >0:clst, -1:not used (may be merged)
    union {
	struct {	// case: level=0, correspond to block
    	    BLG::blnode_T 	*org;	// original blnode
	    struct bltmp_alike	alike;	// to get merge priority (atomic, rate, etc.)
	    // subsystem
	    struct bltmp_clst	*ss_parent;	// parent subsystem (NULL)
	    struct bltmp_clst	*ss_sibling;	// one of siblings in subsystem (NULL)
	    struct bltmp_clst	*ss_child;	// one of children if subsystem (NULL)
	} bl;
	struct {	// case: level>0, correspond to cluster
	    struct bltmp_clst *child; // one of children in cluster (NULL)
	} cl;
    } u;

    int		pos;    // position of vector or array
    int		order;  // exec order (earliest in cluster)
    float 	perf;   // performance of the block or clst
    int		cpu_util;	// CPU utilization (unit: 0.1%)
    int 	core;   // assigned core
    struct bltmp_alike	*alike_type;	// alike type

    // hierarchical graph structure
    struct bltmp_conn	*conn_s; // one of conn as initial node
    struct bltmp_conn	*conn_t; // one of conn as terminal node
    struct bltmp_clst	*parent; // parent node of the cluster
    struct bltmp_clst	*sibling; // one of siblings in the cluster

    // for path search (temporary use, not initialized)
    struct bltmp_clst	*Qnext;
    int		count_s, count_t, tmp;

    // for critical path calculation (not initialized)
    int		est;	// earliest start time
    int		lst;	// latest start time

    // task mapping group
    int		g_num;	// task mapping group number, init=-1
    int		num;	// clster number in a task mapping group (for hMETIS)
    int		next_pos; // next pos in the group
};

struct bltmp_conn {
    int		level;  // hierarchy level, 0:bledge, >0:clst, -1:not used (may be merged
    // BLG::bledge_T 	*org; // org bledge
    // int 		pos;  // position of vector or array
    int 		flag; // FALSE if reverse order in code, otherwise TRUE
    float		w;    // edge weight (normally 1)
    int		pos_s;	// position of initial node
    int		pos_t;	// position of terminal node
    struct bltmp_conn *next_s;	// next conn around initial node
    struct bltmp_conn *next_t;	// next conn aroung terminal node

    // for critical path calculation (not initialized)
    int		budget;		// budget for CP calc
    int		checked;	// checked conn in CP search
};

struct bltmp_hier {
    struct  bltmp_clst	*clst;  // cluster / block array in the hierarchy level
    int clst_n; // the number of clusters / blocks in the hierarcy level
    struct  bltmp_conn	*conn;  // connection array in the hierarchy level
    int conn_n;  // the number of connections in the hierarcy level
};

struct bltmp_core_budget {
    int core;
    int budget;
    struct bltmp_core_budget *next;
};

struct bltmp_tmp_params {
    int level;
    int first;
    int tmp_n;
    int tmp_m;
    int g_num;
    int part_n;
    struct bltmp_core_budget *coreb;
    int *core_trans;
    int *core_load;
    struct bltmp_clst *stnode;
};

typedef struct bltmp_clst blclst_T;
typedef struct bltmp_conn blconn_T;
typedef struct bltmp_alike blalike_T;
typedef struct bltmp_core_budget blcoreb_T;
typedef struct bltmp_tmp_params blparams_T;

int bltmp_0_read_blgraph(int, char *[], int *);
void bltmp_0_1_read_blnode(void);
void bltmp_0_2_subsystem_connect(void);
void bltmp_0_3_read_bledge(void);
void bltmp_0_4_rate_propagation(void);
void bltmp_0_5_calc_alike(void);
void bltmp_0_6_calc_weights(void);
int bltmp_1_clustering(int);
int bltmp_2_global_mapping(int, int, blcoreb_T ***, int **);
void bltmp_3_local_mapping(int, int, blcoreb_T **, int *); // new
// void bltmp_3_local_mapping(int, int, int); // old
void bltmp_8_output(void);
int bltmp_9_perf_eval(int, int);

void bltmp_delete_bledge(int);
void bltmp_connect(blconn_T *, int, int);
void bltmp_del_conn_s(blconn_T *);
void bltmp_del_conn_t(blconn_T *);
int bltmp_expand_to_lower(int);
int bltmp_check_mem_type_node(blclst_T *);
int bltmp_comp_alike(blalike_T *, blalike_T *);
int bltmp_get_pos_node(blnode_T *);
float bltmp_get_rate_value(blclst_T *);
blclst_T *bltmp_get_block_node(blclst_T *);

extern struct bltmp_hier hier[MAX_HIER];
extern Reader xrd;
extern BLGraph *p_graph;
extern int alike_count, non_atomic_alike;
extern int SINGLE_RATE;
extern char infile[FILENAME_LEN];
extern char outfile[FILENAME_LEN];

extern map<blalike_T*, blclst_T*> m_alike_type;
// better to be supported in BLGRAPH
extern map<block_T*, blnode_T*> xsd_blg_map;
extern map<blnode_T*, int> get_pos_blnode;

#define bltmp_get_name(node) \
	((node)->u.bl.org->p_block->name())

#define bltmp_get_blocktype(node) \
	((node)->u.bl.org->p_block->blocktype())

#define bltmp_get_rate(node) \
	((node)->u.bl.alike.rate)

#define bltmp_is_subsystem(node) \
	(bltmp_get_blocktype(node) == "SubSystem")

#define bltmp_has_effective_rate(node) \
	((*bltmp_get_rate(node)) && \
	(**bltmp_get_rate(node) != "-1") && \
	(**bltmp_get_rate(node) != "0") && \
	(**bltmp_get_rate(node) != "inf") && \
	(**bltmp_get_rate(node) != "SampleTime"))

#define bltmp_is_ioport(node) \
	((bltmp_get_blocktype(node) == "Inport") || \
	(bltmp_get_blocktype(node) == "Outport"))

#define bltmp_is_specialport(node) \
	((bltmp_get_blocktype(node) == "TriggerPort") || \
	(bltmp_get_blocktype(node) == "ActionPort") || \
	(bltmp_get_blocktype(node) == "EnablePort"))

#define bltmp_single_rate_terminals(node) \
	((bltmp_get_blocktype(node) != "Inport") && \
	(bltmp_get_blocktype(node) != "Outport") && \
	(bltmp_get_blocktype(node) != "UnitDelay") && \
	(bltmp_get_blocktype(node) != "Mux") && \
	(bltmp_get_blocktype(node) != "Demux") && \
	(bltmp_get_blocktype(node) != "SubSystem") && \
	(bltmp_get_blocktype(node).find("DataStore", 0) == string::npos))

