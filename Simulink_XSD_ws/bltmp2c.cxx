#include "bltmp2c.hxx"

static void bltmp_4_subsystem_color(int);
static void bltmp_4sub_ss_color(blclst_T *, int, float *);

Reader xrd;
BLGraph *p_graph;
char infile[FILENAME_LEN] = "Fibonacci/Fibonacci_cycles.xml";
char outfile[FILENAME_LEN] = "tmp_results.xml";

int main(int argc, char *argv[])
{
    int level=0, part_k=2, g_num, err, *core_budget;
    blcoreb_T **rate_coreb;

    err = bltmp_0_read_blgraph(argc, argv, &part_k);
    if(err != 0) return err;
    // 1. clustering (at least atomic) (rate,offset) (switch-case)
    level = bltmp_1_clustering(part_k);
    // 2. global mapping = inter-group (rate, offset) core assigment
    g_num = bltmp_2_global_mapping(level, part_k, &rate_coreb, &core_budget);
    level = bltmp_expand_to_lower(level);
    // 3. local mapping = inner-group core assignment
	// will be (level, group_numer, # of cores assined to the group, core lists)
    bltmp_3_local_mapping(level, g_num, rate_coreb, core_budget);
    level = bltmp_expand_to_lower(level);
    bltmp_4_subsystem_color(part_k);
    // 8. output resultant XML and csv files
    bltmp_8_output();
    // 9. performance evaluation adn output resultant csv file
    bltmp_9_perf_eval(part_k, W_OVERHEAD);
    return 0;
}

int bltmp_0_read_blgraph(int argc, char *argv[], int *part_k) {
  if(argc >= 2) {
    *part_k = atoi(argv[1]);
    if(*part_k <= 0) {
      cerr << "Error: # of partitions" << endl;
      return 1;
    }
  }
  if(argc >= 3) {
    strncpy(infile, argv[2], FILENAME_LEN);
  }
  if(argc >= 4) {
    strncpy(outfile, argv[3], FILENAME_LEN);
  }
  xrd.load_xml(infile);
  if(!xrd){
    cerr << "Failed loading XML..." << endl;
    return 1;
  }
  static BLGraph graph(xrd);
  p_graph = &graph;

  bltmp_0_1_read_blnode();
  bltmp_0_2_subsystem_connect();
  bltmp_0_3_read_bledge();
  bltmp_0_4_rate_propagation();
  bltmp_0_5_calc_alike();
  bltmp_0_6_calc_weights();

  return 0;
}

static void bltmp_4_subsystem_color(int part_k) {
    blclst_T *blclst=hier[0].clst, *node;
    int clst_n = hier[0].clst_n;
    float *core_perf;

    for(int i=0; i<clst_n; i++) {
	node = &blclst[i];
	if(bltmp_is_subsystem(node) == FALSE) continue;
	if(node->u.bl.ss_parent != NULL) continue;
        core_perf = (float *)calloc((part_k+1), sizeof(float));
	bltmp_4sub_ss_color(node, part_k, core_perf);
    }
}

static void bltmp_4sub_ss_color(blclst_T *node0, int part_k, float *core_perf0) {
    blclst_T *node;
    float *core_perf, max_perf, max_core;

    core_perf = (float *)malloc((part_k+1)*sizeof(float));
    for(node=node0->u.bl.ss_child; node; node=node->u.bl.ss_sibling) {
	if(bltmp_is_subsystem(node)) {
	    for(int k=0; k<=part_k; k++) core_perf[k] = 0.0;
	    bltmp_4sub_ss_color(node, part_k, core_perf);
	    for(int k=0; k<=part_k; k++) core_perf0[k] = core_perf[k];
	} else if((node->core < 0) || (node->core >= part_k)) {
	    core_perf0[part_k] += node->perf;
	} else {
	    core_perf0[node->core]++;
	}
    }
    max_perf = core_perf0[part_k];
    max_core = -1;
    for(int k=0; k<part_k; k++) {
        if(max_perf < core_perf0[k]) {
	    max_perf = core_perf0[k];
	    max_core = k;
        }
    }
    if(max_core != -1) {
        node0->core = max_core;
    } else {
cerr << "NO CORE!" << endl;
    }
}

