#include "bltmp2c.hxx"

static void bltmp_3_0_preprocess(blparams_T *, int *);
static void bltmp_3_1_make_task_mapping_group(blparams_T *);
static void bltmp_3_2_make_graph(blparams_T *);
static int bltmp_3_3_calc_path_length(blparams_T *);
static void bltmp_3_4_calc_rev_path(blparams_T *, int);
static void bltmp_3_5_calc_budget(blparams_T *, int);
static void bltmp_3_6_do_mapping(blparams_T *, int);

static void bltmp_free_params(blparams_T *);

void bltmp_3_local_mapping(int level, int g_num, 
			blcoreb_T **rate_coreb, int *core_budget) {
    for(int i=0; i<g_num; i++) {
	if(rate_coreb[i]->next == NULL) continue;
	blparams_T *params = (blparams_T *)malloc(sizeof(blparams_T));
	params->level = level;
	params->g_num = i;
	params->coreb = rate_coreb[i];
	params->stnode = (blclst_T *)malloc(sizeof(blclst_T));
	bltmp_3_0_preprocess(params, core_budget);
	bltmp_3_1_make_task_mapping_group(params);
	bltmp_3_2_make_graph(params);
	int max_est = bltmp_3_3_calc_path_length(params);
// cout << "max earliest start time: " << max_est << endl;
	bltmp_3_4_calc_rev_path(params, max_est);
	bltmp_3_5_calc_budget(params, max_est);
	bltmp_3_6_do_mapping(params, W_OVERHEAD);
	bltmp_free_params(params);
    }
    free(*rate_coreb);
    free(core_budget);
}

static void bltmp_3_0_preprocess(blparams_T *params, int *core_budget) {
    int core_n = 0, i, max_budget = 0;
    blcoreb_T *coreb;
    for(coreb=params->coreb; coreb; coreb=coreb->next) {
	core_n++;
	if(max_budget < coreb->budget) max_budget = coreb->budget;
    }
    params->core_trans = (int *)malloc(sizeof(int)*core_n);
    params->core_load = (int *)malloc(sizeof(int)*core_n);
    for(coreb=params->coreb, i=0; coreb; coreb=coreb->next, i++) {
	params->core_trans[i] = coreb->core;
	params->core_load[i] = max_budget - coreb->budget - core_budget[coreb->core];
	if(params->core_load[i] < 0) params->core_load[i] = 0;
// cout << "core_trans[" << i << "]=" << params->core_trans[i] << endl;
// cout << "core_load[" << i << "]=" << params->core_load[i] << endl;
    }
    params->part_n = core_n;
}

static void bltmp_3_1_make_task_mapping_group(blparams_T *params) {
    blclst_T *blclst = hier[params->level].clst;
    int clst_n = hier[params->level].clst_n;
    int num_n=0, prev;

    for(int i=0; i<clst_n; i++) {
	if(blclst[i].level < 0) continue;
	if(blclst[i].g_num != params->g_num) continue;
	num_n++;
	blclst[i].num = num_n;
	if(num_n == 1) {
	    params->first = i;
	} else {
	    blclst[prev].next_pos = i;
	}
	prev = i;
    }
    blclst[prev].next_pos = -1;
    params->tmp_n = num_n;
}

static void bltmp_3_2_make_graph(blparams_T *params) {
    blclst_T *blclst = hier[params->level].clst, *node;
    blconn_T *conn, *new_conn;

    params->stnode->conn_s = params->stnode->conn_t = NULL;
    for(int pos=params->first; pos!=-1; pos=node->next_pos) {
	node = &blclst[pos];
	node->count_s = node->count_t = 0;

// {blclst_T *tc = bltmp_get_block_node(&blclst[pos]);
// cout << tc->u.bl.org->p_block->name() << ":" << tc->u.bl.order << endl;}

	/* add snode */
	for(conn=node->conn_t; conn; conn=conn->next_t) {
	    if(conn->flag == FALSE) continue;
	    break;
	}
	if(!conn) {
	    new_conn = (blconn_T *)malloc(sizeof(*new_conn));
	    new_conn->pos_s = -1;
	    new_conn->pos_t = pos;
	    new_conn->next_s = params->stnode->conn_s;
	    params->stnode->conn_s = new_conn;
// cout << "add snode" << endl;
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
	    new_conn->next_t = params->stnode->conn_t;
	    params->stnode->conn_t = new_conn;
// cout << "add tnode" << endl;
	}
    }
    for(int pos=params->first; pos!=-1; pos=node->next_pos) {
	node = &blclst[pos];

	/* count snode */
	for(conn=node->conn_s; conn; conn=conn->next_s) {
	    if(conn->flag == FALSE) continue;
	    if(blclst[conn->pos_t].g_num != params->g_num) continue;
	    blclst[conn->pos_t].count_s++;
	}
	/* count tnode */
	for(conn=node->conn_t; conn; conn=conn->next_t) {
	    if(conn->flag == FALSE) continue;
	    if(blclst[conn->pos_s].g_num != params->g_num) continue;
	    blclst[conn->pos_s].count_t++;
	}
    }
}

static int bltmp_3_3_calc_path_length(blparams_T *params) {
    blclst_T *blclst=hier[params->level].clst, *node, *node0, *Q=NULL;
    blconn_T *conn;
    int est, max_est = 0;

// cout << "start calculate forward critical path" << endl;

    for(int pos=params->first; pos!=-1; pos=node->next_pos) {
	node = &blclst[pos];
	node->tmp = node->count_s;
	node->est = 0;
    }
    for(conn=params->stnode->conn_s; conn; conn=conn->next_s) {
	node = &blclst[conn->pos_t];
	node->Qnext = Q;
	Q = node;
    }
    while((node0=Q)!=NULL) {
// cout << "eval " << node0->pos << endl;
/*
blclst_T *tc = bltmp_get_block_node(&blclst[node0->pos]);
cout << node0->pos << "(" << tc->u.bl.org->p_block->name() 
<< "):" << tc->u.bl.org->p_block->blocktype() << ":" <<
node0->cpu_util << ":" << node0->est << endl;
*/
	Q = node0->Qnext;
	est = node0->est + node0->cpu_util;
	if(max_est < est) max_est = est;	// may care about update cost
	for(conn=node0->conn_s; conn; conn=conn->next_s) {
	    if(conn->flag == FALSE) continue;
	    node = &blclst[conn->pos_t];
	    if(node->g_num != params->g_num) continue;
	    if(node->est < est) node->est = est;
	    if((--node->tmp) <= 0) {
		node->Qnext = Q;
		Q = node;
	    }
	}
    }
    return max_est;
}

static void bltmp_3_4_calc_rev_path(blparams_T *params, int max_est) {
    blclst_T *blclst=hier[params->level].clst, *node, *node0, *Q=NULL;
    blconn_T *conn;
    int lst;

// cout << "start calculate backward critical path" << endl;

    for(int pos=params->first; pos!=-1; pos=node->next_pos) {
	node = &blclst[pos];
	node->tmp = node->count_t;
	node->lst = max_est;
    }
    for(conn=params->stnode->conn_t; conn; conn=conn->next_t) {
	node = &blclst[conn->pos_s];
	node->lst -= node->cpu_util;	// may care about update cost
	node->Qnext = Q;
	Q = node;
    }
    while((node0=Q)!=NULL) {
/*
blclst_T *tc = bltmp_get_block_node(&blclst[node0->pos]);
cout << node0->pos << "(" << tc->u.bl.org->p_block->name() 
<< "):" << tc->u.bl.org->p_block->blocktype() << ":" <<
node0->cpu_util << ":" << node0->lst << endl;
*/
	Q = node0->Qnext;
	for(conn=node0->conn_t; conn; conn=conn->next_t) {
	    if(conn->flag == FALSE) continue;
	    node = &blclst[conn->pos_s];
	    if(node->g_num != params->g_num) continue;
	    lst = node0->lst - node->cpu_util;
	    if(node->lst > lst) node->lst = lst;
	    if((--node->tmp) <= 0) {
		node->Qnext = Q;
		Q = node;
	    }
	}
    }
}

static void bltmp_3_5_calc_budget(blparams_T *params, int max_est) {
    blclst_T *blclst=hier[params->level].clst, *node_s, *node_t;
    blconn_T *conn0, *conn;
    int budget_s, budget_t, tmp_m=0;

// cout << "start calculate edge budget" << endl;

    for(int pos=params->first; pos!=-1; pos=node_s->next_pos) {
	node_s = &blclst[pos];
	budget_s = node_s->lst - node_s->est;
	for(conn=node_s->conn_s; conn; conn=conn->next_s) {
	    node_t = &blclst[conn->pos_t];
	    if((conn->flag == FALSE) || (node_t->g_num != params->g_num)) {
		budget_t = max_est - node_s->lst - node_s->cpu_util;
	    } else {
		budget_t = node_t->lst - node_t->est;
	    }
	    conn->budget = (budget_s > budget_t) ? budget_s : budget_t;
	    conn->checked = -1;
	}
 	for(conn0=node_s->conn_s; conn0; conn0=conn0->next_s) {
	    if(conn0->checked >= 0) continue;
	    if(blclst[conn0->pos_t].g_num != params->g_num) continue;
	    conn0->checked = ++tmp_m;
	    for(conn=conn0->next_s; conn; conn=conn->next_s) {
		if(conn->checked >= 0) continue;
		if(conn->budget == conn0->budget) conn->checked = tmp_m;
	    }
	}
    }
    params->tmp_m = tmp_m;
}

static void bltmp_3_6_do_mapping(blparams_T *params, int overhead) {
    blclst_T *blclst = hier[params->level].clst;
    // int clst_n = hier[params->level].clst_n;
    blconn_T *conn, *conn0;
    int next_pos, ne, weight;
    char f_name[TMPFILENAME_LEN], f_name1[TMPFILENAME_LEN];
    char f_name2[TMPFILENAME_LEN];
    char tmp_command[TMPFILENAME_LEN];

    if(params->tmp_n == 0) return;

    time_t timer;
    time(&timer);
    struct tm *date = localtime(&timer);
    sprintf(f_name, "metis%04d%02d%02d%02d%02d%02d.dat", 
	date->tm_year+1900, date->tm_mon+1, date->tm_mday, 
	date->tm_hour, date->tm_min, date->tm_sec);
    sprintf(f_name2, "metis%04d%02d%02d%02d%02d%02d.fix", 
	date->tm_year+1900, date->tm_mon+1, date->tm_mday, 
	date->tm_hour, date->tm_min, date->tm_sec);
    ofstream ofs(f_name);

//    cout << params->tmp_m << " " << params->tmp_n+params->part_n << " 11" << endl;
    ofs << params->tmp_m << " " << params->tmp_n+params->part_n << " 11" << endl;

    for(int pos=params->first; pos!=-1; pos=next_pos) {
	next_pos = blclst[pos].next_pos;
	ne = -1;
 	for(conn0=blclst[pos].conn_s; conn0; conn0=conn0->next_s) {
	    if(conn0->checked <= ne) continue;
	    if(blclst[conn0->pos_t].g_num != params->g_num) continue;
	    ne = conn0->checked;
	    weight = (overhead - conn0->budget) * conn0->w;
	    if(weight < 1) weight = 1;

//	    cout << weight << " " << blclst[pos].num << " " 
//		<< blclst[conn0->pos_t].num;
	    ofs << weight << " " << blclst[pos].num << " " 
		<< blclst[conn0->pos_t].num;

	    for(conn=conn0->next_s; conn; conn=conn->next_s) {
		if(conn->checked != ne) continue;
		if(blclst[conn->pos_t].g_num != params->g_num) continue;
//		cout << " " << blclst[conn->pos_t].num;
		ofs << " " << blclst[conn->pos_t].num;
	    }
//	    cout << endl;
	    ofs << endl;
	}
    }
    for(int pos=params->first; pos!=-1; pos=next_pos) {
	next_pos = blclst[pos].next_pos;
	blclst_T *tc = bltmp_get_block_node(&blclst[pos]);
/*
        cout << "% " << blclst[pos].num << ": " 
		<< bltmp_get_name(tc) << endl;
	cout << blclst[pos].cpu_util << endl;
*/
        ofs << "% Block " << blclst[pos].num << "(" 
		<< bltmp_get_name(tc) << ":"
		<< bltmp_get_blocktype(tc) << ")" << endl;
	ofs << blclst[pos].cpu_util << endl;
    }
    for(int i=0; i<params->part_n; i++) {
/*
            cout << "% load for core " << i << endl;
	    cout << params->core_load[i] << endl;
*/
            ofs << "% Load for core " << i << endl;
	    ofs << params->core_load[i] << endl;
    }
    ofs.close();

    ofs.open(f_name2);
    for(int i=0; i<params->tmp_n; i++) ofs << "-1" << endl;
    for(int i=0; i<params->part_n; i++) ofs << i << endl;
    ofs.close();

    sprintf(tmp_command, "/usr/local/bin/shmetis %s %s %d 5", f_name, 
	f_name2, params->part_n);
cerr << tmp_command << endl;
    system(tmp_command);

    sprintf(f_name1, "%s.part.%d", f_name, params->part_n);
    ifstream fin(f_name1);
    for(int pos=params->first; pos!=-1; pos=next_pos) {
	next_pos = blclst[pos].next_pos;
	int core;
	fin >> core;
	blclst[pos].core = params->core_trans[core];
    }
    fin.close();
}

static void bltmp_free_params(blparams_T *params) {
    blconn_T *conn, *next_conn;

    free(params->core_trans);
    free(params->core_load);
    for(conn=params->stnode->conn_s; conn; conn=next_conn) {
	next_conn = conn->next_s;
	free(conn);
    }
    for(conn=params->stnode->conn_t; conn; conn=next_conn) {
	next_conn = conn->next_t;
	free(conn);
    }
    free(params->stnode);
    // free struct bltmp_core_budget *coreb;
}
