#include "BLGraph.hxx"

#include <vector>
#include <iostream>
#include <fstream>

#include <getopt.h>
#include <string.h>

using namespace std;
using namespace SimulinkModel;
using namespace SimulinkModel::XSD;
using namespace Simulink;
using namespace Simulink::XML;

using namespace BLG;

#define MAX_CNT 100

int main(int argc, char *argv[])
{
  ostream wstream(cout.rdbuf());
  ofstream wfstream;

  if (argc < 2){
    cerr << "Usage: " << argv[0]
	 << " input.xml [output.hgr]" << endl;
  }

  Reader xrd(argv[1]);
  if(!xrd){
    cerr << "Failed loading XML..." << endl;
    return 1;
  }

  if ( argc >= 3){
    if(strcmp(argv[2], "-") != 0){
      wfstream.open(argv[2], fstream::out);
      wstream.rdbuf(wfstream.rdbuf());
    }
  }   

  BLGraph graph(xrd);

  vector<blnode_T*> node_list(graph.getNodeVector());
  int node_n = node_list.size();  // nodeの数は、vectorクラスのsizeメソッドで得られる。
  int h_edge_n = 0;
  map<blnode_T*, int> nodemap;// ノードへのポインタからインデックスを探す連想配列
  for(int i = 0; i < node_n; i++){
    if(node_list[i]->p_out_edge != NULL) h_edge_n++;//出力エッジが一本でもあればハイパーエッジを作成
    nodemap[node_list[i]] = i;// 連想配列のテーブル作成
  }

  wstream << h_edge_n << " " << node_n << endl;

  for(int i = 0; i < node_n; i++){
    bledge_T *out_ptr = node_list[i]->p_out_edge;// 最初のout_edgeを取得
    if (out_ptr == NULL) continue;
    wstream << i+1;
    do{
      wstream << " " << nodemap[out_ptr->p_t_node]+1;// 終点側ノードの番号を追記
      // ↑連想配列に対して、ノードのポインタを[]で与えることによって、インデックスが得られる。
    } while( (out_ptr = out_ptr->p_out_edge) != NULL );
    wstream << endl;
  }
  
#ifdef __BLG_WITH_GRAPHVIZ__
  graph.dumpDotFile("_blgraph.dot");
#endif

  wfstream.close();
}
