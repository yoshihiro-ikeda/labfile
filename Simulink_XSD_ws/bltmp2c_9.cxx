#include "bltmp2c.hxx"

static int bltmp_9_1_group_all_blocks(void);
static void bltmp_9_2_make_graph(int, blclst_T *);
static void bltmp_9_3_longest_from_sink(int, blclst_T *, int);
static int bltmp_9_4_eval_delay(int, blclst_T *, int, int);
static void bltmp_9_5_write_results(int, blclst_T *, int);

static blclst_T *get_farthest_Qnode(blclst_T **);
static void bltmp_free_stedges(blclst_T *);

int bltmp_9_perf_eval(int part_k, int w_overhead) {
    int max_delay;
    blclst_T *stnode = (blclst_T *)malloc(sizeof(*stnode));
    int first;
    first = bltmp_9_1_group_all_blocks();
    bltmp_9_2_make_graph(first, stnode);
    bltmp_9_3_longest_from_sink(first, stnode, w_overhead);
    max_delay = bltmp_9_4_eval_delay(first, stnode, part_k, w_overhead);
    bltmp_9_5_write_results(first, stnode, max_delay);
    bltmp_free_stedges(stnode);
    return max_delay;
}

static int bltmp_9_1_group_all_blocks(void) {
    blclst_T *blclst = hier[0].clst;
    int clst_n = hier[0].clst_n;
    int num_n=0, prev, first;

    for(int i=0; i<clst_n; i++) {
	num_n++;
	blclst[i].num = num_n;
	if(num_n == 1) {
	    first = i;
	} else {
	    blclst[prev].next_pos = i;
	}
	prev = i;
    }
    blclst[prev].next_pos = -1;
    return first;
}

static void bltmp_9_2_make_graph(int first, blclst_T *stnode) {
    blclst_T *blclst = hier[0].clst, *node;
    blconn_T *conn, *new_conn;

    stnode->conn_s = stnode->conn_t = NULL;
    for(int pos=first; pos!=-1; pos=node->next_pos) {
	node = &blclst[pos];
	node->count_s = node->count_t = 0;

	/* add snode */
	for(conn=node->conn_t; conn; conn=conn->next_t) {
	    if(conn->flag == FALSE) continue;
	    break;
	}
	if(!conn) {
	    new_conn = (blconn_T *)malloc(sizeof(*new_conn));
	    new_conn->pos_s = -1;
	    new_conn->pos_t = pos;
	    new_conn->next_s = stnode->conn_s;
	    stnode->conn_s = new_conn;
	}

	/* add tnode */
	for(conn=node->conn_s; conn; conn=conn->next_s) {
	    if(conn->flag == FALSE) continue;
	    break;
	}
	if(!conn) {
	    new_conn = (blconn_T *)malloc(sizeof(*new_conn));
	    new_conn->pos_s = pos;
	    new_conn->pos_t = -1;
	    new_conn->next_t = stnode->conn_t;
	    stnode->conn_t = new_conn;
	}
    }
    for(int pos=first; pos!=-1; pos=node->next_pos) {
	node = &blclst[pos];

	/* count snode */
	for(conn=node->conn_s; conn; conn=conn->next_s) {
	    if(conn->flag == FALSE) continue;
	    blclst[conn->pos_t].count_s++;
	}
	/* count tnode */
	for(conn=node->conn_t; conn; conn=conn->next_t) {
	    if(conn->flag == FALSE) continue;
	    blclst[conn->pos_s].count_t++;
	}
    }
}

static void bltmp_9_3_longest_from_sink(int first, blclst_T *stnode, int w_overhead) {
    blclst_T *blclst=hier[0].clst, *node, *node0, *Q=NULL;
    blconn_T *conn;
    int lst;

// cout << "start longest path analysis from sink" << endl;

    for(int pos=first; pos!=-1; pos=node->next_pos) {
	node = &blclst[pos];
	node->tmp = node->count_t;
	node->lst = 0;
    }
    for(conn=stnode->conn_t; conn; conn=conn->next_t) {
	node = &blclst[conn->pos_s];
	node->Qnext = Q;
	Q = node;
// cout << "add node " << node->pos << "(" << 
// bltmp_get_name(node) << ")" << endl;
    }
    while((node0=Q)!=NULL) {
	Q = Q->Qnext;
	node0->lst += node0->cpu_util;
	for(conn=node0->conn_t; conn; conn=conn->next_t) {
	    node = &blclst[conn->pos_s];
	    if(conn->flag == FALSE) continue;
	    if(node0->core != node->core) lst = node0->lst + w_overhead;
	    else lst = node0->lst;
	    if(node->lst < lst) node->lst = lst;
	    if((--node->tmp) <= 0) {
		node->Qnext = Q;
		Q = node;
// cout << "add node " << node->pos << "(" << 
// bltmp_get_name(node) << ")" << endl;
	    }
	}
    }
}

static int bltmp_9_4_eval_delay(int first, blclst_T *stnode, int part_k, int w_overhead) {
    blclst_T *blclst=hier[0].clst, *node, *node0, *Q=NULL;
    blconn_T *conn;
    int perf, est, max_est[part_k], max_delay;
    int sum_est[part_k], sum_delay, max_sum;

// cout << "start calculate eval delay" << endl;

    for(int i=0; i<part_k; i++) max_est[i] = sum_est[i] = 0;
    for(int pos=first; pos!=-1; pos=node->next_pos) {
	node = &blclst[pos];
	node->tmp = node->count_s;
	node->est = 0;
    }
    for(conn=stnode->conn_s; conn; conn=conn->next_s) {
	node = &blclst[conn->pos_t];
	node->Qnext = Q;
	Q = node;
// cout << "add node " << node->pos << "(" << 
// node->u.bl.org->p_block->name() << ")" << endl;
    }
    while((node0=get_farthest_Qnode(&Q))!=NULL) {
	perf = node0->cpu_util;
	/* in case no performance is annotated at connected node */
	if((node0->count_s != 0) || (node0->count_t != 0)) {
	    if(perf == 0) perf = 1;
	}
	sum_est[node0->core] += perf;
	if(node0->est < max_est[node0->core]) node0->est = max_est[node0->core]+0.5;

// cout << "Eval node " << node0->pos << "(" << node0->u.bl.org->p_block->name() 
// << "): core" << node0->core << ": Start " << node0->est << "+ Perf "
// << perf << ", Sum "<< sum_est[node0->core] << endl;

	max_est[node0->core] = est = node0->est + perf;

	for(conn=node0->conn_s; conn; conn=conn->next_s) {
	    node = &blclst[conn->pos_t];
	    if(conn->flag == FALSE) {
		if(node0->core != node->core) {
		    if(max_est[node->core] < est + w_overhead)
			max_est[node->core] = est + w_overhead;
		}
	        continue;
	    }
	    if(node->est < est) {
		node->est = est+0.5;
	    }
	    if((--node->tmp) <= 0) {
		node->Qnext = Q;
		Q = node;
// cout << "add node " << node->pos << "(" << 
// node->u.bl.org->p_block->name() << ")" << endl;
	    }
	}
    }
    if(SINGLE_RATE == TRUE) cerr << "SINGLE RATE" << endl;
    else cerr << "MULTIPLE RATE" << endl;
    max_delay = sum_delay = max_sum = 0;
    for(int i=0; i<part_k; i++) {
	cerr << "core "  << i << ": max delay = " << max_est[i]
	    << ", sum delay = " << sum_est[i] << endl;
	sum_delay += sum_est[i];
	if(max_delay < max_est[i]) max_delay = max_est[i];
	if(max_sum < sum_est[i]) max_sum = sum_est[i];
    }
    cerr << "Total: max delay = " << max_delay
	    << ", sum delay = " << sum_delay 
	    << ", ratio = " << (float)sum_delay / (float)max_delay << endl;
    cerr << "(ratio of CPU utils = " << (float)sum_delay / (float)max_sum << ")" << endl;
    return max_delay;
}

static void bltmp_9_5_write_results(int first, blclst_T *stnode, int max_delay) {
    blclst_T *blclst=hier[0].clst, *node;
    int clst_n = hier[0].clst_n, i;
    blconn_T *blconn = hier[0].conn, *conn;
    int conn_n = hier[0].conn_n;
    ofstream ofs("tmp_sch_results.csv");

    ofs << "% # of blocks, # of connections, # maximum delay" << endl;
    ofs << clst_n << "," << conn_n << "," << max_delay << endl;
    ofs << "% block no, block name, core, start time, end time" << endl;

    for(i=0; i<clst_n; i++) {
	node = &blclst[i];
	ofs << i << "," << node->u.bl.org->p_block->name() << "," 
	<< node->core << "," << node->est << ","
	<< (int)(node->est + node->cpu_util) << endl;
    }

    ofs << "% initial block, terminal block" << endl;

    for(i=0; i<conn_n; i++) {
	conn = &blconn[i];
	ofs << conn->pos_s << "," << conn->pos_t << endl;
    }
    ofs.close();
}

static blclst_T *get_farthest_Qnode(blclst_T **Q) {
    blclst_T *node, *max_node=*Q, *prev, *max_prev=NULL;

    if(!max_node) return NULL;
    for(prev=*Q, node=(*Q)->Qnext; node; prev=node, node=node->Qnext) {
	if(node->lst > max_node->lst) { // Need to Improve what's min
	    max_node = node;
	    max_prev = prev;
	}
    }
    if(max_prev) max_prev->Qnext = max_node->Qnext;
    else *Q = max_node->Qnext;
    return max_node;
}

static void bltmp_free_stedges(blclst_T *stnode) {
    blconn_T *conn, *next_conn;

    for(conn=stnode->conn_s; conn; conn=next_conn) {
	next_conn = conn->next_s;
	free(conn);
    }
    for(conn=stnode->conn_t; conn; conn=next_conn) {
	next_conn = conn->next_t;
	free(conn);
    }
}
