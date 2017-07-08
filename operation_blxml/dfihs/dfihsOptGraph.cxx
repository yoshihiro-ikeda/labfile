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
	graph.dumpDotFile("change_graph.dot");
	
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
