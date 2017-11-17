
#include "dfihs.hxx"

//暫定解
dfihsnode_t* interimSolution;
double interimSolutionTime = FTIME;


////////////////////
// DFIHSTree(コンストラクタ)
// [概要]
// [引数] blp_list
// [返り値] DFIHS tree
// [備考]
//

DFIHSTree::DFIHSTree(vector<BLNPlus> blp_list)
{
	constructFromBlplist(blp_list);
}

////////////////////
// constructFromBlplist
// [概要] DH/IHS法の最初のノードを追加
// [引数] blp_list
// [返り値] success:0 fault:1
// [備考]
//
int DFIHSTree::constructFromBlplist(vector<BLNPlus> blp_list)
{
	dfihsnode_t* tmpDfihsNode;
	blnode_T* tmpBlNode;
	vector<int> tmpTaskTable;

	//最初の時点で実行可能なタスクをtmpTaskTableに追加
	for(int i = 0;i < (int) blp_list.size();i++){
		tmpBlNode = blp_list[i].getblnode();
		//入力のみある場合
		if(tmpBlNode->p_in_edge == NULL && tmpBlNode->p_out_edge != NULL){
			tmpTaskTable.push_back(blp_list[i].getPriorityNum());
		}else if(tmpBlNode->p_block->blocktype() == "UnitDelay"){//UnitDelay等の特殊ブロックに対応
			tmpTaskTable.push_back(blp_list[i].getPriorityNum());
		}
	}
	//tmpTaskTable.push_back(NOP);
	tmpDfihsNode = new dfihsnode_t;

	//必要情報を構造体に追加
	tmpDfihsNode->degree = 0;
	tmpDfihsNode->width.push_back(0);
	vector<int> tmpExecuteTaskTable;
	tmpExecuteTaskTable.push_back(-1);
	cout << "ok" << endl;
	tmpDfihsNode->executeTaskTable = tmpExecuteTaskTable;

	cout << "ok1" << endl;
	//tmpDfihsNode->selectedTaskPointer = NULL;
	tmpDfihsNode->readyTaskTable = tmpTaskTable;
	//tmpDfihsNode->alreadyFinishTaskTable.push_back(-2);
	tmpDfihsNode->currentTime = 0;
	tmpDfihsNode->parentNode = NULL;
	//tmpDfihsNode->slaveNode = NULL;
	//クラス更新
	cout << "ok2" << endl;
	dfihsnode_list.push_back(tmpDfihsNode);
	blnode_priority_list = blp_list;
	//result_dfihsnode_list = NULL;
	cout << "ok3" << endl;
	//空のコア情報を作成
	vector<coreinfo_t*> idleCoreInNextStep;
	coreinfo_t* tmpCoreInfo;
	for(int k = 0;k < CORE_NUM;k++){
		tmpCoreInfo->executeTaskNum = -1;
		tmpCoreInfo->finishTime = FTIME;
		idleCoreInNextStep.push_back(tmpCoreInfo);
	}
	cout << "ok4" << endl;


	addDfihsNodeToTree(tmpDfihsNode,idleCoreInNextStep);
	cout << "exit" << endl;
	vector<BLNPlus>().swap(blp_list);

	return 0;
}

////////////////////
// createDfihsNode
// [概要] DFIHSのTreeにノードを追加
// [引数] 各情報を追加されたdfihsNode
// [返り値] success:1 fault:0
// [備考]
//
dfihsnode_t* createDfihsNode(dfihsnode_t* dfihsNode)
{

}

////////////////////
// calcResult
// [概要] 完成されたDF/IHS treeからパスを取り出す
// [引数] 最短の実行時間を持つ葉ノード
// [返り値] 実行パス
// [備考] Treeが出来上がってからよんでください
//
vector<dfihsnode_t*> calcResult(dfihsnode_t* leafNode)
{
	vector<vector<int> > result;
	vector<dfihsnode_t*> tmpResult;
	vector<dfihsnode_t*>	Result;
	dfihsnode_t* tmpDfihsNode = leafNode;
	int step_count = 0;
	while(tmpDfihsNode != NULL){
		tmpResult.push_back(tmpDfihsNode);
		tmpDfihsNode = tmpDfihsNode->parentNode;
 		step_count++;
	}
	while((int)tmpResult.size() != 0){
		Result.push_back(tmpResult.back());
		tmpResult.pop_back();
	}

	return Result;
}

void printDfihsNode(dfihsnode_t* dfihsNode)
{
	cout << "----------------------" << endl;
	cout << "|    degree: " << dfihsNode->degree << "       |" << endl;
	//cout << "|     width: " << dfihsNode->width << "       |" << endl;
//	cout << "|    width: ";
//	for(int i = 0;i < (int)dfihsNode->width.size();i++){
//		cout << dfihsNode->width[i] << " ";
//	}
	cout << "   |" << endl;
	cout << "|    execute task    |" << endl;
	cout << "|    ";
	for(int i = 0;i < (int)dfihsNode->executeTaskTable.size();i++){
		cout << dfihsNode->executeTaskTable[i] << " ";
	}
	cout << "   |" << endl;
	cout << "|  selected pointer  |" << endl;
	cout << "| SP=[";
	for(int i = 0;i < (int)dfihsNode->selectedTaskPointer.size();i++){
			cout << dfihsNode->selectedTaskPointer[i] << " ";
	}
	cout << "]  |" << endl;
	cout << "|  ready task table  |" << endl;
	cout << "|    ";
	for(int i = 0;i < (int)dfihsNode->readyTaskTable.size();i++){
			cout << dfihsNode->readyTaskTable[i] << " ";
	}
	cout << "    |" << endl;
	cout << "| already task table |" << endl;
	cout << "|    ";
	for(int i = 0;i < (int)dfihsNode->alreadyFinishTaskTable.size();i++){
			cout << dfihsNode->alreadyFinishTaskTable[i] << " ";
	}
	cout << "    |" << endl;
	cout << "time:" << dfihsNode->currentTime << endl;
	cout << "----------------------" << endl;
}

void print_usage()
{
	cout << "usage: ./dfihs [-i]"
	cout << "-i:input-BLXML" << endl;
}


int main(int argc, char *argv[])
{
	//計測用
	struct timeval start,end,tmp;
	gettimeofday(&start,NULL);

	char filename[64];
	int i;//ループ用変数

	//オプション等の処理
	if(argc < 2){
		print_usage();
		exit(1);
	}
	int opts;
	while((opts=getopt(argc,argv,"hf:i:")) != -1){
		switch(opts){
			case 'h':
				print_usage();
				exit(1);
			case 'i':
				cout << optarg << endl;
				strcpy(filename,optarg);
				break;
		}
	}

	//探索される階層
	string subsys;
	//int subsys_size;

	//blnode_T *node;

	//全体のnode list
	vector<blnode_T*> node_list;
	int node_list_size;

	vector<BLNPlus> blgp;
	int blgp_size;

	cout << "start reading." << endl;
	//cout << "filename is " << argv[1] << endl;
	//strcpy(filename,argv[1]);
	Reader xrd(filename); //XMLファイルを読み込み
	cout << "finish reading XML." << endl;

	BLGraph graph(xrd); //BLGragh作成完了
	cout << "finish creating graph." << endl;

	graph = deleteBus(graph);
	graph = deleteNormalSubsystemBlock(graph);
	graph = deleteIoportBlockInSubsystem(graph);

	cout << "trim graph" << endl;

	graph = extractBlocksFromBLGraph(graph,1,4,2);

	node_list = graph.getNodeVector();
	node_list_size = (int)node_list.size();

	//クラス継承したものをリストに追加
	for(i = 0;i < node_list_size;i++){
		BLNPlus tmp_pnode(node_list[i]);
		blgp.push_back(tmp_pnode);
	}
	blgp_size = (int)blgp.size();

	for(i = 0;i < node_list_size;i++){
		critical_path_node cnode = search_critical_path(graph,node_list[i],subsys);
		blgp[i].setid1(cnode.get_cost());
		blgp[i].setid2(getEdgeNum(node_list[i]));
	}

	//id1：CP
	//id2：直属のタスク数

	//各ノードのCPと直属のタスクを生成
	for(i = 0;i < blgp_size;i++){
		cout << (blgp[i].getblnode())->p_block->name() << ":" << blgp[i].getid1() << ":" << blgp[i].getid2() << endl;
	}

	blgp = sortNodesByPriority(blgp);

	//タスク優先度を付与

	for(i = 0;i < blgp_size;i++){
		cout << i << ":" << (blgp[i].getblnode())->p_block->name() << ":" << blgp[i].getid1() << ":" << blgp[i].getid2() << endl;
		blgp[i].setPriorityNum(i);
		//test.push_back(i);
	}
	vector<int> test;
	test.push_back(i);
	cout << test.size() << "a" << CORE_NUM << "a" << calcCombination((int)test.size(),CORE_NUM) << endl;
	for(i = 1;i <= calcCombination((int)test.size(),CORE_NUM);i++){
		vector<int> test2 = dictionaryOrder(test,i);
		cout << "test:" << i << ":";
		for(int j = 0;j < CORE_NUM;j++)
			cout << test2[j] << " ";
		cout << endl;
		sleep(1);
	}

	//DF/IHS法による最適解の探索
	DFIHSTree dfihsTree(blgp);

	cout << "tansaku owari" << endl;

	//calcResult(interimSolution);
	int nodeCount = 1;
	printDfihsNode(interimSolution);
	dfihsnode_t *parentNode = interimSolution->parentNode;
	while(parentNode->degree != 0){
		printDfihsNode(parentNode);
		parentNode = parentNode->parentNode;
		nodeCount++;
	}

	cout << "---------------------------------------------------" << endl;

	//DF/IHS法によるスケジューリング結果からコア割り当て
	vector<dfihsnode_t*> Result = calcResult(interimSolution);
	for(vector<dfihsnode_t*>::iterator di = Result.begin();di != Result.end();di++){
		printDfihsNode(*di);
	}

	for(i = 0;i < blgp_size;i++){
		cout << i << ":" << (blgp[i].getblnode())->p_block->name() << ":" << blgp[i].getid1() << ":" << blgp[i].getid2() << endl;
	}

	blgp = setCoreinfoNum(blgp,Result);

	cout << "Result Core Assignment" << endl;
	for(i = 0;i < blgp_size;i++){
		cout << i << ":" << (blgp[i].getblnode())->p_block->name() << ":" << blgp[i].getblnode()->p_block->peinfo() << endl;
	}

	cout << "output owari" << endl;
	gettimeofday(&end,NULL);
	tmp.tv_sec = end.tv_sec - start.tv_sec;
	if (end.tv_usec < start.tv_usec) {
	   tmp.tv_sec = tmp.tv_sec - 1;
	   tmp.tv_usec = end.tv_usec + 1000000 - start.tv_usec;
	}else {
	   tmp.tv_usec = end.tv_usec - start.tv_usec;
	}
	printf("%10ld.%06ld\n",tmp.tv_sec,tmp.tv_usec);
	return 0;
}
