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
	
	static int id = 0;
	id++;
	cout << "id:" << id << endl;
	cout << "------------------------------------------------------------------------" << endl;
	//if(id > 2000)
	//	return;
	//if(dfihsNode->currentTime > 2800)
		//return;

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
	//cout << "checkpoint" << endl;
	if(dfihsNode->readyTaskTable.size() < CORE_NUM){
		createNodeNum = 1;
	}

	printCoreInfo(coreInfo);
	printDfihsNode(dfihsNode);
	cout << "createNodeNum:" << createNodeNum << endl;
	//sleep(1);

	vector<int> tmpPAlreadyTaskTable;
	tmpPAlreadyTaskTable.resize(dfihsNode->alreadyFinishTaskTable.size());
	copy(dfihsNode->alreadyFinishTaskTable.begin(),dfihsNode->alreadyFinishTaskTable.end(),tmpPAlreadyTaskTable.begin());

	dfihsnode_t *tmpDfihsNode;
	tmpDfihsNode = new dfihsnode_t;
	memcpy(tmpDfihsNode,dfihsNode,sizeof(dfihsnode_t));
	//cout << "parent" << tmpDfihsNode->degree << endl;
	const double tmpFinishTime = (tmpDfihsNode->currentTime);
	//cout << "-----------------------------------------tmp finish-----------------------------------------------" << tmpFinishTime << endl;

	for(int i = 0;i < createNodeNum;i++){
		//次のノードを定義
		dfihsnode_t *nextDfihsNode;
		nextDfihsNode = new dfihsnode_t;
		nextDfihsNode->degree = dfihsNode->degree + 1;
		nextDfihsNode->width = dfihsNode->width;
		nextDfihsNode->width.push_back(i);
		
		//親ノード情報を追加
		//dfihsNode->currentTime = tmpFinishTime;
		nextDfihsNode->parentNode = new dfihsnode_t;
//		memcpy(nextDfihsNode->parentNode,dfihsNode,sizeof(dfihsnode_t));
//		tmpDfihsNode->alreadyFinishTaskTable.resize(tmpPAlreadyTaskTable.size());
//		copy(tmpPAlreadyTaskTable.begin(),tmpPAlreadyTaskTable.end(),tmpDfihsNode->alreadyFinishTaskTable.begin());
//		memcpy(nextDfihsNode->parentNode,tmpDfihsNode,sizeof(dfihsnode_t));
//		memcpy(nextDfihsNode->parentNode,dfihsNode,sizeof(dfihsnode_t));

		nextDfihsNode->parentNode = dfihsNode;
		nextDfihsNode->parentNode->currentTime = tmpFinishTime;
		//cout << nextDfihsNode->parentNode->currentTime << endl;
		//selectedPointerを生成
		vector<int> sourceSelectedPointer;
		for(int j = 1;j <= (int)dfihsNode->readyTaskTable.size();j++){
			sourceSelectedPointer.push_back(j);
		}
		
		
		//nextDfihsNode->selectedTaskPointer = dictionaryOrder(sourceSelectedPointer,i+1);
		

		vector<int> tmpExecuteTask;
		tmpExecuteTask.reserve(CORE_NUM);
		int spcounter = 0;
		//使用しているコア情報を追加
		for(int j = 0;j < CORE_NUM;j++){
			if(coreInfo[j]->executeTaskNum != -1){
				nextDfihsNode->coreInfo.push_back(coreInfo[j]);
				tmpExecuteTask.push_back(coreInfo[j]->executeTaskNum);
				//cout << "korejikkousareteiru" << endl;
			}else{
				spcounter++;
			}
		}
		cout << "spcounter is " << spcounter << endl;
		nextDfihsNode->selectedTaskPointer = createSelectedPointer(sourceSelectedPointer,spcounter,i+1);

		//readyTaskTableからexecuteTaskを決定

		//tmpExecuteTask = dfihsNode->executeTaskTable;
		int count = 0;//selected pointer用
		nextDfihsNode->alreadyFinishTaskTable.resize(tmpPAlreadyTaskTable.size());
		copy(tmpPAlreadyTaskTable.begin(),tmpPAlreadyTaskTable.end(),nextDfihsNode->alreadyFinishTaskTable.begin());
		dfihsNode->alreadyFinishTaskTable.resize(tmpPAlreadyTaskTable.size());
		copy(tmpPAlreadyTaskTable.begin(),tmpPAlreadyTaskTable.end(),dfihsNode->alreadyFinishTaskTable.begin());
		if((int)dfihsNode->readyTaskTable.size() != 0){//実行タスクアリでreadyTaskTableが空の時時間を経過させる必要がある
			for(int j = 0;j < CORE_NUM;j++){
				if(coreInfo[j]->executeTaskNum == -1){
					int tmpExecuteTaskNum = dfihsNode->readyTaskTable[nextDfihsNode->selectedTaskPointer[count] - 1];
					cout << "tmpnum:" <<tmpExecuteTaskNum << endl;
					int tmpFinishTime = 100;
					tmpFinishTime = dfihsNode->currentTime + getNodePerformance(blp_list[tmpExecuteTaskNum].getblnode(),1);
					coreinfo_t *tmpCoreInfo;
					tmpCoreInfo = new coreinfo_t;
					tmpCoreInfo->executeTaskNum = tmpExecuteTaskNum;
					tmpCoreInfo->finishTime = tmpFinishTime;
					nextDfihsNode->coreInfo.push_back(tmpCoreInfo);
					//nextDfihsNode->alreadyFinishTaskTable.push_back(tmpExecuteTaskNum);
					//nextDfihsNode->executeTaskTable.push_back(tmpExecuteTaskNum);
					cout << tmpExecuteTaskNum << endl;
					tmpExecuteTask.push_back(tmpExecuteTaskNum);
					count++;
					//ループを終了する場合
					if((int)dfihsNode->readyTaskTable.size() == count){
						cout << "----loop owari----" << endl;
						if(count != idleCoreNum){
							for(int k = count;k < CORE_NUM;k++){
								coreinfo_t *tmpCoreInfo;
								tmpCoreInfo = new coreinfo_t;
								tmpCoreInfo->executeTaskNum = -1;
								tmpCoreInfo->finishTime = FTIME;
								nextDfihsNode->coreInfo.push_back(tmpCoreInfo);
							}
						}
						goto L4;
					}
				}
			}
		}else{
			for(int j = (int)nextDfihsNode->coreInfo.size();j < CORE_NUM;j++){
				coreinfo_t *tmpCoreInfo;
				tmpCoreInfo = new coreinfo_t;
				tmpCoreInfo->executeTaskNum = -1;
				tmpCoreInfo->finishTime = FTIME;
				nextDfihsNode->coreInfo.push_back(tmpCoreInfo);
			}
		}
		L4:
		//}
		//readyTaskTableを更新

		//各必要情報を追加したnextDfihsNodeをdfihsTreeに追加
		//再帰呼出し（readyTaskTableが空でなかったら）
		//コアごとの終了タイミング
		//この再帰関数の引数に空いているコア数じゃなくてcoreInfo渡せば解決するかなー
		//dfihs法的にはコアが空いた時点で次の処理を行っていくはず
		vector<coreinfo_t*> idleCoreInNextStep; 
		//coreInfoを早く終わる順にソート
		//cout << "before:" << endl;
		//for(int j = 0;j < (int)nextDfihsNode->coreInfo.size();j++)
			//cout << nextDfihsNode->coreInfo[j]->executeTaskNum << endl;
		sort(nextDfihsNode->coreInfo.begin(),nextDfihsNode->coreInfo.end(),compCoreInfo);
		//cout << "after:" << endl;
		//for(int j = 0;j < (int)nextDfihsNode->coreInfo.size();j++)
			//cout << nextDfihsNode->coreInfo[j]->executeTaskNum << endl;

		//次ループのために各種テーブルを退避
		vector<int> tmpAlreadyTaskTable;
		tmpAlreadyTaskTable.resize(nextDfihsNode->alreadyFinishTaskTable.size());
		copy(nextDfihsNode->alreadyFinishTaskTable.begin(),nextDfihsNode->alreadyFinishTaskTable.end(),tmpAlreadyTaskTable.begin());
		vector<int> tmpReadyTaskTable;
		tmpReadyTaskTable.resize(nextDfihsNode->readyTaskTable.size());
		copy(nextDfihsNode->readyTaskTable.begin(),nextDfihsNode->readyTaskTable.end(),tmpReadyTaskTable.begin());
//		nextDfihsNode->executeTaskTable.resize(tmpExecuteTaskTable.size());
//		copy(tmpExecuteTaskTable.begin(),tmpExecuteTaskTable.end(),nextDfihsNode->executeTaskTable.begin());

		//再帰呼出しループ
		for(int j = 0;j < (int)nextDfihsNode->coreInfo.size();j++){
			idleCoreInNextStep.clear();
			idleCoreInNextStep.reserve(CORE_NUM);
			if(nextDfihsNode->coreInfo[j]->finishTime == FTIME)
				continue;
			int tmpCallTime = nextDfihsNode->coreInfo[j]->finishTime;
			if(j > 0){
				if(tmpCallTime == nextDfihsNode->coreInfo[j-1]->finishTime){
					continue;
				}
			}
			vector<int>::iterator eitr = find(nextDfihsNode->executeTaskTable.begin(),nextDfihsNode->executeTaskTable.end(),nextDfihsNode->coreInfo[j]->executeTaskNum);
			if(eitr != nextDfihsNode->executeTaskTable.end())
				eitr = nextDfihsNode->executeTaskTable.erase(eitr);

			//executeTasktableのクリア
			nextDfihsNode->executeTaskTable.clear();

			//あるコアの時間にした時に終わっていないタスクをそのまま残留させる
			for(int k = 0;k < (int)nextDfihsNode->coreInfo.size();k++){
				nextDfihsNode->executeTaskTable.push_back(nextDfihsNode->coreInfo[k]->executeTaskNum);
				if(tmpCallTime >= nextDfihsNode->coreInfo[k]->finishTime && tmpCallTime != FTIME){
					//cout << "task kousin:" << nextDfihsNode->coreInfo[k]->executeTaskNum << endl;
					coreinfo_t *tmpCoreInfo;
					tmpCoreInfo = new coreinfo_t;
					tmpCoreInfo->executeTaskNum = -1;
					tmpCoreInfo->finishTime = FTIME;
					idleCoreInNextStep.push_back(tmpCoreInfo);
					nextDfihsNode->alreadyFinishTaskTable.push_back(nextDfihsNode->coreInfo[k]->executeTaskNum);
					nextDfihsNode->readyTaskTable = updateReadyTaskTable(dfihsNode,nextDfihsNode->coreInfo[k]->executeTaskNum);

					vector<int>::iterator ritr = find(nextDfihsNode->readyTaskTable.begin(),nextDfihsNode->readyTaskTable.end(),nextDfihsNode->coreInfo[k]->executeTaskNum);
					if(ritr != nextDfihsNode->readyTaskTable.end())
						ritr = nextDfihsNode->readyTaskTable.erase(ritr);
	//				for(int l = 0;l < (int)nextDfihsNode->readyTaskTable.size();l++)
						//cout << nextDfihsNode->readyTaskTable[l] << endl;
//					vector<int>::iterator eeitr = find(nextDfihsNode->executeTaskTable.begin(),nextDfihsNode->executeTaskTable.end(),nextDfihsNode->coreInfo[k]->executeTaskNum);
//					if(eeitr != nextDfihsNode->executeTaskTable.end())
//						eeitr = nextDfihsNode->executeTaskTable.erase(eeitr);
//						}
				}else{
					//残留タスクをalreadyfinishtasktableから削除
					vector<int>::iterator aitr = find(nextDfihsNode->alreadyFinishTaskTable.begin(),nextDfihsNode->alreadyFinishTaskTable.end(),nextDfihsNode->coreInfo[k]->executeTaskNum);
					if(aitr != nextDfihsNode->alreadyFinishTaskTable.end())
						aitr = nextDfihsNode->alreadyFinishTaskTable.erase(aitr);
					vector<int>::iterator ritr = find(nextDfihsNode->readyTaskTable.begin(),nextDfihsNode->readyTaskTable.end(),nextDfihsNode->coreInfo[k]->executeTaskNum);
					if(ritr != nextDfihsNode->readyTaskTable.end())
						ritr = nextDfihsNode->readyTaskTable.erase(ritr);
					coreinfo_t *tmpCoreInfo;
					tmpCoreInfo = new coreinfo_t;
					tmpCoreInfo->executeTaskNum = nextDfihsNode->coreInfo[k]->executeTaskNum;
					tmpCoreInfo->finishTime = nextDfihsNode->coreInfo[k]->finishTime;
					idleCoreInNextStep.push_back(tmpCoreInfo);
				}
				cout << "nodesize:" << (int)nextDfihsNode->alreadyFinishTaskTable.size() << endl;
				printCoreInfo(nextDfihsNode->coreInfo);
				//コアの終了タイミングが同じ場合（暫定的な処置）
			}
			//次ノード呼び出し時の時間情報をnextDfihsNodeに追加
			nextDfihsNode->currentTime = tmpCallTime;
			//cout << "currentTime:" << tmpCallTime << endl;
			nextDfihsNode->parentNode->currentTime = tmpFinishTime;
			//printDfihsNode(nextDfihsNode);
			//printCoreInfo(idleCoreInNextStep);
			if((int)nextDfihsNode->alreadyFinishTaskTable.size() != (int)blnode_priority_list.size()){
				cout << nextDfihsNode->parentNode->currentTime << endl;
				addDfihsNodeToTree(nextDfihsNode,idleCoreInNextStep);
				nextDfihsNode->currentTime = tmpFinishTime;
				nextDfihsNode->alreadyFinishTaskTable.resize(tmpAlreadyTaskTable.size());
				copy(tmpAlreadyTaskTable.begin(),tmpAlreadyTaskTable.end(),nextDfihsNode->alreadyFinishTaskTable.begin());
			}
		}//end of for(int j = 0;j < (int)nextDfihsNode->coreInfo.size();j++)
		if((int)nextDfihsNode->readyTaskTable.size() == 0 && id < 2000){
			//最後の実行時間の設定
			int finishTime = 0;
			for(int j = 0;j < (int)nextDfihsNode->coreInfo.size();j++){
				if(nextDfihsNode->coreInfo[j]->finishTime == FTIME)
					continue;
				if(finishTime < nextDfihsNode->coreInfo[j]->finishTime){
					finishTime = nextDfihsNode->coreInfo[j]->finishTime;
				}
			}
			if(finishTime == 0 && (int)nextDfihsNode->alreadyFinishTaskTable.size() != (int)blp_list.size())//暫定的な処置(2017/10/16)
				//finishTime = FTIME;
			nextDfihsNode->currentTime = finishTime;
			cout << "-------------------this node is leaf-------------------" << endl;
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			printDfihsNode(nextDfihsNode);
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			if(interimSolutionTime > nextDfihsNode->currentTime){
				//cout << "kokookitenaikana" << endl;
				interimSolution = nextDfihsNode;
				interimSolutionTime = nextDfihsNode->currentTime;
			}

			return;
			//DFIHSTree::calcResult(nextDfihsNode);
			//exit(1);
		}
		tmpExecuteTask.clear();

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


	
	//UnitDelayの場合、後続のブロック追加をキャンセル
	int unitdelayFlag = 0;
	blnode_T* beforenode;
	for(int i = 0;i < (int)blp_list.size();i++){
		blnode_T* node = blp_list[i].getblnode();
		int taskNum = blp_list[i].getPriorityNum();
		if(taskNum == finishTaskNum){
			if(node->p_block->blocktype() == "UnitDelay"){
				vector<int>::iterator checkFinishTaskNum = find(dfihsNode->alreadyFinishTaskTable.begin(),dfihsNode->alreadyFinishTaskTable.end(),taskNum);
				if(checkFinishTaskNum != dfihsNode->alreadyFinishTaskTable.end()){
					unitdelayFlag = 1;
					beforenode = node->p_in_edge->p_s_node;
				}
			}
		}
	}
	
	if(unitdelayFlag == 1)
		goto L1;
		
	dfihsNode->alreadyFinishTaskTable.push_back(finishTaskNum);
	alreadyFinishTaskTable = dfihsNode->alreadyFinishTaskTable;	
	//unitdelay部分の対応(9/18)

	//cout << "------------------------------------------------------------------------------------------------------------" << endl;
	//printDfihsNode(dfihsNode);

	//alreadyFinishTaskTable.push_back(finishTaskNum);

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

	L1:
	return tmpTaskTable;
}

////////////////////
// compCoreInfo
// [概要] coreinfo内をソートするための条件
// [引数] 比較したいcoreinfo２つ
// [返り値] 差分
// [備考]
// クイックソート関数で比較演算のために使用
bool compCoreInfo(const coreinfo_t *core1,const coreinfo_t *core2)
{
//	coreinfo_t *tmp1,*tmp2;
//	tmp1 = core1;
//	tmp2 = core2;
//
//	int ftime1 = core1->finishTime;
//	int ftime2 = core2->finishTime;
//
//	return ftime1 - ftime2;

	return core1->finishTime == core2->finishTime ? core1->executeTaskNum < core2->executeTaskNum : core1->finishTime < core2->finishTime;
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

////////////////////
// createSelectedPointer
// [概要] dictionaryOrderの可変サイズ対応版
// [引数] readytasktableのs_vec、コアの空き状況のsp_size、ほしい順番のwant_num
// [返り値] selected pointer
// [備考] 
// 
vector<int> createSelectedPointer(vector<int> s_vec, int sp_size, int want_num)
{
	int i;//第一要素を決めた場合の組み合わせ数
	int j = 0;//現在見ている要素

	vector<int> determine_vec;

	int core_num = sp_size;//dictionaryOrderからの変更点
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

////////////////////
// printCoreInfo
// [概要] コアの使用状況等を表示
// [引数] coreinfo(vector)
// [返り値]
// [備考]
//
void printCoreInfo(vector<coreinfo_t*> coreList)
{
	cout << "coreNum:\t" << "executeTask:\t" << "finishTime:\t" << endl;
	for(int i = 0;i < (int)coreList.size();i++){
		cout << i << "\t" << coreList[i]->executeTaskNum << "\t" << coreList[i]->finishTime << endl;
	}
}
