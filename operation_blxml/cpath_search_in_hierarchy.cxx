//入力：探索したいサブシステム
//出力：クリティカル・パス及び分割候補
//　　　コスト的な分割地点、サブシステムの境界、レートの変わる場所等
//使い方：./cpath_search_in_hierarchy <BLXML-file> <探索したいサブシステム>
//または：./cpath_search_in_hierarchy <BLXML-file> <モデル名(.slxなし)>

#include "blg_ctrl.hxx"

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include <xercesc/dom/DOM.hpp>
#include <unistd.h>

extern cpList cplist;

int main(int argc, char *argv[])
{
	if(argc<2)
		cout << "usage:./cpath_search_in_hierarchy <BLXML-file> <modelname(no .slx)>" << endl;
	
  char filename[64];
	
	//探索される階層
	string subsys;
	int subsys_size;
	
  blnode_T *node;
  
  //全体のnode list
	vector<blnode_T*> node_list;
	int node_list_size;
  
  vector<blnode_T*> result_nodes;
  vector<blnode_T*> candidate_list;
	
  vector<string>::iterator blki;
  
  //クリティカル・パスのリストの初期化
	cplist.initialize();

  cout << "start reading." << endl;
  cout << "filename is " << argv[1] << endl;
  strcpy(filename,argv[1]);
  Reader xrd(filename); 
  cout << "finish reading XML." << endl;
	
  BLGraph graph(xrd); //BLGragh作成完了
  cout << "finish creating graph." << endl;

  //nodeリストを取得(node_listはグローバル変数なことに注意)
  node_list = graph.getNodeVector();   
  node_list_size = (int)node_list.size();
  
  //各始点ブロックごとにコストを初期化
  node = node_list[0];
  for(int i = 0;i != node_list_size;i++){
    node_list[i]->p_block->peinfo("-1");
  }
  
  int subsystemFlag = 1;
  //入力のサブシステムを探してCP探索開始
  for(int i = 0;i < node_list_size;i++){
    if(node_list[i]->p_block->name() == argv[2]){
      node = node_list[i];
      subsys = node->p_block->name();
      subsys_size = subsys.size();
      cout << subsys << ":ok" << endl;
      //ここで該当サブシステム以外のブロックをすべて削除
      graph = selectSubsystem(graph,subsys);
      search_critical_path(graph,node,subsys);
      subsystemFlag = 0;
      break;
    }
  }
  
  //サブシステム指定されていない場合
  if(subsystemFlag == 1){
		subsys = argv[2];
		subsys_size = subsys.size();
		search_critical_path(graph,node,subsys);
  }

	cplist.printCpList();

	cout << "-----result-----" << endl;
	criticalPathNode tmp(0);
	tmp = cplist.getCpList(0);
	cout << "cost:" << tmp.get_cost() << endl;
	tmp.printNodeList();
	
	int edgeNum = cplist.printHalfSignalLine(0);
	cout << edgeNum << endl;
	graph = cplist.cuttingEdgeOnCriticalPath(graph,0,edgeNum);
	
	//最上位のクリティカル・パスのコストを保存
	//探索したクリティカルパスのコストがそれの1/4以下なら探索を打ち切り
	int mostLongPathCost = cplist.getCpList(0).get_cost()/4;
	
	//二回目
	for(int ii = 0;ii < 9;ii++){
		//nodeリストを取得(node_listはグローバル変数なことに注意)
		node_list = graph.getNodeVector();   
		node_list_size = (int)node_list.size();
		
		//各始点ブロックごとにコストを初期化
		node = node_list[0];
		for(int i = 0;i != node_list_size;i++){
			node_list[i]->p_block->peinfo("-1");
		}
		cplist.initialize();
		
		//入力のサブシステムを探してCP探索開始
		for(int i = 0;i < node_list_size;i++){
			if(node_list[i]->p_block->name() == argv[2]){
				node = node_list[i];
				subsys = node->p_block->name();
				subsys_size = subsys.size();
				cout << subsys << ":ok" << endl;
				//ここで該当サブシステム以外のブロックをすべて削除
				graph = selectSubsystem(graph,subsys);
				search_critical_path(graph,node,subsys);
				subsystemFlag = 0;
				break;
			}
		}
		
		//サブシステム指定されていない場合
		if(subsystemFlag == 1){
			subsys = argv[2];
			subsys_size = subsys.size();
			search_critical_path(graph,node,subsys);
		}

		//cplist.printCpList();
		if(cplist.getCpList(0).get_cost() < mostLongPathCost)
			break;
		cout << "-----result-----" << endl;
		cout << ii+1 << "--------------------------------------------" << endl;
		criticalPathNode tmp2(0);
		tmp2 = cplist.getCpList(0);
		cout << "cost:" << tmp2.get_cost() << endl;
		tmp2.printNodeList();
		
		edgeNum = cplist.printHalfSignalLine(0);
		graph = cplist.cuttingEdgeOnCriticalPath(graph,0,edgeNum);
	}
	return 0;
}
