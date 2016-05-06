#include "bltmp2c.hxx"

// #define RENESPECIAL	1

// void bltmp_0_1_read_blnode(void);
// void bltmp_0_2_subsystem_connect(void);
// void bltmp_0_3_read_bledge(void);
static void bltmp_get_port_nodes(bledge_T *);
static int bltmp_is_same_subsystem(blnode_T *, blnode_T *);
static int bltmp_port_type(blnode_T *);
static void bltmp_loop_detect(void);
static void bltmp_dfs_loop_detect(blclst_T *, int);
// void bltmp_0_5_calc_alike(void);
static blalike_T *bltmp_make_alike(blclst_T *);
// void bltmp_delete_bledge(int);

struct bltmp_hier hier[MAX_HIER];
int alike_count, non_atomic_alike;
int SINGLE_RATE;

static vector<blnode_T*> node_list;
static vector<bledge_T*> edge_list;

map<blalike_T*, blclst_T*> m_alike_type;
map<block_T*, blnode_T*> xsd_blg_map;
map<blnode_T*, int> get_pos_blnode;

void bltmp_0_1_read_blnode(void) {
  int EXIST_PERF = FALSE;

#ifdef RENESPECIAL
  ofstream ofs("perf_output.csv");
#endif

  node_list = p_graph->getNodeVector();
  int node_n = node_list.size();
  blclst_T *blclst_list = 
	(blclst_T *)malloc(sizeof(blclst_T)*node_n);
  hier[0].clst = blclst_list;
  hier[0].clst_n = node_n;

  for(int i=0; i < node_n; i++) {
    blnode_T *node = node_list[i];
    xsd_blg_map[node->p_block] = node;
    get_pos_blnode[node] = i;

    blclst_T *blclst = &(blclst_list[i]);
    blclst->level = 0;
    blclst->u.bl.org = node;
    blclst->pos = i;
    blclst->g_num = -1;
    blclst->conn_s = blclst->conn_t = NULL;
    blclst->parent = blclst->sibling = NULL;
    blclst->u.bl.ss_parent = blclst->u.bl.ss_sibling = 
	blclst->u.bl.ss_child = NULL;

// cout << "node " << i << ":" << blclst->u.bl.org->p_block->name()  << endl;

    blclst->u.bl.alike.atomic = -1;
    if(((node->p_block->type()) && 
	    (*node->p_block->type() == "atomic")) ||
	((node->p_block->TreatAsAtomicUnit()) &&
	    (*node->p_block->TreatAsAtomicUnit() == "on"))) {
	blclst->u.bl.alike.atomic = i;
// cout << "Atomic Subsystem: " << bltmp_get_name(blclst) << endl;
    }
    blclst->order = -1;
    block_T::code_sequence cs = node->p_block->code();
    for(block_T::code_const_iterator ci = cs.begin(); ci!=cs.end(); ci++) {
      code_T code = *ci;
      if(code.line()) {
        int linum = code.line().get();
        if(code.type() == "task") blclst->order = linum;
        // cout << "code type=\"" << code.type() << "\" line=\""
        // << linum << "\" ...>" << endl;
      }
    }
    blclst->perf = 0;
    block_T::measuringResult_optional mr = node->p_block->measuringResult();
    if(mr){
	blclst->perf = (float)mr.get();
	EXIST_PERF = TRUE;
    }
    block_T::performance_sequence ps = node->p_block->performance();
    for(block_T::performance_const_iterator pi = ps.begin();
	pi != ps.end(); pi++) {
      performance_T perf = *pi;
      if(perf.typical()) {
        if(perf.type() == "task") blclst->perf += perf.typical();
        if(perf.type() == "update") blclst->perf += perf.typical();
	// cout << "perf type=\"" << perf.type() << "\" best=\""
        // << perf.best() << "\" typ=\"" << perf.typical()
        // << "\" worst=\"" << perf.worst() << "\"" << endl;
	EXIST_PERF = TRUE;
      }
    }
#ifdef RENESPECIAL
BlockInfo *bi = xrd.find_block(bltmp_get_name(blclst));
ofs << bltmp_get_blocktype(blclst) << "," << bltmp_get_name(blclst);
if(bi->merged_to().size() != 0) ofs << ",-1" << endl;
else ofs << "," << blclst->perf << endl;
#endif
  }
  if(EXIST_PERF == FALSE) {
    for(int i=0; i < node_n; i++) blclst_list[i].perf = 1;
  }
#ifdef RENESPECIAL
  ofs.close();
#endif
}

void bltmp_0_2_subsystem_connect(void) {
    blclst_T *blclst = hier[0].clst, *node, *parent;
    int clst_n = hier[0].clst_n, pos_parent;
    BlockInfo *bi, *bi_upper;

    for(int i=0; i<clst_n; i++) {
	node = &(blclst[i]);
	bi = xrd.find_block(bltmp_get_name(node));
	if((bi_upper=bi->upper_subsystem()) != NULL) {
	    pos_parent = bltmp_get_pos_node(xsd_blg_map[bi_upper->block()]);
	    parent = &(blclst[pos_parent]);
	    node->u.bl.ss_parent = parent;
	    node->u.bl.ss_sibling = parent->u.bl.ss_child;
	    parent->u.bl.ss_child = node;
	    while((bi_upper)) {
		if(((bi_upper->block()->type()) && 
			((*bi_upper->block()->type() == "atomic") ||
			(*bi_upper->block()->type() == "enabled") ||
			(*bi_upper->block()->type() == "triggered"))) ||
		    ((bi_upper->block()->TreatAsAtomicUnit()) &&
			(*bi_upper->block()->TreatAsAtomicUnit() == "on"))) {
// cout << bltmp_get_name(node) << " is in Atomic Subsystem: " << bi_upper->block()->name() << endl;
		    node->u.bl.alike.atomic = bltmp_get_pos_node(xsd_blg_map[bi_upper->block()]);
		}
		bi_upper = bi_upper->upper_subsystem();
	    }
	}
    }
}

void bltmp_0_3_read_bledge(void) {
  edge_list = p_graph->getEdgeVector();
  int edge_n = edge_list.size();
  blclst_T *blclst = hier[0].clst;
  blconn_T *blconn_list = 
	(blconn_T *)malloc(sizeof(blconn_T)*edge_n);
  hier[0].conn = blconn_list;
  hier[0].conn_n = edge_n;

  for(int i=0; i < edge_n; i++) {
    bledge_T *edge = edge_list[i];
    blconn_T *blconn = &(blconn_list[i]);
    blconn->level = 0;
    blconn->w = 1.0;	// maybe more sophisticated value in future
    // blconn->org = edge;
    // blconn->pos = i;

// if((edge->p_s_node->p_block->name().find("synrmmodel_mt_RTW_Maketargetvalue1", 0) 
// == 0) || (edge->p_t_node->p_block->name().find("synrmmodel_mt_RTW_Maketargetvalue1", 0) 
// == 0)) {
// cout << "X " << edge->p_s_node->p_block->name() << ":" <<  edge->p_t_node->p_block->name() << endl;
// }
    if((edge->p_s_node->p_block->blocktype() == "SubSystem") ||
	(edge->p_t_node->p_block->blocktype() == "SubSystem")) {
	bltmp_get_port_nodes(edge);
    }
    int pos_s = bltmp_get_pos_node(edge->p_s_node);
    int pos_t = bltmp_get_pos_node(edge->p_t_node);

    if(pos_s == pos_t) {
	blconn->level = -1;
	continue;
    }

    if(blclst[pos_t].u.bl.org->p_block->blocktype() == "UnitDelay") {
	blconn->flag = FALSE;
    } else if((blclst[pos_t].order < 0) || 
	(blclst[pos_s].order < blclst[pos_t].order)) {
      blconn->flag = TRUE;
    } else {
      blconn->flag = FALSE;
    }
    bltmp_connect(blconn, pos_s, pos_t);
    blconn->checked = FALSE;
  }
  bltmp_loop_detect();
}

// When an edge is connected to a terminal of subsystem,
// reconnected to the ioport block associated with the terminal
static void bltmp_get_port_nodes(bledge_T *edge) {
    blnode_T *node_s = edge->p_s_node;
    blnode_T *node_t = edge->p_t_node;
    block_T *block;

// cout << "-----" << endl;
// cout << "check SubSystem(s) " << node_s->p_block->name() << ":" << node_s->p_block->blocktype() << endl;
// cout << "check SubSystem(t) " << node_t->p_block->name() << ":" << node_t->p_block->blocktype() << endl; 
// cout << "Start s" << endl;

    if(node_s->p_block->blocktype() == "SubSystem") {
	if((!bltmp_is_same_subsystem(node_s, node_t)) && (bltmp_port_type(node_t))) {
	    BlockInfo *bi = xrd.find_block(node_t->p_block->name());
	    block = bi->upper_subsystem()->block();
	    if(node_s->p_block == block) {
		edge->p_t_node = xsd_blg_map[block];
// cout << "Delete! (" << node_s->p_block->name() << "," << node_t->p_block->name() << ")" << endl;
		return;
	    }
	}
	block =  node_t->p_block;
	int flag = FALSE;
	block_T::output_iterator oi(node_s->p_block->output().begin());
	for(; oi != node_s->p_block->output().end(); oi++) {
// cout << "check output " << oi->line() << ":" << oi->port() << endl;
	    ioport_T::connect_const_iterator cci(oi->connect().begin());
	    for(; cci != oi->connect().end(); cci++){
// cout << "check connect " << cci->block() << ":" << cci->port() << endl;
		if((cci->block() == block->name()) ||
		    (cci->port() == block->name())) {
// cout << "get " << oi->port() << endl;
	    	    BlockInfo *bix = xrd.find_block(oi->port());
		    edge->p_s_node = xsd_blg_map[bix->block()];
		    flag = TRUE;
// cout << "take node " << edge->p_s_node->p_block->name() << endl;
		    break;
		}
	    }
	    if(flag) break;
	}
    }

// cout << "Start t" << endl;

    if(node_t->p_block->blocktype() == "SubSystem") {
	if((!bltmp_is_same_subsystem(node_s, node_t)) && (bltmp_port_type(node_s))) {
	    BlockInfo *bi = xrd.find_block(node_s->p_block->name());
	    block = bi->upper_subsystem()->block();
	    if(node_t->p_block == block) {
		edge->p_s_node = xsd_blg_map[block];
// cout << "Delete!" << endl;
		return;
	    }
	}
	block =  node_s->p_block;
	int flag = FALSE;
	block_T::input_iterator ii(node_t->p_block->input().begin());
	for(; ii != node_t->p_block->input().end(); ii++) {
// cout << "check input " << ii->line() << ":" << ii->port() << endl;
	    ioport_T::connect_const_iterator cci(ii->connect().begin());
	    for(; cci != ii->connect().end(); cci++){
// cout << "check connect " << cci->block() << ":" << cci->port() << endl;
		if((cci->block() == block->name()) ||
		    (cci->port() == block->name())) {
// cout << "get " << ii->port() << endl;
	    	    BlockInfo *bix = xrd.find_block(ii->port());
		    edge->p_t_node = xsd_blg_map[bix->block()];
		    flag = TRUE;
// cout << "take node " << edge->p_t_node->p_block->name() << endl;
		    break;
		}
	    }
	    if(flag) break;
	}
    }
}

static int bltmp_is_same_subsystem(blnode_T *node_s, blnode_T *node_t) {
    blclst_T *blclst = hier[0].clst;
    int pos_s = get_pos_blnode[node_s];
    int pos_t = get_pos_blnode[node_t];
    return (blclst[pos_s].u.bl.ss_parent == blclst[pos_t].u.bl.ss_parent);
}

static int bltmp_port_type(blnode_T *node) {
    if(node->p_block->blocktype() == "Inport") return TRUE;
    if(node->p_block->blocktype() == "Outport") return TRUE;
    if(node->p_block->blocktype() == "TriggerPort") return TRUE;
    if(node->p_block->blocktype() == "ActionPort") return TRUE;
    if(node->p_block->blocktype() == "EnablePort") return TRUE;
    return FALSE;
}

static void bltmp_loop_detect(void) {
    blclst_T *blclst = hier[0].clst, *node, *Q=NULL;
    int clst_n = hier[0].clst_n;
    blconn_T *conn;

    for(int i=0; i<clst_n; i++) {
	node = &blclst[i];
	node->tmp = -1;
	for(conn=node->conn_t; conn; conn=conn->next_t) {
	    if(conn->flag == FALSE) continue;
	    break;
	}
	if(!conn) {
	    node->Qnext = Q;
	    Q = node;
	}
    }
    for(node=Q; node; node=node->Qnext)	bltmp_dfs_loop_detect(node, 0);
}

static void bltmp_dfs_loop_detect(blclst_T *node0, int rank) {
    blclst_T *blclst = hier[0].clst, *node;
    blconn_T *conn;

    node0->tmp = rank;
    for(conn=node0->conn_s; conn; conn=conn->next_s) {
	if(conn->checked == TRUE) continue;
	conn->checked = TRUE;
	if(conn->flag == FALSE) continue;
	node = &blclst[conn->pos_t];
	if(node->tmp == -1) bltmp_dfs_loop_detect(node, rank+1);
	else conn->flag = FALSE;
    }
    node0->tmp = -1;
}

void bltmp_0_5_calc_alike(void) {
    blclst_T *blclst = hier[0].clst, *node, *node2;
    int clst_n = hier[0].clst_n, pos;

    alike_count = 0;
    non_atomic_alike = -1;
    node2 = NULL;
    SINGLE_RATE = TRUE;
    for(int i=0; i<clst_n; i++) {
	node = &(blclst[i]);
	if(bltmp_has_effective_rate(node)) {
	    if(!node2) node2 = node;
	    else {
		if(**bltmp_get_rate(node) != **bltmp_get_rate(node2)) {
		    SINGLE_RATE = FALSE;
		}
	    }
	}
	if(node->u.bl.alike.atomic != node->pos) continue;
	alike_count++;
	node->alike_type = bltmp_make_alike(node);
	m_alike_type[node->alike_type] = node;
	node->tmp = -1;
    }
    for(int i=0; i<clst_n; i++) {
	node = &(blclst[i]);
	if(node->u.bl.alike.atomic == node->pos) continue;
	if((pos=node->u.bl.alike.atomic) == -1) pos = non_atomic_alike;
	for(; pos!=-1; pos=node2->tmp) {
	    node2 = &(blclst[pos]);
	    if(bltmp_comp_alike(&(node->u.bl.alike), &(node2->u.bl.alike)) == 0) break;
	}
	if(pos != -1) { // already exist
	    node->alike_type = node2->alike_type;
	    if(bltmp_check_mem_type_node(m_alike_type[node->alike_type]) == TRUE)
		m_alike_type[node->alike_type] = node;
	    continue;
	}
	alike_count++;
	node->alike_type = bltmp_make_alike(node);
	m_alike_type[node->alike_type] = node;
	if(node->u.bl.alike.atomic == -1) {
	    node->tmp = non_atomic_alike;
	    non_atomic_alike = node->pos;
	} else {
	    node2 = &(blclst[node->u.bl.alike.atomic]);
	    node->tmp = node2->tmp;
	    node2->tmp = node->pos;
	}
    }
}

static blalike_T *bltmp_make_alike(blclst_T *node) {
    blalike_T *alike = &node->u.bl.alike;
    blalike_T *new_alike = (blalike_T*)malloc(sizeof(blalike_T));
    new_alike->rate = alike->rate;
    new_alike->atomic = alike->atomic;
cerr << "alike group: rate=" << *alike->rate << ", atomic=" << alike->atomic << endl;
    return new_alike;
}

void bltmp_0_6_calc_weights(void) {
    blclst_T *blclst = hier[0].clst, *node;
    int clst_n = hier[0].clst_n;
    blconn_T *blconn = hier[0].conn, *conn;
    int conn_n = hier[0].conn_n;
    float rate_s, rate_t;

    if(SINGLE_RATE) {
        for(int i=0; i<clst_n; i++) {
	    node = &(blclst[i]);
	    node->cpu_util = (node->perf == 0) ? 1 : node->perf;
	}
	return;
    }
    // for multi rate
    for(int i=0; i<clst_n; i++) {
	node = &(blclst[i]);
	rate_s = bltmp_get_rate_value(node);
// cout << "rate_s=" << rate_s << endl;
	if(rate_s <= 0) rate_s = BASE_RATE;
	node->cpu_util = (int)(node->perf * PRECISION / CPU_MIPS / rate_s + 0.5);
	if(node->cpu_util == 0) node->cpu_util = 1;
// cout << "cpu_util=" << node->cpu_util << endl;
    }
    for(int i=0; i<conn_n; i++) {
	conn = &(blconn[i]);
	if(conn->level < 0) continue;
	rate_s = bltmp_get_rate_value(&blclst[conn->pos_s]);
	if(rate_s <= 0) rate_s = BASE_RATE;
	rate_t = bltmp_get_rate_value(&blclst[conn->pos_t]);
	if(rate_t <= 0) rate_t = BASE_RATE;
// cout << "rate_s=" << rate_s << ", rate_t=" << rate_t << endl;
	if(rate_s > rate_t) rate_s = rate_t;
	conn->w = (int)(conn->w * PRECISION / CPU_MIPS / rate_s + 0.5);
	if(conn->w == 0) conn->w = 1;
// cout << "w=" << conn->w << endl;
    }
}

void bltmp_delete_bledge(int i) {
    p_graph->deleteEdge(edge_list[i]);
}
