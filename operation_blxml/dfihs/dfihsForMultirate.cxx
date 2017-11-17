//DF/IHS法において長周期タスクのあるオフセットが設定されているブロック群と
//短周期タスクのブロック群をBLGraph上で切り出す関数群

#include "dfihs.hxx"



//string型をint型にして返す
//int stoi_me(string str)
//{
  //return atoi(str.c_str());
//}

////////////////////
// split
// [概要] blxml内のrateからオフセット付きデータを取得するために使用
// [引数] 分割したい文字列input、区切り文字delimiter
// [返り値] vector型の文字群
// [備考]

vector<string> split(const string& input, char delimiter)
{
    std::istringstream stream(input);

    std::string field;
    std::vector<std::string> result;
    while (std::getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

////////////////////
// extractBlocksFromBLGraph
// [概要] DF/IHS法の適用箇所を指定するためグラフを切り出し
//        (長周期タスクの一部と短周期タスク)
// [引数] BLGraphであるgraphとオフセットのIDであるdivid、長周期時間rate_l、短周期時間rate_s
// [返り値] 切り出されたBLGraph
// [備考]
// Atomic subsystemはサブシステムを残すがそれ以外はBLGraph上からサブシステムも削除
//オフセット反映が終了したSimulinkモデルから生成されるBLXMLが入力という前提
BLGraph extractBlocksFromBLGraph(BLGraph graph, int divid, double rate_l, double rate_s)
{
	//全体のnode list
	vector<blnode_T*> node_list;
	vector<blnode_T*>::iterator node_itr;
	int node_list_size;
	
	node_list = graph.getNodeVector();
	node_list_size = (int)node_list.size();
	
	//peinfo操作用の変数
  stringstream ss_tmp;
  int i_tmp;
  //string str_tmp;
  vector<string> result;
  vector<string>::iterator  j_itr;
	
	//切り出す周期-オフセット情報を生成(string型)
	double offset = rate_s * divid;
	
	double rate_l_tmp,rate_s_tmp,offset_tmp;
	string s,t;
	char *ends;
	
	//周期は２つしかないことを想定、オフセットはいくつでも
	for(int i = 0;i < node_list_size;i++){
		cout << node_list[i]->p_block->rate() << endl;
		ss_tmp << node_list[i]->p_block->rate();
		string str_tmp(ss_tmp.str());
		cout << str_tmp << endl;
		i_tmp = stoi_me(ss_tmp.str());
		cout << i_tmp << endl;

		if(i_tmp == 0){//offsetか<not present>
			if(ss_tmp.str() == "<not present>"){
				graph.deleteNode(node_list[i]);
			}else{//offsetの場合
				str_tmp.erase(str_tmp.end()-1);
				cout << str_tmp << endl;
				str_tmp.erase(str_tmp.begin());
				//str_tmp.pop_back();
				//
				cout << str_tmp << endl;
				result = split(str_tmp,',');
				for(j_itr = result.begin();j_itr != result.end();j_itr++){
					cout << *j_itr << endl;
				}
				cout << *result.begin() << endl;
				cout << *(result.end()-1) << endl;
				
				s = (*result.begin());
				t = (*(result.end()-1));
				
				rate_l_tmp = strtod(s.c_str(),&ends);
				offset_tmp = strtod(t.c_str(),&ends);
				//rate_l_tmp = strtod((*result.begin()).c_str());
				//offset_tmp = strtod(*(result.end()-1));
				if(rate_l !=  rate_l_tmp|| offset != offset_tmp){
					graph.deleteNode(node_list[i]);
				}else{
					//nop
				}
			}
		}else if(i_tmp == rate_s){//短周期と同じ場合
			//nop
		}else if(i_tmp == rate_l){//長周期と同じ場合
			//offset値が0ということでそれ以外の場合削除
			//Atomic subsystemの場合だけ残す予定だけど今は保留
			if(divid != 0){
				graph.deleteNode(node_list[i]);
			}
		}else{//該当無し
		}
		
		ss_tmp.str("");
		ss_tmp.clear(stringstream::goodbit);
		
	}//end node loop
	
	/* デバッグ用 */
	graph.dumpDotFile("change_graph_multirate.dot");
	
	return graph;
		
}


