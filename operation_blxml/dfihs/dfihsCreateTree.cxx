//DF/IHSのTreeを作っていく関数群

#include "dfihs.hxx"



////////////////////
// addDfihsNodeToTree
// [概要] あるdfihsノードから複数のノードを再帰的に生成します
// [引数] dfihsTree,dfihsNode
// [返り値] 
// [備考] 
// 再帰的によびだされます。
// 一つでもコアが空いたらそこにタスクを埋めるかnopを入れるかのノードを生成
void DFIHSTree::addDfihsNodeToTree(dfihsnode_t* dfihsNode,vector<coreinfo_t*> coreInfo)
{
	vector<BLNPlus> blp_list = blnode_priority_list;
	//空きコア数とreadyTaskTableの個数に応じてループ回数が変化
	//空いているコア数を計測
	int idleCoreNum = 0;
	for(int i = 0;i < CORE_NUM;i++){
		if(coreInfo[i]->executeTaskNum == -1){
			idleCoreNum++;
		}
	}
	int createNodeNum = calcCombination((int)(dfihsNode->readyTaskTable.size()),idleCoreNum);
	//ここでcreatenodeNumが0になってしまっている
	cout << "checkpoint" << endl;
	if(dfihsNode->readyTaskTable.size() < CORE_NUM){
		createNodeNum = 1;
		//for(int i = (int)dfihsNode->readyTaskTable.size();i <= CORE_NUM;i++)
			//dfihsNode->readyTaskTable.push_back(NOP);
	}


	//printDfihsNode(dfihsNode);
	//sleep(1);

	for(int i = 0;i < createNodeNum;i++){
		//次のノードを定義
		dfihsnode_t *nextDfihsNode;
		nextDfihsNode = new dfihsnode_t;
		nextDfihsNode->degree = dfihsNode->degree + 1;
		nextDfihsNode->width = dfihsNode->width;
		nextDfihsNode->width.push_back(i);
		
		//selectedPointerを生成
		vector<int> sourceSelectedPointer;
		for(int j = 1;j <= (int)dfihsNode->readyTaskTable.size();j++){
			sourceSelectedPointer.push_back(j);
		}
		
		
		nextDfihsNode->selectedTaskPointer = dictionaryOrder(sourceSelectedPointer,i+1);

		//readyTaskTableからexecuteTaskを決定
		vector<int> tmpExecuteTask;
		tmpExecuteTask.reserve(CORE_NUM);

		int count = 0;//selected pointer用
		nextDfihsNode->alreadyFinishTaskTable = dfihsNode->alreadyFinishTaskTable;
		for(int j = 0;j < CORE_NUM;j++){
			if(coreInfo[j]->executeTaskNum == -1){
				int tmpExecuteTaskNum = dfihsNode->readyTaskTable[nextDfihsNode->selectedTaskPointer[count] - 1];
				int tmpFinishTime = 100;
				//この行入れるとセグメントエラーする
				//if(tmpExecuteTaskNum != NOP)
				tmpFinishTime = dfihsNode->currentTime + getNodePerformance(blp_list[tmpExecuteTaskNum].getblnode(),1);
				//cout << "nani:" << tmpFinishTime << endl;
				coreinfo_t *tmpCoreInfo;
				tmpCoreInfo = new coreinfo_t;
				tmpCoreInfo->executeTaskNum = tmpExecuteTaskNum;
				tmpCoreInfo->finishTime = tmpFinishTime;
				nextDfihsNode->coreInfo.push_back(tmpCoreInfo);
				nextDfihsNode->alreadyFinishTaskTable.push_back(tmpExecuteTaskNum);
				nextDfihsNode->executeTaskTable.push_back(tmpExecuteTaskNum);
				cout << tmpExecuteTaskNum << endl;
				tmpExecuteTask.push_back(tmpExecuteTaskNum);
				count++;
				//ループを終了する場合
				if((int)dfihsNode->readyTaskTable.size() == count){
					cout << "----loop owari----" << endl;
					for(int k = j+1;k < CORE_NUM;k++){
						coreinfo_t *tmpCoreInfo;
						tmpCoreInfo = new coreinfo_t;
						tmpCoreInfo->executeTaskNum = -1;
						tmpCoreInfo->finishTime = FTIME;
						nextDfihsNode->coreInfo.push_back(tmpCoreInfo);
					}
					//printDfihsNode(nextDfihsNode);
					break;
				}
//				if((int)nextDfihsNode->alreadyFinishTaskTable.size() == 9){
//					cout << "-----------------------------------return-----------------------------------" << endl;
//					return;
//				}

			}
		}
		//}
		//readyTaskTableを更新
		//dfihsNode->alreadyFinishTaskTable.push_back(tmpExecuteTask[0]);
		nextDfihsNode->readyTaskTable = updateReadyTaskTable(dfihsNode,tmpExecuteTask[0]);
		for(int j = 1;j < (int)tmpExecuteTask.size();j++){
			//dfihsNode->alreadyFinishTaskTable.push_back(tmpExecuteTask[j]);
			nextDfihsNode->readyTaskTable = updateReadyTaskTable(nextDfihsNode,tmpExecuteTask[j]);
		}
		//sort(nextDfihsNode->readyTaskTable.begin(),nextDfihsNode->readyTaskTable.end());
		for(int j = 0;j < (int)tmpExecuteTask.size();j++){
			vector<int>::iterator i = find(nextDfihsNode->readyTaskTable.begin(),nextDfihsNode->readyTaskTable.end(),tmpExecuteTask[j]);
			if(i != nextDfihsNode->readyTaskTable.end())
				i = nextDfihsNode->readyTaskTable.erase(i);
		}
		tmpExecuteTask.clear();
		//親ノード情報を追加
		nextDfihsNode->parentNode = dfihsNode;
		//各必要情報を追加したnextDfihsNodeをdfihsTreeに追加
		//再帰呼出し（readyTaskTableが空でなかったら）
		//コアごとの終了タイミング
		//この再帰関数の引数に空いているコア数じゃなくてcoreInfo渡せば解決するかなー
		//dfihs法的にはコアが空いた時点で次の処理を行っていくはず
		vector<coreinfo_t*> idleCoreInNextStep; 
		if((int)nextDfihsNode->readyTaskTable.size() != 0){
			//coreInfoを早く終わる順にソート
			cout << "before:" << endl;
			for(int j = 0;j < (int)nextDfihsNode->coreInfo.size();j++)
				cout << nextDfihsNode->coreInfo[j]->executeTaskNum << endl;
			sort(nextDfihsNode->coreInfo.begin(),nextDfihsNode->coreInfo.end());
			//for(int j = nextDfihsNode->coreInfo.begin();j < nextDfihsNode->coreInfo.end();j++)
			cout << "after:" << endl;
			for(int j = 0;j < (int)nextDfihsNode->coreInfo.size();j++)
				cout << nextDfihsNode->coreInfo[j]->executeTaskNum << endl;
			for(int j = 0;j < (int)nextDfihsNode->coreInfo.size();j++){
				idleCoreInNextStep.clear();
				if(nextDfihsNode->coreInfo[j]->finishTime == FTIME)
					continue;
				int tmpCallTime = nextDfihsNode->coreInfo[j]->finishTime;
				//２コア限定の飛ばし方
				if(j > 0 && tmpCallTime == nextDfihsNode->coreInfo[0]->finishTime)
					continue;
				for(int k = 0;k < (int)nextDfihsNode->coreInfo.size();k++){
					if(tmpCallTime >= nextDfihsNode->coreInfo[k]->finishTime && tmpCallTime != FTIME){
						coreinfo_t *tmpCoreInfo;
						tmpCoreInfo = new coreinfo_t;
						tmpCoreInfo->executeTaskNum = -1;
						tmpCoreInfo->finishTime = FTIME;
						idleCoreInNextStep.push_back(tmpCoreInfo);
					}else{
						cout << "kottikiteru" << endl;
						idleCoreInNextStep.push_back(nextDfihsNode->coreInfo[k]);
					}

				}
				//次ノード呼び出し時の時間情報をnextDfihsNodeに追加
				nextDfihsNode->currentTime = tmpCallTime;
				cout << "currentTime:" << tmpCallTime << endl;
				printDfihsNode(nextDfihsNode);
				addDfihsNodeToTree(nextDfihsNode,idleCoreInNextStep);
			}
		}else{
			//最後の実行時間の設定
			int finishTime = 0;
			for(int j = 0;j < (int)nextDfihsNode->coreInfo.size();j++){
				if(nextDfihsNode->coreInfo[j]->finishTime == FTIME)
					continue;
				if(finishTime < nextDfihsNode->coreInfo[j]->finishTime){
					finishTime = nextDfihsNode->coreInfo[j]->finishTime;
				}
			}
			nextDfihsNode->currentTime = finishTime;
			cout << "-------------------this node is leaf-------------------" << endl;
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			printDfihsNode(nextDfihsNode);
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			if(interimSolutionTime > nextDfihsNode->currentTime){
				cout << "kokookitenaikana" << endl;
				interimSolution = nextDfihsNode;
				interimSolutionTime = nextDfihsNode->currentTime;
			}

			return;
			//DFIHSTree::calcResult(nextDfihsNode);
			//exit(1);
		}
	}//End for(int i = 0;i < createNodeNum;i++)
}

////////////////////
// updateReadyTaskTable
// [概要] レディタスクテーブルを更新
// [引数] dfihsTree,現在のreadyTaskTable,終わったブロックのナンバー
// [返り値] 更新されたreadyTaskTable
// [備考] 
// push_backで追加すると優先度が逆転してしまう可能性があるため、
// readyTaskTableを作り直します。
vector<int> DFIHSTree::updateReadyTaskTable(dfihsnode_t* dfihsNode, int finishTaskNum)
{
	vector<BLNPlus> blp_list = blnode_priority_list;
	vector<int> tmpTaskTable;
	vector<int> readyTaskTable = dfihsNode->readyTaskTable;
	vector<int> alreadyFinishTaskTable = dfihsNode->alreadyFinishTaskTable;

	//cout << "------------------------------------------------------------------------------------------------------------" << endl;
	//printDfihsNode(dfihsNode);

	alreadyFinishTaskTable.push_back(finishTaskNum);

	for(int i = 0;i < (int) blp_list.size();i++){
		blnode_T* tmpBlNode = blp_list[i].getblnode();
		int tmpTaskNum = blp_list[i].getPriorityNum();
		//cout << "searchnode:" << tmpBlNode->p_block->name() << endl;
		//readyTaskTableに元々あるものはそのまま次も使用
//		vector<int>::iterator checkTaskNumIte = find(readyTaskTable.begin(),readyTaskTable.end(),tmpTaskNum);
//		if(checkTaskNumIte != readyTaskTable.end()){
//			vector<int>::iterator checkExecute = find(alreadyFinishTaskTable.begin(),alreadyFinishTaskTable.end(),tmpTaskNum);
//			if(checkExecute == alreadyFinishTaskTable.end()){
//				tmpTaskTable.push_back(tmpTaskNum);
//				cout << "jikkou:" << tmpTaskNum << endl;
//			}
//			continue;
//		}
		//else{
		bledge_T* inEdge = tmpBlNode->p_in_edge;
		while(inEdge != NULL){
			blnode_T* inNode = inEdge->p_s_node;
			int nodeNum;
			//対象のノードの入力となるノードを検索
			for(int j = 0;j < (int) blp_list.size();j++){
				if(inNode == blp_list[j].getblnode()){
					nodeNum = j;
					break;
				}
			}
			//そのノードがすでに実行されたかどうか確認
			//探索されていれば良し
			vector<int>::iterator checkFinishTaskNum = find(alreadyFinishTaskTable.begin(),alreadyFinishTaskTable.end(),blp_list[nodeNum].getPriorityNum());
			if(checkFinishTaskNum == alreadyFinishTaskTable.end()){
				//cout << "kidoku:" << blp_list[nodeNum].getPriorityNum() << endl;
				break;
			}
			inEdge = inEdge->p_in_edge;
		}
		if(inEdge == NULL){
			vector<int>::iterator checkExecute = find(alreadyFinishTaskTable.begin(),alreadyFinishTaskTable.end(),tmpTaskNum);
			if(checkExecute == alreadyFinishTaskTable.end())
				tmpTaskTable.push_back(tmpTaskNum);
		//}
		}
	}
	//vector<int>::iterator eraseTaskNum = find(tmpTaskTable.begin(),tmpTaskTable.end(),finishTaskNum);
	//tmpTaskTable.erase(eraseTaskNum);
//	for(int i = 0;i < (int)tmpTaskTable.size();i++){
//		cout << "num:" << tmpTaskTable[i] << endl;
//	}
	return tmpTaskTable;
}

////////////////////
// compCoreInfo
// [概要] coreinfo内をソートするための条件
// [引数] 比較したいcoreinfo２つ
// [返り値] 差分
// [備考]
// クイックソート関数で比較演算のために使用
int compCoreInfo(coreinfo_t *core1,coreinfo_t *core2)
{
	coreinfo_t *tmp1,*tmp2;
	tmp1 = core1;
	tmp2 = core2;

	int ftime1 = core1->finishTime;
	int ftime2 = core2->finishTime;

	return ftime1 - ftime2;
}

////////////////////
// factorialMethod
// [概要] 階乗を計算
// [引数] n!の場合のn
// [返り値] 計算結果
// [備考] 
// 組み合わせを求める際に使います。
int factorialMethod(int k)
{
	int sum = 1;
	for(int i = 1;i <= k;i++){
		sum *= i;
	}
	return sum;
}

////////////////////
// calcCombination
// [概要] 組み合わせの計算
// [引数] nCkのnとk
// [返り値] 計算結果
// [備考] 
// addDfihsNodeToTree内の再帰ループ回数の決定に使います。
int calcCombination(int n,int k)
{
	int dominator = factorialMethod(n-k) * factorialMethod(k);
	int molecule = factorialMethod(n);
	
	//cout << molecule << "---" << dominator << endl;

	return (molecule/dominator);
}

////////////////////
// dictionaryOrder
// [概要] 組み合わせの辞書順を返す
// [引数] vectorとほしい番号num
// [返り値] 計算結果
// [備考] 
// vectorが[1,2,3,4]だった場合、3と言われたら[1,4]を返し、4と言われたら[2,3]を返す。
// コア数に応じて変化させる必要あり
// 0を引数に入れてしまうとおかしくなります
vector<int> dictionaryOrder(vector<int> s_vec,int want_num)
{

	int i;//第一要素を決めた場合の組み合わせ数
	int j = 0;//現在見ている要素

	vector<int> determine_vec;

	int core_num = CORE_NUM;
	int s_vec_size = (int)s_vec.size();

	if(s_vec_size < 2)
		return s_vec;

	if(calcCombination(s_vec_size,core_num) < want_num){
		cout << "sonnnanonaiyo" << endl;
		//exit(1);
	}


	while(core_num != 0){
	  i = calcCombination(s_vec_size - 1,core_num - 1);
	  if(want_num > i && i != 0){
		want_num = want_num - i;
		s_vec_size--;
		j++;
	  }
	  else{
		determine_vec.push_back(s_vec[j]);
		s_vec_size--;
		core_num--;
		j++;
	  }
	}
	return determine_vec;
}
