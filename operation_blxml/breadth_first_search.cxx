//幅優先探索による負荷分散

#include "BLGraph.hxx"
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>

#include <algorithm>

#include <xercesc/dom/DOM.hpp>

#include <unistd.h>

#define DIVIDE 2

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
      id1 = -1;
      id2 = 0;
    }
    int getid1(){return id1;}
    int getid2(){return id2;}
    blnode_T* getblnode(){return node;}
    void setid1(int num){id1 = num;}
    void setid2(int num){id2 = num;}
  private:
    int id1;
    int id2;
    blnode_T* node; 
};

int getNodePerformance(blnode_T *node,int flag);
int set_id_blgp(blnode_T *node,int num);
int get_id_blgp(blnode_T* node);
int setOffset(blnode_T *node,int num);
int getEdgeNum(blnode_T *node);
int getpeinfo(blnode_T *node);
int setpeinfo(blnode_T *node,int num);
int stoi_me(string str);
string itos_me(int num);
void print_node_info(vector<BLNPlus> nl);



vector<BLNPlus> blgp;
int blgp_size;

int main(int argc, char *argv[])
{
  char filename[64];
  int cost;//pathのコスト計算用
	
  int i,j;//ループ用変数
	
  //FILE* fp_out;
	
  block_T::performance_sequence ps;
  block_T::performance_iterator pi;
	
  blnode_T *node;
	
  //全体のnode list
  vector<blnode_T*> node_list;
  int node_list_size;

  //vector<BLNPlus> blgp;
  vector<BLNPlus> blqueue;
  vector<blnode_T*> wait_queue;
  
  int l_rate,tmp_rate;
  int total_cost = 0;
  int part_cost;
  
  //探索用変数
  blnode_T* current_node;
  blnode_T* next_node;
  bledge_T *out_edge;
  int current_cost = 0;
  int target_cost = 0;
  int current_id = 0;
  int outEdgeNum = 0;
  
  //結果用
  vector<int> idcounter(DIVIDE);
  vector<int> dividepf(DIVIDE);
	  
  cout << "start reading." << endl;
  cout << "filename is " << argv[1] << endl;
  strcpy(filename,argv[1]);
  Reader xrd(filename); //XMLファイルを読み込み
  cout << "finish reading XML." << endl;
	
  BLGraph graph(xrd); //BLGragh作成完了
  cout << "finish creating graph." << endl;
	
  node_list = graph.getNodeVector(); //nodeリストを取得(node_listはグローバル変数なことに注意)
  node_list_size = (int)node_list.size();
  
  //クラス継承したものをリストに追加
  for(i = 0;i < node_list_size;i++){
    BLNPlus tmp_pnode(node_list[i]);
    blgp.push_back(tmp_pnode);
  }
  blgp_size = (int)blgp.size();
  cout << "keisyo kanryo" << endl;
  
  for(i = 0;i < node_list_size;i++){
    node = blgp[i].getblnode();
    if(node->p_in_edge == NULL){
      cout << node->p_block->name() << endl;
    }
  }
  //探索開始ブロックを決定
  for(i = 0;i < node_list_size;i++){
    //if(node_list[i]->p_block->name() == argv[2]){
		if((node_list[i]->p_in_edge == NULL && node_list[i]->p_out_edge != NULL) || node_list[i]->p_block->blocktype() == "UnitDelay"){	
      cout << "starnode:" << node_list[i]->p_block->name() << endl;
      node_list[i]->p_block->peinfo("1");
      blqueue.push_back(node_list[i]);
    }
  }
  
  //ノードの合計処理量を算出
  //サブシステム単位で指定したほうがいい
  for(i = 0;i < node_list_size;i++){
    total_cost += getNodePerformance(node_list[i],1);
  }
  
  //分割したひとつあたりの処理量を算出
  part_cost = total_cost / DIVIDE;
  target_cost = part_cost;
  
  cout << part_cost << ":" << total_cost << endl;
  
  //幅優先探索開始
  //始点ノードが一つならループは一回のみ実行
  //探索を全てblnode上で行う
  //ID付けはblgp上で行う
  //うまく行ったら全てblgp上で行いたい(速そう)2017/02/05
  for(i = 0;i < (int)blqueue.size();i++){
    current_node = blqueue[i].getblnode();
    //setpeinfo(current_node,1);
    wait_queue.push_back(current_node);
	}
	while(!wait_queue.empty()){
		//cout << "tekk" << endl;
		//実行可能ノードを選出
		for(j = 0;j < (int)wait_queue.size();j++){
			current_node = wait_queue[j];
			//cout << wait_queue[j]->p_block->name() << endl;
			bledge_T* inEdge = current_node->p_in_edge;
			int alreadyCheckFlag = 1;
			while(inEdge != NULL){
				blnode_T* search_node = inEdge->p_s_node;
				if(get_id_blgp(search_node) == -1){
					cout << search_node->p_block->name() << endl;
					alreadyCheckFlag = 0;
				}
				inEdge = inEdge->p_in_edge;
			}
			if(alreadyCheckFlag == 1 || wait_queue[j]->p_block->blocktype() == "UnitDelay"){
				cout << "wait:" << j << ":" << wait_queue[j]->p_block->name() << endl;
				wait_queue.erase(wait_queue.begin() + j);
				break;
			}
		}
			
		//デバッグ用
		//cout << current_node->p_block->name() << endl;
		current_cost += getNodePerformance(current_node,1);
		if(current_cost > target_cost){
			current_id++;
			target_cost += part_cost;
		}
		set_id_blgp(current_node,current_id);
		outEdgeNum = getEdgeNum(current_node);
		cout << outEdgeNum << endl;
		out_edge = current_node->p_out_edge;
		for(j = 0;j < outEdgeNum;j++){
			next_node = out_edge->p_t_node;
			//if(getpeinfo(next_node) != 1 && next_node->p_block->name() != argv[3]){
			if(getpeinfo(next_node) != 1 && next_node->p_block->blocktype() != "UnitDelay"){
				next_node->p_block->peinfo("1");
				wait_queue.push_back(next_node);
			}
			out_edge = out_edge->p_out_edge;
		}
		for(j = 0;j < (int)wait_queue.size();j++){
			//cout << wait_queue[j]->p_block->name() << endl;
		}
	}
  
  
  cout << "end" << endl;
  
  print_node_info(blgp);
  
  
  cout << "-----result-----" << endl;
  for(i = 0;i < blgp_size;i++){
    current_node = blgp[i].getblnode();
    idcounter[blgp[i].getid1()]++;
    dividepf[blgp[i].getid1()] += getNodePerformance(current_node,1);
  }
  
  for(i = 0;i < DIVIDE ;i++){
    printf("ID %d : %d\t%d\t\n",i,idcounter[i],dividepf[i]);
  }
  
  cout << "thank you" << endl;
  
  return 0;
}

  //function 幅優先探索(v)
    //v に訪問済みの印を付ける
    //v をキューに追加
    //while キューに要素を含む do
        //v ← キューから取り出す
        //v を処理
        //for each v に接続している頂点 i do
            //if i が未訪問 then
                //i に訪問済みの印を付ける
                //i をキューに追加

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
    || node->p_block->blocktype() == "Mux"
    || node->p_block->blocktype() == "Demux"
    || node->p_block->blocktype() == "Goto"
    || node->p_block->blocktype() == "From"
    ){
      cost = 0;;
    }else{
      cost = 10;
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


//blgpのリストにidを追加
int set_id_blgp(blnode_T *node,int num)
{
  string str_tmp;
  string blk_name;
  int i;
  blnode_T* tmp_node;
  
  str_tmp = itos_me(num);
  blk_name = node->p_block->name();
  
  for(i = 0;i < blgp_size;i++){
    tmp_node = blgp[i].getblnode();
    if(tmp_node->p_block->name() == blk_name){
      //blgp[i]->p_block->peinfo(str_tmp);
      blgp[i].setid1(num);
      return 1;//途中で見つければ成功として1を返す
    }
  }
  
  return 0;//最後まで見つけられなければ0を返す
}

int get_id_blgp(blnode_T* node)
{
	int i;
  blnode_T* tmp_node;
  
  string blk_name = node->p_block->name();
  
	for(i = 0;i < blgp_size;i++){
    tmp_node = blgp[i].getblnode();
    if(tmp_node->p_block->name() == blk_name){
      //blgp[i]->p_block->peinfo(str_tmp);
      int num = blgp[i].getid1();
      return num;//途中で見つければ成功として1を返す
    }
  }
  return -1;
}

// ノードを入力としてエッジの本数を返す
int getEdgeNum(blnode_T *node)
{
  bledge_T *edge;
  //blnode_T *tmp_node;
  int count = 0;
  
  edge = node->p_out_edge;
  while(edge != NULL){
    count++;
    edge = edge->p_out_edge;
  }
  return count;
}

int getpeinfo(blnode_T *node)
{
  //peinfo操作用の変数
  stringstream ss_tmp;
  int i_tmp;
  string str_tmp;
  
  //peinfo情報読み取り
  ss_tmp << node->p_block->peinfo();
  i_tmp = stoi_me(ss_tmp.str());
  ss_tmp.str("");
  ss_tmp.clear(stringstream::goodbit);
  
  return i_tmp;
}

//int setpeinfo(blnode_T *node,int num)
//{
  //string str_tmp;
  //string blk_name;
  //int i;
  
  //str_tmp = itos_me(num);
  //blk_name = node->p_block->name();
  
  //for(i = 0;i < node_list_size;i++){
    //if(node_list[i]->p_block->name() == blk_name){
      //node_list[i]->p_block->peinfo(str_tmp);
      //return 1;//途中で見つければ成功として1を返す
    //}
  //}
  
  //return 0;//最後まで見つけられなければ0を返す
//}

//string型をint型にして返す
int stoi_me(string str)
{
  return atoi(str.c_str());
}

//int型をstring型にして返す
string itos_me(int num)
{
  std::ostringstream stream;
  stream << num;
  string result = stream.str();
	
  return result;
}

void print_node_info(vector<BLNPlus> nl)
{
  int i;
  blnode_T* node;
  
  //ここにファイル出力機構を追加
  char filename[64] = "offset_info.csv";
  std::ofstream writing_file(filename);
  
  for(i = 0;i < (int)nl.size();i++){
    node = nl[i].getblnode();
    writing_file << node->p_block->name() << ",," << nl[i].getid1() << endl;
  }
}
