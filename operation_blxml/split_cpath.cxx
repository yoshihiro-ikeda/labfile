#include "BLGraph.hxx"
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>

#include <algorithm>

#include <xercesc/dom/DOM.hpp>

#include <unistd.h>

#define RATE_L 0.01
#define RATE_S 0.002


using namespace std;
using namespace SimulinkModel;
using namespace SimulinkModel::XSD;
using namespace Simulink;
using namespace Simulink::XML;

using namespace BLG;

//最長パス保存用クラス
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
  //typedef std::vector<std::string>::iterator iterator;
  //iterator vec_begin(){return blk_list.begin();}
  //iterator vec_end(){return blk_list.end();}
  vector<blnode_T*> getNodeList(){return c_node_list;}
  //void clear_cnode(){c_node_list.swap(empty_node);}
private:
  std::vector <blnode_T*> c_node_list;
  //std::vector <blnode_T*> empty_node;
  int cost;
};

void sum_path(BLGraph graph,blnode_T *node,vector<blnode_T*> current_node_list,int cost);
int stoi_me(string str);
string itos_me(int num);

//12/17追加分
void search_critical_path_for_branch(BLGraph graph,blnode_T *node,int first_flag);
int judge_node_list(blnode_T* node);
//int judge_node_list(vector<blnode_T*> tmp_node_list,string str);
int getNodePerformance(blnode_T *node,int flag);
int setpeinfo(blnode_T *node,int num);
int getpeinfo(blnode_T *node);
int setOffset(blnode_T *node,int num);
int getOffset(blnode_T* node);
int split_path_and_add_coreinfo(vector<blnode_T*> c_node_list,int cost,double rate_l,double rate_s);
int getEdgeNum(blnode_T *node);
void print_node_info(vector<blnode_T*> nl);

//最長パス保存用
//vector<string> critical_path;
//int max_cost;

critical_path_node cnode(0);
critical_path_node empty(0);


//全体のnode list
vector<blnode_T*> node_list;
int node_list_size;

//オフセット設定用のnode_list
vector<blnode_T*> offset_node_list;
int offset_node_list_size;

//コア割り当て済み

int main(int argc, char *argv[])
{
  char filename[64];
  int cost;//pathのコスト計算用
	
  int i,j;//ループ用変数
	
  //FILE* fp_out;
	
  block_T::performance_sequence ps;
  block_T::performance_iterator pi;
	
  blnode_T *node;
	
  vector<string>::iterator blki;
	  
  cout << "start reading." << endl;
  cout << "filename is " << argv[1] << endl;
  strcpy(filename,argv[1]);
  Reader xrd(filename); //XMLファイルを読み込み
  Reader offset_xrd(filename);
  cout << "finish reading XML." << endl;
	
  BLGraph graph(xrd); //BLGragh作成完了
  BLGraph offset_graph(offset_xrd);
  cout << "finish creating graph." << endl;
	
  node_list = graph.getNodeVector(); //nodeリストを取得(node_listはグローバル変数なことに注意)
  offset_node_list = offset_graph.getNodeVector();
  
  node_list_size = (int)node_list.size();
  offset_node_list_size = (int)offset_node_list.size();
  
  //これはうまくいった
  node = node_list[0];
  for(j = 0;j != (int)offset_node_list.size();j++){//各始点ブロックごとにコストを初期化
    offset_node_list[j]->p_block->peinfo("-1");
  }
  
  for(i = 0;i < node_list_size;i++){
    cout << node_list[i]->p_block->name() << endl;
    if(node_list[i]->p_block->name() == "branch_offset_rate210_UnitDelay2"){
      cout << "yes" << endl;
      node = node_list[i];
      search_critical_path_for_branch(graph,node,1);
    }
  }
  cout << "tansaku owari" << endl;
  
  print_node_info(offset_node_list);
  return 0;
}

// 始点ブロックを受け取りそこから最長パスを求める
// split_path関数を呼び出し分割
// 途中分岐箇所があれば再帰的に呼び出し

void search_critical_path_for_branch(BLGraph graph,blnode_T *node,int first_flag)
{
  blnode_T *next_node;
  blnode_T *next_start_node;
  bledge_T *out_edge;
  
  int current_cost = 0;//現在のコスト計算用
  vector<blnode_T*> current_node_list;
  
  double rate_l,rate_s;
  int i;
  
  current_cost = getNodePerformance(node,1);
  current_node_list.push_back(node);
  
  cnode = empty;
  
  cout << "current: "<< node->p_block->name() << endl;
  
  //各始点ブロックごとにコストを初期化
  for(i = 0;i != (int)node_list.size();i++){
    node_list[i]->p_block->peinfo("-1");
    //offset_node_list[i]->p_block->peinfo("-1");
  }
  // クリティカル・パス保存用クラスのリセット
  
  // n回目のクリティカル・パスを探索
  // クリティカル・パスの情報はcpathクラスに格納
  out_edge = node->p_out_edge;
  while(out_edge != NULL){
    next_node = out_edge->p_t_node;
    current_node_list.push_back(next_node);
    sum_path(graph,next_node,current_node_list,current_cost);
    out_edge = out_edge->p_out_edge;
  }
  
  
  //クリティカル・パスを周期比に分割
  //再帰呼び出し時にはrate_lの方は変更されるはず(12/17)
  current_node_list = cnode.getNodeList();
  if(first_flag == 0){
    rate_l = RATE_S * getOffset(current_node_list[(int)current_node_list.size() - 1]);
    rate_s = RATE_S * getOffset(current_node_list[0]);
    //rate_l = current_node_list[(int)current_node_list.size()]->p_block->rate();
  }else{
    rate_l = RATE_L;
    rate_s = RATE_S;
  }
  
  //cout << "koko" << rate_l << rate_s << endl;
  split_path_and_add_coreinfo(cnode.getNodeList(),cnode.get_cost(),rate_l,rate_s);
  //cout << "koko1" << rate_l << rate_s << endl;
  //デバッグ用
  //print_node_info(offset_node_list);
  //print_node_info(current_node_list);
  
  //次にクリティカル・パス上に分岐が存在した場合
  //クリティカル・パスに無いノードに対して再帰呼出し
  cout << current_node_list.size() << endl;
  for(i = 0;i < (int)current_node_list.size();i++){
    if(getEdgeNum(current_node_list[i]) > 1){
      out_edge = current_node_list[i]->p_out_edge;
      while(out_edge != NULL){
	next_start_node = out_edge->p_t_node;
	if(i + 1 != (int)current_node_list.size()){
	  if(current_node_list[i+1]->p_block->name() != next_start_node->p_block->name()){
	    //接続先がコア割り当てされていないことを追加したほうがいいかも...
	    cout << "next!" << endl;
	    setOffset(next_start_node,getOffset(current_node_list[i]));
	    search_critical_path_for_branch(graph,next_start_node,0);
	  }
	}
	out_edge = out_edge->p_out_edge;
      }
    }
  }
  cout << "finish node: " << node->p_block->name() << endl;
  //print_node_info(offset_node_list);
}


void sum_path(BLGraph graph,blnode_T *node,vector<blnode_T*> current_node_list,int cost)
{
  bledge_T *edge;
  blnode_T *next_node;
	
  int tmp_cost = 0;
  int last_cost = 0;
  int i;
	
  //cout << "node: " << node->p_block->name() << endl;

  if(node->p_out_edge != NULL && node->p_block->blocktype() != "UnitDelay"){//あとでUnitDelayに関する記述を追加
    //ループ検知用
    //二回連続でblk_listに登録されているブロックを踏んだら
    //そこでそのパスは探索終了
    if(judge_node_list(node)){
      //cout << "一度とおりました" << endl;
      //cout << node->p_block->name() << endl;
      last_cost = getNodePerformance(node,0);
      cost += last_cost;
    
      if(cnode.get_cost() < cost){//現状のクリティカル・パスより大きければ更新
	cnode.update_cost(cost);
	cnode.update_path(current_node_list);
      }
    }else{
      //エッジの数だけsum_path関数を呼び出し
      edge = node->p_out_edge;
      while(edge != NULL){
	next_node = edge->p_t_node;
	current_node_list.push_back(next_node);//次のノードをcurrent_node_listに追加
	tmp_cost = cost + getNodePerformance(next_node,0);//次のノードのコストを加算
	
	// 他の探索ルートによるそのノードのコストより高ければ探索続行
	if(tmp_cost > getpeinfo(next_node)){
	  setpeinfo(next_node,tmp_cost);
	  //cout << "次回のループ呼び出しノードは" << next_node->p_block->name() << endl;
	  sum_path(graph,next_node,current_node_list,tmp_cost);
	}
	edge = edge->p_out_edge;//次のループのためにエッジ更新
      }//ループ終了
    }
  }else{ //現在のノードが終端の時
    // 終端ノードのコストを追加
    last_cost = getNodePerformance(node,0);
    cost += last_cost;
    
    if(cnode.get_cost() < cost){//現状のクリティカル・パスより大きければ更新
      cnode.update_cost(cost);
      cnode.update_path(current_node_list);
    }
  }
}

//入力のブロックがすでにオフセットを割り当てられているかを判定
//ある：1
//ない：0
int judge_node_list(blnode_T* node)
{
  int i;
  
  for(i = 0;i < (int)offset_node_list.size();i++){
    if(offset_node_list[i]->p_block->name() == node->p_block->name()){
      //cout << offset_node_list[i]->p_block->name() << ": " << offset_node_list[i]->p_block->peinfo() << endl;
      if(getpeinfo(offset_node_list[i]) != -1){
	return 1;
      }
    }
  }
  return 0;
}

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

// 入力のクリティカル・パスのノードリストをレー卜比で分割
// 計算されたオフセット値をpeinfoに追加
// うまく行ったら分割数を返す（いる！？）
int split_path_and_add_coreinfo(vector<blnode_T*> c_node_list,int cost,double rate_l,double rate_s)
{
  int i;
  int d_number; 	// 分割数
  int d_cost; 		// 分割した際のコスト
  
  int current_cost = 0;	//ループ中のコスト計算用
  int current_offset = 0;
  
  double tmp;
  
  tmp = (rate_l - rate_s) / RATE_S;
  
  //tmp = rate_l / rate_s;
  d_number = (int)tmp;
  //if(d_number != 0){
    //d_cost = cost / d_number;
  //}
  d_cost = cost / (d_number + 1);
  current_offset = rate_s / RATE_S;
  //cout << d_cost <<endl;
  
  for(i = 0;i < (int)c_node_list.size();i++){
    //cout << "current_offset:" << current_offset << endl; 
    if(getOffset(c_node_list[i]) == -1){
      setOffset(c_node_list[i],current_offset);
    }
    if(i == 0){
      current_cost += getNodePerformance(c_node_list[i],1);
    }else{
      current_cost += getNodePerformance(c_node_list[i],0);
    }
    if(current_cost > current_offset * d_cost){
      current_offset++;
    }
  }
  
  return d_number;
}

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
    if(node->p_block->blocktype() == "Inport" || node->p_block->blocktype() == "Outport"){
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

// オフセットを設定
// 長周期タスク内のブロックにオフセットを設定
// peinfoに何番目に実行なのかの情報を埋め込み
// クリティカル・パス探索の際のノード重み付けにも使用

int setpeinfo(blnode_T *node,int num)
{
  string str_tmp;
  string blk_name;
  int i;
  
  str_tmp = itos_me(num);
  blk_name = node->p_block->name();
  
  for(i = 0;i < node_list_size;i++){
    if(node_list[i]->p_block->name() == blk_name){
      node_list[i]->p_block->peinfo(str_tmp);
      return 1;//途中で見つければ成功として1を返す
    }
  }
  
  return 0;//最後まで見つけられなければ0を返す
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

int setOffset(blnode_T *node,int num)
{
  string str_tmp;
  string blk_name;
  int i;
  
  str_tmp = itos_me(num);
  blk_name = node->p_block->name();
  
  for(i = 0;i < node_list_size;i++){
    if(offset_node_list[i]->p_block->name() == blk_name){
      offset_node_list[i]->p_block->peinfo(str_tmp);
      return 1;//途中で見つければ成功として1を返す
    }
  }
  
  return 0;//最後まで見つけられなければ0を返す
}

int getOffset(blnode_T* node)
{
  string str_tmp;
  string blk_name;
  int i;
  
  blk_name = node->p_block->name();
  
  int offset_num;
  
  for(i = 0;i < node_list_size;i++){
    if(offset_node_list[i]->p_block->name() == blk_name){
      offset_num = getpeinfo(offset_node_list[i]);
      return offset_num;//途中で見つければ成功として1を返す
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

void print_node_info(vector<blnode_T*> nl)
{
  int i;
  
  for(i = 0;i < (int)nl.size();i++){
    cout << nl[i]->p_block->name() << ",," << nl[i]->p_block->peinfo() << endl;
  }
}
