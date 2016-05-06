#include "BLGraph.hxx"

#include <vector>
#include <iostream>
// #include <cstring>

#include <unistd.h>

using namespace std;
using namespace SimulinkModel;
using namespace SimulinkModel::XSD;
using namespace Simulink;
using namespace Simulink::XML;

using namespace BLG;

#define FILENAME_LEN 1024
#define MAX_CNT 100

void print_usage(char *exec_name);

int main(int argc, char *argv[])
{
  int cnt = 0;
  char filename[FILENAME_LEN];
  string savefile;
  unsigned int mode = 0;
  int c;
  while( (c = getopt(argc, argv, "bchnp")) != -1){
    switch(c){
    case 'c':
      mode += BLGraph::DDF_COLORED_NODE;
      break;
    case 'b':
      mode += BLGraph::DDF_PRINT_BLG_ID;
      break;
    case 'n':
      mode += BLGraph::DDF_PRINT_TASK_NAME;
      break;
    case 'p':
      mode += BLGraph::DDF_PRINT_TASK_PERF;
      break;
    case 'h':
    default:
      print_usage(argv[0]);
      return -1;
    }
  }

  argv += optind - 1;
  argc -= optind - 1;
  
  if(argc >= 2){
    strncpy(filename, argv[1], FILENAME_LEN);
  } else {
    print_usage(argv[0]);
    return -1;
  }
  if(argc >= 3){
    savefile = string(argv[2]);
  }else{
    savefile = string("_blgraph.dot");
  }

  Reader xrd(filename);
  if(!xrd){
    cerr << "Failed loading XML..." << endl;
    return 1;
  }
  BLGraph graph(xrd);

#if 0
  // p_out_edgeをたどりつづけるテスト
  vector<blnode_T*> node_list(graph.getNodeVector());
  blnode_T *node = node_list[0];
  cout << "node: " << node->p_block->name() << endl;
  cout << " in_addr: " << node->p_in_edge << endl;
  cout << "out_addr: " << node->p_out_edge << endl;
  while(node->p_out_edge != NULL && cnt++ < MAX_CNT){
    node = node->p_out_edge->p_t_node;
    cout << "node: " << node->p_block->name() << endl;
  };
#endif
#if 0
  // 親子関係の確認用
  vector<blnode_T*> node_list(graph.getNodeVector());
  for(unsigned int i = 0; i < node_list.size(); i++){
    blnode_T *node = node_list[i];
    cout << "node" << endl
	 << "  name: " << node->p_block->name() << endl
	 << "  blocktype: " << node->p_block->blocktype() << endl
	 << "  index: " << node->index << endl;
    if(node->p_parent)
      cout << "    parent: " << node->p_parent->p_block->name() << endl;
    if(node->p_sibling)
      cout << "    sibling: " << node->p_sibling->p_block->name() << endl;
    if(node->p_child)
      cout << "    child: " << node->p_child->p_block->name() << endl;
  }
#endif
  
#ifdef __BLG_WITH_GRAPHVIZ__
  graph.dumpDotFile(savefile, mode);
#endif
}

void print_usage(char *exec_name)
{
  cout << "Usage: " << exec_name << " [-bcnp] <in.xml> [out.dot]" << endl
       << "\t-b " << "Print task BLGraph id in nodes" << endl
       << "\t-c " << "Coloring nodes by peinfo" << endl
       << "\t-n " << "Print task Name in nodes" << endl
       << "\t-p " << "Print task Performance in nodes" << endl
       << "\t-h "  << "Print usage and exit" << endl;
}
