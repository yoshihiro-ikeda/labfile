#include "bltmp2c.hxx"

void bltmp_connect(blconn_T *conn, int pos_s, int pos_t) {
    int level = conn->level;
    blclst_T *clst_list = hier[level].clst;
    blclst_T *clst_s = &clst_list[pos_s];
    blclst_T *clst_t = &clst_list[pos_t];
    blconn_T *prev, *next;

// cout << "bltmp_connect " << pos_s << " to " << pos_t << endl;

    conn->pos_s = pos_s;
    conn->pos_t = pos_t;

    prev = NULL;
    for(next=clst_s->conn_s; next; prev=next, next=next->next_s) {
	if(pos_t <= next->pos_t) break;
    }
    if((next) && (pos_t == next->pos_t)) {  // merge conns because equal (pos_s, pos_t)
	next->w += conn->w;
	conn->level = -1;
	return;
    }
    conn->next_s = next;
    if(prev) prev->next_s = conn;
    else clst_s->conn_s = conn;

    prev = NULL;
    for(next=clst_t->conn_t; next; prev=next, next=next->next_t) {
	if(pos_s <= next->pos_s) break;
    }
    conn->next_t = next;
    if(prev) prev->next_t = conn;
    else clst_t->conn_t = conn;
}

void bltmp_del_conn_s(blconn_T *conn) {
    int level = conn->level;
    blclst_T *clst_list = hier[level].clst;
    blclst_T *clst = &clst_list[conn->pos_s];
    blconn_T *prev, *next;

    prev = NULL;
    for(next=clst->conn_s; next; prev=next, next=next->next_s) {
	if(conn == next) break;
    }
    if(!next) return;
    if(prev) prev->next_s = conn->next_s;
    else clst->conn_s = conn->next_s;
}

void bltmp_del_conn_t(blconn_T *conn) {
    int level = conn->level;
    blclst_T *clst_list = hier[level].clst;
    blclst_T *clst = &clst_list[conn->pos_t];
    blconn_T *prev, *next;

    prev = NULL;
    for(next=clst->conn_t; next; prev=next, next=next->next_t) {
	if(conn == next) break;
    }
    if(!next) return;
    if(prev) prev->next_t = conn->next_t;
    else clst->conn_t = conn->next_t;
}

int bltmp_expand_to_lower(int level) {
    blclst_T *blclst = hier[level].clst, *node;
    int clst_n = hier[level].clst_n;

cout << "LEVEL " << level << " to " << level-1 << endl;
    if(level <= 0) return level;

    for(int i=0; i<clst_n; i++) {
	if(blclst[i].level < 0) continue;
	int core = blclst[i].core;
	int g_num = blclst[i].g_num;
	for(node=blclst[i].u.cl.child; node; node=node->sibling) {
	    node->core = core;
	    node->g_num = g_num;
	}
    }
    return (level-1);
}

int bltmp_check_mem_type_node(blclst_T *node) {
    blclst_T *block_node = bltmp_get_block_node(node);

    if(block_node->u.bl.org->p_block->blocktype().find("DataStore", 0) 
		== 0) return TRUE;
    if(block_node->u.bl.org->p_block->blocktype().find("UnitDelay", 0) 
		== 0) return TRUE;
    return FALSE;
}

int bltmp_comp_alike(blalike_T *alike1, blalike_T *alike2) {
    if(alike1->atomic != alike2->atomic) return -1;
    if(*alike1->rate != *alike2->rate) return -1;
    return 0;
}

blclst_T *bltmp_get_block_node(blclst_T *clst) {
    if(clst->level == 0) return clst;
    return bltmp_get_block_node(clst->u.cl.child);
}

float bltmp_get_rate_value(blclst_T *clst) {
    blclst_T *node = bltmp_get_block_node(clst);
    if(!bltmp_has_effective_rate(node)) return -1.0;
    return std::atof((**bltmp_get_rate(node)).c_str());
}

/* should be supperted by BLGRAPH */
int bltmp_get_pos_node(blnode_T *node) {
    if(get_pos_blnode.find(node) != get_pos_blnode.end())
	return get_pos_blnode[node];
    return -1;
}

