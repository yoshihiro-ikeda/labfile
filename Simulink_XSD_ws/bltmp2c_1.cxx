#include "bltmp2c.hxx"

static void bltmp_1_1_datastore_merge(int);
static void bltmp_1_2_lump_code_merge(int);
static void bltmp_1_3_special_port_merge(int);
static void bltmp_1_4_subsystem_merge(int);
static void bltmp_1_5_alike_merge(int);
static int bltmp_make_upper_cluster(int);
static blclst_T *get_norate_in_atomic(blalike_T *);
static blclst_T *bltmp_merge_node(blclst_T *, blclst_T *, int);

int bltmp_1_clustering(int part_k) {
    int level = 0;
    level = bltmp_make_upper_cluster(level);
    bltmp_1_1_datastore_merge(level);
    bltmp_1_2_lump_code_merge(level);
    bltmp_1_3_special_port_merge(level);
    bltmp_1_4_subsystem_merge(level);
    level = bltmp_make_upper_cluster(level);
    bltmp_1_5_alike_merge(level);
    return level;
}

static void bltmp_1_1_datastore_merge(int level) {
    blclst_T *blclst = hier[level].clst, *node, *node2, *block_node;
    int clst_n = hier[level].clst_n;
    map<block_T::DataStoreName_optional, blclst_T*> m_dsname;

    for(int i=0; i<clst_n; i++) {
	node = &blclst[i];
	if(node->level < 0) continue;
	block_node = bltmp_get_block_node(node);
	if(bltmp_get_blocktype(block_node).find("DataStore", 0) 
		!= 0) continue;
	if(m_dsname.find(block_node->u.bl.org->p_block->DataStoreName())
		== m_dsname.end()) {
	    m_dsname[block_node->u.bl.org->p_block->DataStoreName()] = node;
	} else {
	    node2 = m_dsname[block_node->u.bl.org->p_block->DataStoreName()];
/*
cout << "DataStore merge " << node2->pos << " and " << node->pos << ": "
<< bltmp_get_block_node(node2)->u.bl.org->p_block->name() << " and "
<< bltmp_get_block_node(node)->u.bl.org->p_block->name() << endl;
*/
	    node2 = bltmp_merge_node(node2, node, FALSE);
	    m_dsname[block_node->u.bl.org->p_block->DataStoreName()] = node2;
	}
    }
}

static void bltmp_1_2_lump_code_merge(int level) {
    blclst_T *blclst0 = hier[0].clst, *node, *node2;
    int clst_n0 = hier[0].clst_n;
    BlockInfo *bi, *merged_by;

    for(int i=0; i<clst_n0; i++) {
	node = &blclst0[i];
	if(bltmp_check_mem_type_node(node) == TRUE) continue;
	bi = xrd.find_block(node->u.bl.org->p_block->name());
	if(bi->merged_to().size() == 0) continue;
	merged_by = *bi->merged_to().begin();
	node2 = &blclst0[bltmp_get_pos_node(xsd_blg_map[merged_by->block()])];
	for(int l=level; l>0; l--, node2=node2->parent);
	for(int l=level; l>0; l--, node=node->parent);
	bltmp_merge_node(node2, node, TRUE);
    }
}

static void bltmp_1_3_special_port_merge(int level) {
    blclst_T *blclst0 = hier[0].clst, *node, *node2;
    int clst_n0 = hier[0].clst_n;
    blclst_T *ioport, *special_port;

    for(int i=0; i<clst_n0; i++) {
	node = &blclst0[i];
	if(node->u.bl.org->p_block->blocktype() != "SubSystem") continue;
	ioport = special_port = NULL;
	for(node2=node->u.bl.ss_child; node2; node2=node2->u.bl.ss_sibling) {
	    if(bltmp_is_ioport(node2)) ioport = node2;
	    else if(bltmp_is_specialport(node2)) special_port = node2;
	}
	if((ioport == NULL) || (special_port == NULL)) continue;
// cout << "special port merge: " << special_port->u.bl.org->p_block->name()
// << " is merged to " << ioport->u.bl.org->p_block->name() << endl;
	for(int l=level; l>0; l--, ioport=ioport->parent);
	for(int l=level; l>0; l--, special_port=special_port->parent);
	bltmp_merge_node(ioport, special_port, FALSE);
    }
}

static void bltmp_1_4_subsystem_merge(int level) {
    blclst_T *blclst = hier[level].clst, *node, *node2, *block_node;
    int clst_n = hier[level].clst_n, l;

    for(int i=0; i<clst_n; i++) {
	node = &blclst[i];
	if(node->level < 0) continue;
	if((node->conn_s) || (node->conn_t)) continue;
	block_node = bltmp_get_block_node(node);
	if((node2=block_node->u.bl.ss_child)) {
	    while(node2) {
		if((node2->conn_s) || (node2->conn_t)) break;
		node2 = node2->u.bl.ss_sibling;
	    }
	    if(!node2) break;
	    for(l=node->level; l>0; l--, node2=node2->parent);
	    bltmp_merge_node(node2, node, FALSE);
	} else if((node2=block_node->u.bl.ss_sibling)) {
	    while(node2) {
		if((node2->conn_s) || (node2->conn_t)) break;
		node2 = node2->u.bl.ss_sibling;
	    }
	    if(!node2) break;
	    for(l=node->level; l>0; l--, node2=node2->parent);
	    bltmp_merge_node(node2, node, FALSE);
	}
    }
}

static void bltmp_1_5_alike_merge(int level) {
    blclst_T *blclst = hier[level].clst, *node, *node2;
    int clst_n = hier[level].clst_n;

// cout << "Alike Merge" << endl;

    for(int i=0; i<clst_n; i++) {
	node = &blclst[i];
	if(node->level < 0) continue;
	node2 = m_alike_type[node->alike_type];
	if(!bltmp_has_effective_rate(node2)) {
	    node2 = get_norate_in_atomic(node->alike_type);
	    node->alike_type = node2->alike_type;
	}
	for(int l=level; l>0; l--, node2 = node2->parent);
	bltmp_merge_node(node2, node, TRUE);
    }
}

static blclst_T *get_norate_in_atomic(blalike_T *alike) {
    for(map<blalike_T*, blclst_T*>::iterator ai=m_alike_type.begin();
	    ai!=m_alike_type.end(); ai++) {
// cout << ai->first->atomic << "," << ai->first->rate << endl;
	blclst_T *node = ai->second;
	if(bltmp_has_effective_rate(node)) continue;
	if(node->alike_type->atomic == alike->atomic) {
	    return node;
	}
    }
assert(0);
    return NULL;
}

// return merger node. if not merged, return NULL
// check=TRUE: not merge if memory type node
static blclst_T *bltmp_merge_node(blclst_T *node_p, blclst_T *node_c, int check) {
    blclst_T *blclst = hier[node_p->level].clst;
    blclst_T *node_p_c, *node_c_c, *last;
    blconn_T *conn, *next;

    if(node_p == node_c) return node_p;
    if(check == TRUE) {
	if(bltmp_check_mem_type_node(node_p) == TRUE) return NULL;
	if(bltmp_check_mem_type_node(node_c) == TRUE) return NULL;
    }
    if(node_c->order != -1) {
	if((node_p->order == -1) || (node_c->order < node_p->order)) {
	    last = node_p;
	    node_p = node_c;
	    node_c = last;
	}
    }
    node_p_c = node_p->u.cl.child;
    node_c_c = node_c->u.cl.child;

// cout << "merge " << node_p->pos << "<-" << node_c->pos << endl;;
// cout << "node_p:" << node_p_c->u.bl.org->p_block->name() << ":" << node_p_c->u.bl.org->p_block->blocktype() << endl;
// cout << "node_c:" << node_c_c->u.bl.org->p_block->name() << ":" << node_c_c->u.bl.org->p_block->blocktype() << endl;

    for(last=node_c_c; last->sibling; last=last->sibling) last->parent = node_p;
    last->parent = node_p;
    last->sibling = node_p_c;
    node_p->u.cl.child = node_c_c;
    node_c->level = -1;
    node_p->perf += node_c->perf;
    node_p->cpu_util += node_c->cpu_util;

    for(conn=node_c->conn_s; conn; conn=next) {
	next = conn->next_s;
        if((blclst[conn->pos_t].order < 0) || 
	    (blclst[node_p->pos].order < blclst[conn->pos_s].order)) {
	    conn->flag = TRUE;
	} else {
	    conn->flag = FALSE;
	}
	bltmp_del_conn_t(conn);
	bltmp_connect(conn, node_p->pos, conn->pos_t);
    }
    for(conn=node_c->conn_t; conn; conn=next) {
	next = conn->next_t;
        if((blclst[node_p->pos].order < 0) || 
	    (blclst[conn->pos_s].order < blclst[node_p->pos].order)) {
	    conn->flag = TRUE;
	} else {
	    conn->flag = FALSE;
	}
	bltmp_del_conn_s(conn);
	bltmp_connect(conn, conn->pos_s, node_p->pos);
    }
    return node_p;
}

static int bltmp_make_upper_cluster(int l_level) {
    int u_level = l_level+1;
    blclst_T *l_blclst = hier[l_level].clst, *u_blclst;
    int l_clst_n = hier[l_level].clst_n, u_clst_n;
    blconn_T *l_blconn = hier[l_level].conn, *u_blconn;
    int l_conn_n = hier[l_level].conn_n, u_conn_n;
    blclst_T *l_node, *u_node;
    blconn_T *l_conn, *u_conn;
    int i;

    u_clst_n = 0;
    for(int i=0; i <l_clst_n; i++) {
	l_node = &(l_blclst[i]);
	if(l_node->level >= 0) u_clst_n++;
    }
    u_blclst = (blclst_T *)malloc(sizeof(blclst_T)*u_clst_n);
    hier[u_level].clst = u_blclst;
    hier[u_level].clst_n = u_clst_n;

    i = 0;
    for(int j=0; j < l_clst_n; j++) {
	l_node = &(l_blclst[j]);
	if(l_node->level < 0) continue;
	u_node = &(u_blclst[i]);

	u_node->level = u_level;
	u_node->u.cl.child = l_node;
	l_node->parent = u_node;
	u_node->pos = i;
	u_node->order = l_node->order;
	u_node->perf = l_node->perf;
	u_node->cpu_util = l_node->cpu_util;
	u_node->alike_type = l_node->alike_type;
	u_node->core = l_node->core;
	u_node->conn_s = u_node->conn_t = NULL;
	u_node->parent = u_node->sibling = NULL;
	u_node->g_num = -1;
	i++;
    }

    u_conn_n = 0;
    for(int i=0; i <l_conn_n; i++) {
	l_conn = &(l_blconn[i]);
	if(l_conn->level >= 0) u_conn_n++;
    }
    u_blconn = (blconn_T *)malloc(sizeof(blconn_T)*u_conn_n);
    hier[u_level].conn = u_blconn;
    hier[u_level].conn_n = u_conn_n;

    i = 0;
    for(int j=0; j < l_conn_n; j++) {
	l_conn = &(l_blconn[j]);
	if(l_conn->level < 0) continue;
	u_conn = &(u_blconn[i++]);

	u_conn->level = u_level;
	u_conn->flag = l_conn->flag;
	int pos_s = l_blclst[l_conn->pos_s].parent->pos;
	int pos_t = l_blclst[l_conn->pos_t].parent->pos;

	bltmp_connect(u_conn, pos_s, pos_t);
    }
    return u_level;
}

