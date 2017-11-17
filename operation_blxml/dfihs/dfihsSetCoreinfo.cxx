//DF/IHS法によるスケジューリング結果からコア割り当てを決定する関数
//上記の方法では各タイミングにおいてどのブロックを実行するかは決定できるが、
//どのコアに配置するかの決定には至らない

#include "dfihs.hxx"

////////////////////
// setCoreinfoNum
// [概要] DF/IHS法の探索結果を元にコア割り当てを実行
// [引数] blnodeの拡張リストblnp、DF/IHS法の最適解dfnodeList
// [返り値] コア割り当てが行われたblnodeの拡張リスト
// [備考]
// blnpは優先度順及びタスク番号順に並んでいることに留意
//vector<BLNPlus> setCoreinfoNum(vector<BLNPlus> blnp,vector<dfihsnode_t*> dfnodeList)
//{
	//cout << "start core assignment" << endl;

	////最初のdfihsnodeは-1が割り当てられているため削除
	//dfnodeList.erase(dfnodeList.begin());

	//cout << "Number of cores: " << CORE_NUM << endl;
	//cout << "Number of dfihsnode: " << (int)dfnodeList.size() << endl;;

	////最初のdfihsnodeを確認(phase1)
	//for(int i = 0; i < CORE_NUM;i++){
		//int executeNodeNum = dfnodeList[0]->executeTaskTable[i];
		//if(executeNodeNum != -1){
			//blnp[executeNodeNum].getblnode()->p_block->peinfo(itos_me(i));
		//}
	//}

	////dfihsnodeの２つ目以降を確認(phase2)
	//int core[CORE_NUM] = {0}; //コアが空かどうか判定するため
	//for(int i = 1;i < (int)dfnodeList.size();i++){
		//cout << "dfihsnode num:" << i << endl;
		////優先度1(最高)：直前のステップに同じブロックがあれば割り当てたことにしてスキップ
		//for(int j = 0;j < CORE_NUM;j++){
			//int executeNodeNum = dfnodeList[i]->executeTaskTable[j];
			//if(executeNodeNum == -1)
				//continue;
////			stringstream peinfo_s;
////			peinfo_s << blnp[executeNodeNum].getblnode()->p_block->peinfo();
////			int peinfo_i = stoi_me(peinfo_s.str());
////			peinfo_s.str("");
////			peinfo_s.clear(stringstream::goodbit);
			//int peinfo_i = getpeinfo(blnp[executeNodeNum].getblnode());
			//if(peinfo_i != -1){
				//core[peinfo_i] = 1;
			//}
		//}
		////優先度2：直前のステップに割り当てられているノードと接続関係にいるノードを同じコアに割り当て
		////最初に見つかった接続関係に基づき割り当て
		//for(int j = 0;j < CORE_NUM;j++){
			//int executeNodeNum = dfnodeList[i]->executeTaskTable[j];
			//if(executeNodeNum == -1)
				//continue;
			//if(getpeinfo(blnp[executeNodeNum].getblnode()) != -1)
				//continue;
			//bledge_T *inedge = blnp[executeNodeNum].getblnode()->p_in_edge;
			
			//while(inedge != NULL){
				//blnode_T *blnode = inedge->p_s_node;
////				stringstream peinfo_s;
////				peinfo_s << blnode->p_block->peinfo();
////				int peinfo_i = stoi_me(peinfo_s.str());
////				peinfo_s.str("");
////				peinfo_s.clear(stringstream::goodbit);
				//int peinfo_i = getpeinfo(blnode);
				//if(peinfo_i != -1 && core[peinfo_i] == 0){
					//blnp[executeNodeNum].getblnode()->p_block->peinfo(itos_me(peinfo_i));
					//core[peinfo_i] = 1;
					//cout << blnp[executeNodeNum].getblnode()->p_block->name() << endl;
					//break;
				//}
				//inedge = inedge->p_in_edge;
			//}
		//}
		////優先度3(最低):上記で割り当てられていないノードを空いているコアに割り当て
		//for(int j = 0;j < CORE_NUM;j++){
			//int executeNodeNum = dfnodeList[i]->executeTaskTable[j];
			//if(executeNodeNum == -1)
				//continue;
			//if(getpeinfo(blnp[executeNodeNum].getblnode()) != -1)
				//continue;
			//stringstream peinfo_s;
			//peinfo_s << blnp[executeNodeNum].getblnode()->p_block->peinfo();
			//int peinfo_i = stoi_me(peinfo_s.str());
			//peinfo_s.str("");
			//peinfo_s.clear(stringstream::goodbit);
			//if(peinfo_i == -1){
				//for(int k = 0;k < CORE_NUM;k++){
					//if(core[k] == 0){
						//cout << blnp[executeNodeNum].getblnode()->p_block->name() << "::" << itos_me(k) << endl;
						//blnp[executeNodeNum].getblnode()->p_block->peinfo(itos_me(k));
						//core[k] = 1;
					//}
				//}
			//}
		//}
		////ループの最後にコアの使用状況を初期化
		//for(int j = 0;j < CORE_NUM;j++){
			//core[j] = 0;
		//}
	//}


	//return blnp;
//}

//新しいバージョン
vector<BLNPlus> setCoreinfoNum(vector<BLNPlus> blnp,vector<dfihsnode_t*> dfnodeList)
{
	cout << "start core assignment" << endl;

	//最初のdfihsnodeは-1が割り当てられているため削除
	dfnodeList.erase(dfnodeList.begin());

	cout << "Number of cores: " << CORE_NUM << endl;
	cout << "Number of dfihsnode: " << (int)dfnodeList.size() << endl;;
	
	for(int i = 0;i < (int)blnp.size();i++){
		blnp[i].getblnode()->p_block->peinfo("-1");
		//cout << i << ":" << (blgp[i].getblnode())->p_block->name() << ":" << blgp[i].getblnode()->p_block->peinfo() << endl;
	}

	//最初のdfihsnodeを確認(phase1)
	for(int i = 0; i < CORE_NUM;i++){
		int executeNodeNum = dfnodeList[0]->executeTaskTable[i];
		if(executeNodeNum != -1){
			blnp[executeNodeNum].getblnode()->p_block->peinfo(itos_me(i));
		}
	}
	
	//dfihsnodeの２つ目以降を確認(phase2)
	int core[CORE_NUM] = {0}; //コアが空かどうか判定するため
	int flagCase3 = 0;
	for(int i = 1;i < (int)dfnodeList.size();i++){
		for(int j = 0;j < CORE_NUM;j++){
			int executeNodeNum = dfnodeList[i]->executeTaskTable[j];
			
			//ブロックが実行されていなければスルー
			if(executeNodeNum == -1)
				continue;
			cout << "dfihsID:" << i << ":block:" << blnp[executeNodeNum].getblnode()->p_block->name() << endl;
			//そのタイミングでブロックがすでにコア割り当てされていればスルー
			int peinfo_i = getpeinfo(blnp[executeNodeNum].getblnode());
			if(peinfo_i != -1){
				core[peinfo_i] = 1;
				continue;
			}
			//直前のDF/IHSノードで信号線でつながっているブロックが実行されていれば同じコアに割り当て
			bledge_T *inedge = blnp[executeNodeNum].getblnode()->p_in_edge;
			while(inedge != NULL){
				blnode_T *blnode = inedge->p_s_node;
				int peinfo_i = getpeinfo(blnode);
				
				if(peinfo_i != -1 && core[peinfo_i] == 0){
					cout << "    dfihsID:" << i << ":block:" << blnp[executeNodeNum].getblnode()->p_block->name() << endl;
					blnp[executeNodeNum].getblnode()->p_block->peinfo(itos_me(peinfo_i));
					core[peinfo_i] = 1;
					//cout << blnp[executeNodeNum].getblnode()->p_block->name() << endl;
					flagCase3 = 1;
					break;
				}
				inedge = inedge->p_in_edge;
			}
			if(flagCase3 == 1){
				flagCase3 = 0;
				
				continue;
			}
			//上のパターンでコア割り当てされなかったとき空いているコアに割り当て
			for(int j = 0;j < CORE_NUM;j++){
				if(core[j] == 0){
					blnp[executeNodeNum].getblnode()->p_block->peinfo(itos_me(j));
					cout << "  dfihsID:" << i << ":block:" << blnp[executeNodeNum].getblnode()->p_block->name() << endl;
					break;
				}
			}
		}//end of for(int j = 0;j < CORE_NUM;j++)
		//ループの最後にコアの使用状況を初期化
		for(int j = 0;j < CORE_NUM;j++){
			core[j] = 0;
		}
	}//end of for(int i = 1;i < (int)dfnodeList.size();i++)
	return blnp;
}

bool checkConnectNode(BLNPlus blnp1,BLNPlus blnp2)
{
	return 1;
}
