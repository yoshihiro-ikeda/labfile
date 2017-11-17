
//#include "dfihs.hxx"

//#include "blg_ctrl.hxx"

#include "BLGraph.hxx"
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include <algorithm>

#include <xercesc/dom/DOM.hpp>

#include <unistd.h>

using namespace std;
using namespace SimulinkModel;
using namespace SimulinkModel::XSD;
using namespace Simulink;
using namespace Simulink::XML;

using namespace BLG;

// nodeを受け取りそのブロックのコストを返す
// 入力のflagが1の時UnitDelayが探索開始ブロックとして認識しパフォーマンスをtaskを採用
// 0の時は探索終了ブロックとし、パフォーマンスをupdateを採用
int getNodePerformance(blnode_T *node,int flag)
{
  int cost = 0;		//コストを返すための変数

  block_T::performance_sequence ps;
  block_T::performance_iterator pi;

  ps = node->p_block->performance();

  if(ps.begin() == ps.end()){//performanceタグがなかった場合
    if(node->p_block->blocktype() == "Inport"
    	|| node->p_block->blocktype() == "Outport"
    	|| node->p_block->blocktype() == "ToWorkspace"){
      cost = 0;;
    }else{
      cost = 100;
    }
  }else{//performanceタグがあった場合
    if(node->p_block->blocktype() == "UnitDelay"){
      if(flag == 1){
	for(pi = ps.begin();pi != ps.end();pi++){
	  if(pi->type() == "task"){
	    cost = (int)(pi->typical());
	    break;
	  }
	}
      }else if(flag == 0){
	for(pi = ps.begin();pi != ps.end();pi++){
	  if(pi->type() == "update"){
	    cost = (int)(pi->typical());
	    break;
	  }
	}
      }
    }else{
      for(pi = ps.begin();pi != ps.end();pi++){
	if(pi->type() == "task"){
	  cost = (int)(pi->typical());
	  break;
	}
      }
    }
  }
  return cost;
}

////////////////////
// mergeSubsystemBlock
// [概要] 階層が離れた時の優先度付ができないため、サブシステム単位でまとめるための関数
// [引数] BLGraphと指定の階層(string)
// [返り値] BLGraph
// [備考] 指定された階層上に存在するサブシステム内の処理をすべてマージ
//        処理量のみをノードにつける方針
//        この関数をdeleteIOportBlockInSubsystemの先に実行すること
BLGraph mergeSubsystemBlock(BLGraph graph,string subsys)
{
	//手順
	//1:選択されたサブシステムを探索
	//2:その中のノードを探索(map<blnode_T*,blnode_T*>使用)
	//3:コストを足し算
	//4:パフォーマンスタグの作成
	//5:サブシステム内の接続情報を復元(サブシステム内のInportとOutportより)
	//6:新しくサブシステムを作り直し(blxml上のブロックから作り直し)
	//7:BLGraph上からマージブロックを削除
	//8:自ループを排除

	int sNameSize = (int)subsys.size();

	vector<blnode_T*> nodeList = graph.getNodeVector();
	vector<blnode_T*>::iterator bi;

	vector<blnode_T*> mergeNodeList;
	blnode_T* sNode;
	double stCost = 0,sbCost = 0,swCost = 0;

	//手順1,2,3
	for(bi = nodeList.begin();bi != nodeList.end();bi++){
		blnode_T* tmpNode = *(bi);
		if(tmpNode->p_block->name() == subsys){
			sNode = tmpNode;
		}
		else if(strncmp((tmpNode->p_block->name()).c_str(),subsys.c_str(),sNameSize)==0){
			mergeNodeList.push_back(*bi);
			stCost += getNodePerformance(*bi,1);
			//best,worstに関する処理も追加する必要あり
		}
	}

	//手順4
	block_T::performance_sequence ps = sNode->p_block->performance();
	SimulinkModel::XSD::performance_T nodePerformance("task",1,stCost,1);
	//nodePerformance->typical(stCost);
	ps.push_back(nodePerformance);
	sNode->p_block->performance(ps);


	//set_performance(sNode->p_block->name(),"task",1,1,1);

	//手順5
	//手順5-1:サブシステム内にInport-Outportブロックを探索
	//手順5-2:それぞれの接続元、接続先をsNodeに接続
	bledge_T *inEdge,*outEdge;
	blnode_T *srcNode,*dstNode;
	for(bi = mergeNodeList.begin();bi != mergeNodeList.end();bi++){
		blnode_T* tmpNode = *(bi);
		if(tmpNode->p_block->blocktype() == "Inport"){
			inEdge = tmpNode->p_in_edge;
			while(inEdge != NULL){
				srcNode = inEdge->p_s_node;
				graph.createEdge(srcNode,sNode);
				inEdge = inEdge->p_in_edge;
			}
		}else if(tmpNode->p_block->blocktype() == "Outport"){
			outEdge = tmpNode->p_out_edge;
			while(outEdge != NULL){
				dstNode = outEdge->p_t_node;
				graph.createEdge(sNode,dstNode);
				outEdge = outEdge->p_out_edge;
			}
		}
	}

	//手順7
	for(bi = mergeNodeList.begin();bi != mergeNodeList.end();bi++){
		blnode_T* tmpNode = *bi;
		cout << tmpNode->p_block->name() << endl;
		graph.deleteNode(tmpNode);
	}

	//手順8
	outEdge = sNode->p_out_edge;
	while(outEdge != NULL){
		dstNode = outEdge->p_t_node;
		if(dstNode == sNode){
			graph.deleteEdge(outEdge);
		}
		outEdge = outEdge->p_out_edge;
	}
	graph.dumpDotFile("change_mergeSubsystem.dot");

	return graph;
}

////////////////////
// chooseMergeSubsystem
// [概要] mergeSubsystemBlockを適用するブロックを選定
// [引数] BLGraphと指定の階層(string)
// [返り値] BLGraph
// [備考] 長周期タスクと短周期タスク
//        yamlファイルをパースする必要があるのでyaml-cpp/yaml.hをインクルードする必要がある
BLGraph chooseMergeSubsystem(BLGraph graph,string filename)
{
	vector<string> atomicssList;
	vector<string>::iterator ali;
	//ファイルの読み込み
	ifstream ifs("./models/atomicsstest/atomicsubsystemlist.csv");
	if(!ifs){
			cout<<"入力エラー";
			exit(1);
	}
	cout << "yomikomi" << endl;
	//csvファイルを1行ずつ読み込む
	string str;
	while(getline(ifs,str)){
		string token;
		istringstream stream(str);

		//1行のうち、文字列とコンマを分割する
		while(getline(stream,token,',')){
			//すべて文字列として読み込まれるため
			//数値は変換が必要
			atomicssList.push_back(token);
		}
	}
	for(ali = atomicssList.begin();ali != atomicssList.end();ali++){
		graph = mergeSubsystemBlock(graph,*ali);
	}
  return graph;
}

//kari
int main(int argc,char *argv[])
{
	char filename[64];
	cout << "start reading." << endl;
  cout << "filename is " << argv[1] << endl;
  strcpy(filename,argv[1]);
  Reader xrd(filename); //XMLファイルを読み込み
  cout << "finish reading XML." << endl;

  BLGraph graph(xrd);
	string configfile = "graphopt.yaml";
  graph = chooseMergeSubsystem(graph,configfile);

	graph.dumpDotFile("change_mergeSubsystem_finalize.dot");

  return 0;
}
