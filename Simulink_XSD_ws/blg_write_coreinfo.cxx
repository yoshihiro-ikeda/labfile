#include "BLGraph.hxx"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <getopt.h>
#include <string.h>

using namespace std;
using namespace SimulinkModel;
using namespace SimulinkModel::XSD;
using namespace Simulink;
using namespace Simulink::XML;

using namespace BLG;

#define MAX_CNT 100

#ifndef CORES
#define CORES 4
#endif

int main(int argc, char *argv[])
{
  ostream wstream(cout.rdbuf());
  ofstream wfstream;

  if (argc < 2){
    cerr << "Usage: " << argv[0]
	 << " input.xml [output.xml]" << endl;
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
  //  map<blnode_T*, int> nodemap;// ノードへのポインタからインデックスを探す連想配列
  for(int i = 0; i < node_n; i++){
    if(node_list[i]->p_block != NULL){
      stringstream s;
      s << i%CORES;
      
      node_list[i]->p_block->peinfo(s.str());
    }
    //    nodemap[node_list[i]] = i;// 連想配列のテーブル作成
  }

#ifdef __BLG_WITH_GRAPHVIZ__
  graph.dumpDotFile("_blgraph.dot");
#endif
  xml_schema::namespace_infomap map;
  map["SM"].name   = "http://example.com/SimulinkModel";
  map["SM"].schema = "SimulinkModel.xsd";
  blocks_T xml = xrd.xml_blocks();
  blocks(wstream, xml, map);
  
  wfstream.close();
}
