#include "bltmp2c.hxx"

static int bltmp_2_1_summarize_alike_groups(int, int);
static void bltmp_2_2_global_alloc(int, int);
static void bltmp_2_3_add_gnum(int, int);
static void bltmp_2_4_core_count(int, int);

static void bltmp_2sub_make_rate_list(blclst_T *, int *);
static int bltmp_get_heaviest_rate(int);
static int bltmp_get_best_fit(int, int);
static void bltmp_core_budget_register(int, int, int);

static int total_cpu_util;
static int *rate_group_list, *rate_sum_cpu_util;
static blcoreb_T **rate_coreb;
static int *core_budget;

static map<block_T::rate_optional, int> m_rate_num;

int bltmp_2_global_mapping(int level, int part_k, 
	blcoreb_T ***rate_coreb_p, int **core_budget_p) {
    int rate_num;

    rate_group_list = (int *)malloc(sizeof(int)*alike_count);
    rate_sum_cpu_util = (int *)malloc(sizeof(int)*alike_count);
    *rate_coreb_p = rate_coreb = (blcoreb_T **)malloc(sizeof(blcoreb_T *)*alike_count);
    *core_budget_p = core_budget = (int *)malloc(sizeof(int)*part_k);

    rate_num = bltmp_2_1_summarize_alike_groups(level, part_k);
    bltmp_2_2_global_alloc(part_k, rate_num);
    bltmp_2_3_add_gnum(level, rate_num);
    bltmp_2_4_core_count(part_k, rate_num);

    free(rate_group_list);
    free(rate_sum_cpu_util);
    return rate_num;
}

static int bltmp_2_1_summarize_alike_groups(int level, int part_k) {
    blclst_T *blclst = hier[level].clst, *clst;
    int clst_n = hier[level].clst_n;
    int gnum=0, ave_cpu_util, rate_num = 0;

    total_cpu_util = 0;
    for(int i=0; i<clst_n; i++) {
	clst = &blclst[i];
	if(clst->level < 0) continue;
	gnum++;
	total_cpu_util += clst->cpu_util;
	bltmp_2sub_make_rate_list(clst, &rate_num);
    }
    ave_cpu_util = total_cpu_util / part_k * 1.05 + 1;  // allow 5% error 
    for(int i=0; i<part_k; i++) {
	core_budget[i] = ave_cpu_util;
    }
// cerr << "LEVEL = " << level << ", clst_n = " << clst_n << ", # of clusters = " 
// << gnum << ", # of alike groups = " << alike_count << ", rate num = " << rate_num 
// << ", total cpu_util = " << total_cpu_util << endl;

    return rate_num;
}

static void bltmp_2_2_global_alloc(int part_k, int rate_num) {
    int sum_cpu_util, cpu_util, num, core;

    while(TRUE) {
	if((num = bltmp_get_heaviest_rate(rate_num)) == -1) break;
	sum_cpu_util = rate_sum_cpu_util[num];
	rate_sum_cpu_util[num] = -1;
	while(sum_cpu_util > 0) {
// cout << "num=" << num << ":" <<sum_cpu_util << endl;
	    core = bltmp_get_best_fit(sum_cpu_util, part_k);
// cout << "--- assiged core " << core << endl;
	    cpu_util =  (sum_cpu_util < core_budget[core]) ? sum_cpu_util : core_budget[core];
	    bltmp_core_budget_register(num, core, cpu_util);
	    sum_cpu_util -= cpu_util;
	    core_budget[core] -= cpu_util;
	}
    }
}

static void bltmp_2_3_add_gnum(int level, int rate_num) {
    blclst_T *blclst = hier[level].clst, *clst;
    int core;

    for(int i=0; i<rate_num; i++) {
        if(rate_coreb[i]->next != NULL) core = -1;   // more than single core
	else core = rate_coreb[i]->core;
	for(int pos=rate_group_list[i]; pos!=-1; pos=clst->tmp) {
	    clst = &blclst[pos];
	    clst->g_num = i;
	    clst->core = core;
	}
    }
}

static void bltmp_2_4_core_count(int part_k, int rate_num) {
    int core_count[part_k];
    blcoreb_T *coreb;

    for(int i=0; i<part_k; i++) core_count[i] = 0;
    for(int i=0; i<rate_num; i++) {
        if(rate_coreb[i]->next == NULL) continue;   // single core
	for(coreb=rate_coreb[i]; coreb; coreb=coreb->next)
	    core_count[coreb->core]++;
    }
    for(int i=0; i<part_k; i++)
	if(core_count[i] >= 2) core_budget[i] /= core_count[i];
}

static void bltmp_2sub_make_rate_list(blclst_T *clst, int *rate_num) {
    int i;
    static int norate_num = -1;
    blclst_T *node = bltmp_get_block_node(clst);

    if(!bltmp_has_effective_rate(node)) {
	if(norate_num != -1) {
	    i = norate_num;
	} else {
	    i = norate_num = (*rate_num)++;
	    rate_group_list[i] = -1;
	    rate_sum_cpu_util[i] = 0;
	    rate_coreb[i] = NULL;
	}
    } else if(m_rate_num.find(*clst->alike_type->rate) != m_rate_num.end()) {
	i = m_rate_num[*clst->alike_type->rate];
    } else {
	m_rate_num[*clst->alike_type->rate] = i = (*rate_num)++;
	rate_group_list[i] = -1;
	rate_sum_cpu_util[i] = 0;
	rate_coreb[i] = NULL;
    }
    clst->tmp = rate_group_list[i];
    rate_group_list[i] = clst->pos;
    rate_sum_cpu_util[i] += clst->cpu_util;
// {
// blclst_T* node = bltmp_get_block_node(clst);
// cout << bltmp_get_name(node) << ": " << i << endl;
// }
}

static int bltmp_get_heaviest_rate(int rate_num) {
    int maxi=-1, max_cpu_util=-1;

    for(int i=0; i<rate_num; i++) {
	if(max_cpu_util < rate_sum_cpu_util[i]) {
	    maxi = i;
	    max_cpu_util = rate_sum_cpu_util[i];
	}
    }
    return maxi;
}

static int bltmp_get_best_fit(int budget, int part_k) {
    int core, x;
    int best_plus_core=-1, best_plus_budget=total_cpu_util;
    int best_minus_core=-1, best_minus_budget=-total_cpu_util;

    for(core=0; core<part_k; core++) {
	x = budget - core_budget[core];
	if(x <= 0) {
	    if(x > best_minus_budget) {
		best_minus_core = core;
		best_minus_budget = x;
	    }
	} else {
	    if(x < best_plus_budget) {
		best_plus_core = core;
		best_plus_budget = x;
	    }
	}
    }
    if(best_minus_core < 0) return best_plus_core;
    return best_minus_core;
}

static void bltmp_core_budget_register(int num, int core, int cpu_util) {
    blcoreb_T *coreb = (blcoreb_T *)malloc(sizeof(*coreb));

// cout << "num=" << num << ", core=" << core << ", cpu_util=" << cpu_util << endl;
    coreb->core = core;
    coreb->budget = cpu_util;
    coreb->next = rate_coreb[num];
    rate_coreb[num] = coreb;
}
