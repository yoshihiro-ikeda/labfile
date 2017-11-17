//df_ihs法において最初のBus関連ブロックを削除するための関数群
#include "dfihs.hxx"

////////////////////
// deleteBus
// [概要] 入力のBLGraphからBus関連のブロックを削除し、ノード依存関係を解決
// [引数] BLGraph
// [返り値] BusノードのないBLGraph
// [備考]
// クリティカル・パス探索を行う前に実行してください。
BLGraph deleteBus(BLGraph graph)
{
  int i,j;//ループ用変数
  blnode_T *node,*next_node,*search_node,*result_node;
  bledge_T *out_edge;

  //全体のnode list
	vector<blnode_T*> node_list;
	vector<blnode_T*>::iterator node_itr;
	int node_list_size;

	vector<bledge_T*> edge_list;
	vector<bledge_T*>::iterator edge_itr;
	int edge_list_size;

	block_T::input_sequence is,is_search;
  block_T::input_iterator ii,ii_search;

	block_T::output_sequence os,os_search;
  block_T::output_iterator oi,oi_search;

  ioport_T::connect_sequence cs;
  ioport_T::connect_iterator ci;

  //buscreatorへ接続している信号線
  //vector<string> candidate_signal;
  //buscreatorに接続している信号線
  string bus_signal;
  //busselectorの出力する信号線
  string connect_signal;
  //busを通して接続するブロック名
  string result_blk;

  stringstream selsig;

  /* 多重ループ離脱用 */
  int csInputFlag = 0;
  int csOutputFlag = 0;

  node_list = graph.getNodeVector();
  node_list_size = (int)node_list.size();
  edge_list = graph.getEdgeVector();
  edge_list_size = (int)edge_list.size();

  //出力先がbuscreatorに接続されているノードを抽出
  for(i = 0;i < node_list_size;i++){
		node = node_list[i];
		out_edge = node->p_out_edge;
		if(out_edge == NULL || node->p_block->blocktype() == "BusCreator")
			continue;
		while(out_edge != NULL){
			next_node = out_edge->p_t_node;
			if(next_node->p_block->blocktype() == "BusCreator"){
				//cout << "taisyo:" << node->p_block->name() << endl;
				//<output>内のlineを取得（outputタグを複数持つ場合を留意）
				os = node->p_block->output();
				for(oi = os.begin();oi != os.end();oi++){
					cs = oi->connect();
					for(ci = cs.begin();ci != cs.end();ci++){
						if(ci->block() == next_node->p_block->name()){
							bus_signal = oi->line();
							cout << "first point:" << bus_signal << endl;
							break;
						}
					}
					//buscreator内の<output>内のselectedsignalが上と同じものを探索しそこのlineを取得
					/* cs_flag:探索終了時ループを抜けるためのフラグ */
					csOutputFlag = 0;
					for(j = 0;j < node_list_size;j++){
						search_node = node_list[j];
						if(search_node->p_block->blocktype() == "BusSelector"){
							os_search = search_node->p_block->output();
							for(oi_search = os_search.begin();oi_search != os_search.end();oi_search++){
								selsig.str("");
								selsig << oi_search->selectedsignal();
								if(selsig.str() == bus_signal){
									connect_signal = oi_search->line();
									cout << "second point:" << connect_signal << endl;
									csOutputFlag = 1;
									break;
								}
							}
						}
						if(csOutputFlag==1){
							break;
						}
					}
					//そのlineを<input>内のlineとして持つブロックを探索
					/* cs_flag:探索終了時ループを抜けるためのフラグ */
					csInputFlag = 0;
					for(j = 0;j < node_list_size;j++){
						result_node = node_list[j];
						is = result_node->p_block->input();
						for(ii = is.begin();ii != is.end();ii++){
							if(ii->line() == connect_signal){
								result_blk = result_node->p_block->name();
								cout << "third point:" << result_blk << endl;
								csInputFlag = 1;
								break;
							}
						}
						if(csInputFlag)
							break;
					}
					// not found
					if(j == node_list_size){
						graph = deleteEdgeBetNode(graph,node,next_node);
						continue;
					}
					cout << node->p_block->name() << "->" << result_blk << endl;
					/*
					 * この地点の情報
					 * node:bus_creatorにつながっているnode
					 * next_node:bus_creator
					 * search_node:bus_selector
					 * result_node:bus_selectorから信号線を選択しているnode
					 */
					/* Bus-Creatorに接続されている信号線を削除 */
					graph = deleteEdgeBetNode(graph,node,next_node);
					/* Bus-CreatorからBus-Selectorにを介さずに接続されている場合の対処
					 * →→Bus信号に対して処理を行えるブロックが今のところない
					 */
					//graph = reconnectNodes(graph,node,next_node);
					//cout << search_node->p_block->name() << "->" << result_node->p_block->name() << endl;
					/* Bus-Selectorに接続されている信号線を削除 */
					graph = deleteEdgeBetNode(graph,search_node,result_node);
					/* nodeとresult_nodeを接続 */
					graph.createEdge(node,result_node);
				}//<outport>のループ終了
			}
			out_edge = out_edge->p_out_edge;
		}
	}
	/* Busブロックの削除 */
	graph = deleteBusNode(graph,node_list);

	/* デバッグ用 */
	graph.dumpDotFile("change_graph_deleteBus.dot");

	return graph;
}

////////////////////
// deleteEdgeBetNode
// [概要] 指定された２つのノード間の信号線を削除
// [引数] node(元)とnext_node(先)
// [返り値] BLGraph
// [備考]
// deleteEdgeを簡単に呼ぶためのものです。
BLGraph deleteEdgeBetNode(BLGraph graph,blnode_T* node,blnode_T* next_node)
{
	bledge_T* outEdge = node->p_out_edge;
	while(outEdge != NULL){
		//cout << "nodeis:" << outEdge->p_t_node->p_block->name() << endl;
		if(outEdge->p_t_node->p_block->name() == next_node->p_block->name()){
			graph.deleteEdge(outEdge);
			break;
		}
		outEdge = outEdge->p_out_edge;
	}
	return graph;
}
////////////////////
// reconnectNode
// [概要] 一つ先のノードへ信号線を再接続
// [引数] nodeとそれを入力とするnext_node
// [返り値] BLGraph
// [備考]
// //**ただいま使用されていません。**//
// nodeとnext_node間の信号線を削除したあとに信号線を継承するために使用
// next_nodeの出力先全てとnodeを接続
BLGraph reconnectNodes(BLGraph graph,blnode_T* node,blnode_T* next_node)
{
	bledge_T* outEdge = next_node->p_out_edge;
	while(outEdge != NULL){
		blnode_T* reconnectNode = outEdge->p_t_node;
		graph.createEdge(node,reconnectNode);
	}
	return graph;
}
////////////////////
// deleteBusNode
// [概要] BusCreator,BusSelectorのブロックを削除
// [引数] BLGraphと現在のnode_list
// [返り値] BLGraph
// [備考]
// Busブロックに接続されている信号線を繋ぎ直してから
// 使用してください。
BLGraph deleteBusNode(BLGraph graph,vector<blnode_T*> node_list)
{
	vector<blnode_T*>::iterator i;

	for(i = node_list.begin();i != node_list.end();i++){
		if((*i)->p_block->blocktype() == "BusCreator"
		|| (*i)->p_block->blocktype() == "BusSelector"){
			graph.deleteNode(*i);
		}
	}
	return graph;
}

////////////////////
// deleteNormalSubsystemBlock
// [概要] ただの仮想的なサブシステムブロックを削除
// [引数] BLGraph
// [返り値] BLGraph
// [備考]
//
BLGraph deleteNormalSubsystemBlock(BLGraph graph)
{
	vector<blnode_T*> blnodeList = graph.getNodeVector();
	vector<blnode_T*>::iterator i;
	vector<blnode_T*> deleteBlnodeList;
	for(i = blnodeList.begin();i != blnodeList.end();i++){
		if((*i)->p_block->blocktype() == "SubSystem"
		&& (*i)->p_in_edge == NULL
		&& (*i)->p_out_edge == NULL
		){
			deleteBlnodeList.push_back(*i);
			//graph.deleteNode(*i);
			cout << "ok" << endl;
		}
	}
	for(i = deleteBlnodeList.begin();i != deleteBlnodeList.end();i++){
		graph.deleteNode(*i);
	}
	return graph;
}

////////////////////
// deleteIoportBlockInSubsystem
// [概要] サブシステム内のInportブロックとOutportブロックを削除
// [引数] BLGraph
// [返り値] BLGraph
// [備考] 出力側にエッジのあるOutportブロック、入力側にエッジのあるInportブロックを削除
//
BLGraph deleteIoportBlockInSubsystem(BLGraph graph)
{
	vector<blnode_T*> blnodeList = graph.getNodeVector();
	vector<blnode_T*>::iterator i;
	vector<blnode_T*> deleteBlnodeList;
	blnode_T *sNode,*tNode;
	bledge_T *oEdge;
	for(i = blnodeList.begin();i != blnodeList.end();i++){
		cout << (*i)->p_block->name() << endl;
		if((*i)->p_block->blocktype() == "Inport"
		&& (*i)->p_in_edge != NULL
		){
			deleteBlnodeList.push_back(*i);
			sNode = (*i)->p_in_edge->p_s_node;
			oEdge = (*i)->p_out_edge;
			while(oEdge != NULL){
				tNode = oEdge->p_t_node;
				//graph.deleteNode(*i);
				graph.createEdge(sNode,tNode);
				oEdge = oEdge->p_out_edge;
			}
		}else if((*i)->p_block->blocktype() == "Outport"
		       && (*i)->p_out_edge != NULL
		){
			deleteBlnodeList.push_back(*i);
			sNode = (*i)->p_in_edge->p_s_node;
			oEdge = (*i)->p_out_edge;
			while(oEdge != NULL){
				tNode = oEdge->p_t_node;
				//graph.deleteNode(*i);
				graph.createEdge(sNode,tNode);
				oEdge = oEdge->p_out_edge;
			}
		}else{
			//nop
		}
	}
	for(i = deleteBlnodeList.begin();i != deleteBlnodeList.end();i++){
		graph.deleteNode(*i);
	}
	/* デバッグ用 */
	graph.dumpDotFile("change_graph_deleteIO.dot");

	return graph;
}

////////////////////
// mergeNonCostBlock
// [概要] performanceタグのつかないブロックを前後のブロックにマージ
// [引数] BLGraph
// [返り値] BLGraph
// [備考] コア割り当て時にマージしたブロックと同じコアとして出力したい(希望)
//
BLGraph mergeNonCostBlock(BLGraph graph)
{
	vector<blnode_T*> blnodeList = graph.getNodeVector();
	vector<blnode_T*>::iterator i;

}

////////////////////
// mergeSubsystemBlock
// [概要] 階層が離れた時の優先度付ができないため、サブシステム単位でまとめるための関数
// [引数] BLGraphと指定の階層(string)
// [返り値] BLGraph
// [備考] 指定された階層上に存在するサブシステム内の処理をすべてマージ
//        処理量のみをノードにつける方針
//        この関数をdeleteIOportBlockInSubsystemの先に実行すること
/*
BLGraph mergeSubsystemBlock(BLGraph graph,string subsys)
{
	//手順
	//1:選択されたサブシステムを探索
	//2:その中のノードを探索(map<blnode_T*,blnode_T*>使用)
	//3:コストを足し算
	//4:パフォーマンスタグの作成
	//5:サブシステム内の接続情報を復元(サブシステム内のInportとOutportより)
	//6:新しくサブシステムを作り直し(blxml上のブロックから作り直し)

	sNameSize = (int)subsys.size();

	vector<blnode_T*> nodeList = graph.getNodeVector();
	vector<blnode_T*>::iterator bi;

	vector<blnode_T*> mergeNodeList;
	blnode_T* sNode;
	double stCost = 0,sbCost = 0,swCost = 0;

	//手順1,2,3
	for(bi = nodeList.begin();bi != nodeList.end();bi++){
		if(*(bi)->p_block->name() == subsys){
			sNode = *(bi);
		}
		else if(strncmp((node_list[i]->p_block->name()).c_str(),subsys,sNameSize)){
			mergeNodeList.push_back(*bi);
			sCost += getNodePerformance(*bi,1);
			//best,worstに関する処理も追加する必要あり
		}
	}

	//手順4
	performace_T nodePerfomace("task");
	nodePerformance->typical(sCost);
	sNode->p_block->performance(nodePerformance);

	//手順5
	//手順5-1:サブシステム内にInport-Outportブロックを探索
	//手順5-2:それぞれの接続元、接続先をsNodeに接続
	bledge_T* inEdge,outEdge;
	blnode_T* srcNode,dstNode;
	for(bi = mergeNodeList.begin();bi != mergeNodeList.end(),bi++){
		if(*(bi)->p_block->blocktype() == "Inport"){
			inEdge = *(bi)->p_in_edge;
			while(inEdge != NULL){
				srcNode = inEdge->p_s_node;
				graph.createEdge(srcNode,sNode);
				inEdge = inEdge->p_in_edge;
			}
		}else if(*(bi)->p_block->blocktype() == "Outport"){
			outEdge = *(bi)->p_out_edge;
			while(outEdge != NULL){
				dstNode = outEdge->p_t_node;
				graph.createEdge(sNode,dstNode);
				outEdge = outEdge->p_out_edge;
			}
		}
	}

	graph.dumpDotFile("change_mergeSubsystem.dot");

	return graph;
}
*/

////////////////////
// chooseMergeSubsystem
// [概要] mergeSubsystemBlockを適用するブロックを選定
// [引数] BLGraphと指定の階層(string)
// [返り値] BLGraph
// [備考] 長周期タスクと短周期タスク
//        yamlファイルをパースする必要があるのでyaml-cpp/yaml.hをインクルードする必要がある
/*
BLGraph chooseMergeSubsystem(BLGraph graph,string filename)
{
  try{
    YAML::Node config = YAML::LoadFile("graphopt.yaml");
    cout << config.size() << endl;
    string aSubsystemName = ["AtomicSubsystem"]["name"].as<string>();
    cout << aSubsystemName << endl;
  }
  catch(YAML::Exeception& e){
    cerr >> e.what() << endl;
  }
  return 0;
}
*/

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
			cout<< "Unable to load file" << endl;
			return graph;
	}
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
  graph.dumpDotFile("change_graph_mergeSubsystem.dot");

  return graph;
}

////////////////////
// deleteConstantBlock
// [概要] performanceタグのつかないConstantブロックおw削除
// [引数] BLGraph
// [返り値] BLGraph
// [備考]
//
BLGraph deleteConstantBlock(BLGraph graph)
{
	vector<blnode_T*> blnodeList = graph.getNodeVector();
	vector<blnode_T*>::iterator i;
	for(i = blnodeList.begin();i != blnodeList.end();i++){
		if((*i)->p_block->blocktype() == "Constant"){
			graph.deleteNode((*i));
		}
	}

	return graph;
}
