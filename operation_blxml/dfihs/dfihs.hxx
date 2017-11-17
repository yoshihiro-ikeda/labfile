//dfihs法のヘッダファイル
//DF/IHS法
//#include "blg_ctrl.hxx"
#include "BLGraph.hxx"

#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include <xercesc/dom/DOM.hpp>
#include <unistd.h>

#include <time.h>
#include <sys/time.h>


#define CORE_NUM 2
#define NOP -2
#define FTIME 100000

using namespace std;
using namespace SimulinkModel;
using namespace SimulinkModel::XSD;
using namespace Simulink;
using namespace Simulink::XML;

using namespace BLG;

//blnodeクラスを継承
class BLNPlus : public blnode_T{
  public:
    BLNPlus (blnode_T* blnode) //コンストラクタ
    {
      node = blnode;
      costFromNode = -1;
      edgesFromNode = 0;
      nodePriorityNum = -1;
    }
    int getid1(){return costFromNode;}
    int getid2(){return edgesFromNode;}
    int getPriorityNum(){return nodePriorityNum;}
    blnode_T* getblnode(){return node;}
    void setid1(int num){costFromNode = num;}
    void setid2(int num){edgesFromNode = num;}
    void setPriorityNum(int num){nodePriorityNum = num;}
    static bool compareNodeId1(BLNPlus lhs,BLNPlus rhs)
    {
			return lhs.getid1() > rhs.getid1();
		}
		static bool compareNodeId2(BLNPlus lhs,BLNPlus rhs)
    {
			return lhs.getid2() > rhs.getid2();
		}
  private:
    int costFromNode;
    int edgesFromNode;
    int nodePriorityNum;
    blnode_T* node;
};

//最長パス保存用クラス
//dfihsDetermineNodePriorityで使用
class critical_path_node {
public:
  critical_path_node (int num) //コンストラクタ
  {
    cost = num;
  }
  int get_cost(){return cost;}
  int c_node_size(){return (int)c_node_list.size();}
  void update_path(std::vector <blnode_T*> list){c_node_list = list;}
  void update_cost(int new_cost){cost = new_cost;}
  vector<blnode_T*> getNodeList(){return c_node_list;}
private:
  std::vector <blnode_T*> c_node_list;
  int cost;
};

//各探索ノードが持つコア情報
typedef struct CoreInfo_t{
	int executeTaskNum;
	int finishTime;
//	bool operator>(const CoreInfo_t&right)const{
//		return finishTime == right.finishTime ? executeTaskNum > right.executeTaskNum : finishTime > right.finishTime;
//	}
}coreinfo_t;

//DF/IHS法の探索木ノード
typedef struct DfihsNode_t{
	int degree;
	vector<int> width;
	vector<int> executeTaskTable;
	vector<int> selectedTaskPointer;
	vector<int> readyTaskTable;
	vector<int> alreadyFinishTaskTable;
	double currentTime;
	vector<coreinfo_t*> coreInfo;
	struct DfihsNode_t* parentNode;
	vector<struct DfihsNode_t*> slaveNode;
}dfihsnode_t;

//DF/IHS法の探索木
class DFIHSTree
{
	public:
		//string treename;
		//string mdlname;
		vector<dfihsnode_t*> dfihsnode_list;
		vector<BLNPlus> blnode_priority_list;
		vector<dfihsnode_t*> result_dfihsnode_list;
	//public:
		//コンストラクタ
		DFIHSTree(vector<BLNPlus> blp_list);
		//必要関数を随時追加
		int constructFromBlplist(vector<BLNPlus> blp_list);
		dfihsnode_t* createDfihsNode(dfihsnode_t* dfihsNode);

		void addDfihsNodeToTree(dfihsnode_t* dfihsNode,vector<coreinfo_t*> coreInfo);
		vector<int> updateReadyTaskTable(dfihsnode_t* dfihsNode, int finishTaskNum);
		//vector<dfihsnode_t*> calcResult(dfihsnode_t* leafNode);
};

//dfihsDetermineNodePriorityで使用
void sum_path(BLGraph graph,blnode_T *node,vector<blnode_T*> current_node_list,int cost);
int stoi_me(string str);
string itos_me(int num);
critical_path_node search_critical_path(BLGraph graph,blnode_T *node,string scp_subsys);
int judge_already_search(vector<blnode_T*> current_node_list,blnode_T* node);
int judge_outside(blnode_T* node);
int getNodePerformance(blnode_T *node,int flag);
int setpeinfo(blnode_T *node,int num);
int getpeinfo(blnode_T *node);
int getEdgeNum(blnode_T *node);
void print_node_info(vector<blnode_T*> nl);
vector<BLNPlus> sortNodesByPriority(vector<BLNPlus> blnp);

//dfihsOptGraphで使用
BLGraph deleteBus(BLGraph graph);
BLGraph deleteEdgeBetNode(BLGraph graph,blnode_T* node,blnode_T* next_node);
BLGraph reconnectNodes(BLGraph graph,blnode_T* node,blnode_T* next_node);
BLGraph deleteBusNode(BLGraph graph,vector<blnode_T*> node_list);
BLGraph deleteNormalSubsystemBlock(BLGraph graph);
BLGraph deleteIoportBlockInSubsystem(BLGraph graph);
BLGraph deleteConstantBlock(BLGraph graph);


//dfihsCreateTreeで使用
//void addDfihsNodeToTree(DFIHSTree dfihsTree, dfihsnode_t* dfihsNode,vector<coreinfo_t*> coreInfo);
int factorialMethod(int k);
int calcCombination(int n,int k);
vector<int> dictionaryOrder(vector<int> s_vec,int want_num);
//vector<int> updateReadyTaskTable(DFIHSTree dfihsTree,dfihsnode_t* dfihsNode, int finishTaskNum);
bool compCoreInfo(const coreinfo_t *core1,const coreinfo_t *core2);
void printCoreInfo(vector<coreinfo_t*> coreList);
vector<int> createSelectedPointer(vector<int> s_vec, int sp_size, int want_num);

//dfihsSetCoreinfoで使用
vector<BLNPlus> setCoreinfoNum(vector<BLNPlus> blnp,vector<dfihsnode_t*> dfnodeList);

//dfihsForMultirateで使用
vector<string> split(const string& input, char delimiter);
BLGraph extractBlocksFromBLGraph(BLGraph graph, int divid, double rate_l, double rate_s);

//dfihs.cxxで定義
vector<dfihsnode_t*> calcResult(dfihsnode_t* leafNode);
void printDfihsNode(dfihsnode_t* dfihsNode);
void print_usage();
extern dfihsnode_t* interimSolution;
extern double interimSolutionTime;
