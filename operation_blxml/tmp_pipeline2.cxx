//11/29仕様変更
//trace_graphでは
//自ノードの検知→
//コア情報追加→
//次ノードでtrace_graphを呼び出し
//それに伴いallocate_core内でのadd_core_infoを削除
//12/06
//始点ブロックリストに入力のないブロックを全て入れたが、それでいいのか
//

#include "BLGraph.hxx"
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>

#include <algorithm>

#include <xercesc/dom/DOM.hpp>

#include <unistd.h>


using namespace std;
using namespace SimulinkModel;
using namespace SimulinkModel::XSD;
using namespace Simulink;
using namespace Simulink::XML;

using namespace BLG;

//プロトタイプ宣言
void allocate_core(BLGraph graph,int core,vector<string> sblk_list,vector<string> eblk_list);
void trace_graph(BLGraph graph,int core,vector<string> eblk_list,blnode_T *node);
void confirm_cycle_lag(BLGraph graph,int core,vector<string> sblk_list,vector<string> eblk_list);
void r_trace_graph(BLGraph graph,int core,vector<string> eblk_list,blnode_T *node);
int compare_forward_reverse_order();
int periodic_deviation_for_multi_input(BLGraph graph,vector<vector<string> > ud_list);
int counts_number_through_UnitDelay(BLGraph graph,vector<string> ud_list,blnode_T *node,int current_ud_num);
int check_vector(vector<int> list);
int stoi_me(string str);
string itos_me(int num);
int judge_core_info(blnode_T *node,int core);
int add_core_info(int flag,blnode_T *node,int core);
void print_core_info(int flag,char *filename);
int count_in_edge(blnode_T *node);
void print_usage();


//全体のnode list
vector<blnode_T*> node_list;
int node_list_size;

//逆トレース検証用
vector<blnode_T*> r_node_list;
int r_node_list_size;

//flag類
int output_flag = 0;		// output用フラッグ:0の時標準出力へ1の時ファイルへ
int debug_flag = 0;			// debug用フラッグ:周期遅れになっていないブロックの一覧を出力

// 2入力遅延検知用リスト
vector<blnode_T*> check_nodes;
vector<int> delay_list;

int main(int argc, char *argv[])
{
  char input_filename[64];
  char output_filename[64];
  char udlist_filename[4][64];
  int i,j;//ループ用変数
	

  block_T::performance_sequence ps;
  block_T::performance_iterator pi;
	
  blnode_T *node;
	
  vector<string>::iterator blki;
  vector<string> inport_list;
  vector<string> outport_list;
  vector<vector<string> > ud_list(3);

  string str;
  int p;
  
  int opts;				// オプション箇所で使用
  
  int core_num;		// コアの総数
  int fin_core;
  
  int file_id = 0;
  
  if(argc < 2){
    //オプションの付け方の説明
    print_usage();
    exit(1);
  }

  //オプション実装
  //dについては未実装
  //d:周期遅れになっていない箇所を抽出
  //c:複数分割対応用オプション
  while((opts=getopt(argc,argv,"hf:c:i:o:u:d"))!=-1){
    switch(opts){

      // 値をとらないオプション
    case 'h':
      print_usage();
      return 0;
    case 'd':
      debug_flag = 1;
      break;
      //以下は全て値を取るオプション
    case 'c':
      cout << "Total number of core is "<< optarg << endl;
      core_num = stoi_me(optarg);
      break;
    case 'i':
      cout << "input-BLXML is " << optarg << endl;
      strcpy(input_filename,optarg);
      break;
    case 'o':
      cout << "output-BLXML is " << optarg << endl;
      strcpy(output_filename,optarg);
      output_flag = 1;
      break;
    case 'u':
      cout << "unitdelay list is " << optarg << endl;
      strcpy(udlist_filename[file_id],optarg);
      file_id++;
      break;
    }
  }
	
  cout << "start reading." << endl;
  cout << "filename is " << input_filename << endl;
  Reader xrd(input_filename); //XMLファイルを読み込み
  Reader r_xrd(input_filename);
  cout << "finish reading XML." << endl;
	
  BLGraph graph(xrd); //BLGragh作成完了
  BLGraph r_graph(r_xrd); //BLGragh作成完了
  cout << "finish creating graph." << endl;
	
  node_list = graph.getNodeVector(); //nodeリストを取得
  node_list_size = node_list.size();
  
  r_node_list = r_graph.getNodeVector();
  r_node_list_size  = r_node_list.size();

  for(i = 0; i < file_id;i++){
    cout << udlist_filename[i] << endl;
    ifstream file(udlist_filename[i]);
    //挿入したUnitDelayのリストを取得
    while(getline(file, str)){
      //コメント行は排除
      if( (p = str.find("//")) != str.npos ) continue;
      ud_list[i].push_back(str);
    }
  }
  
  cout << "finish loading UnitDelay List" << endl;
  // UnitDelayのリストを取得完了
	
  // 各ノードのコア割り当て情報を初期化
  for(i = 0;i != node_list_size;i++){//各始点ブロックごとにコストを初期化
    node_list[i]->p_block->peinfo("-1");
    r_node_list[i]->p_block->peinfo("-1");
  }

  // 再帰的にコア割り当てを決める
  // inportブロック(入力なし)のリストを渡して追加されたUnitDelayにぶつかったら打ち切り
  // 2コア目以降はUnitDelayのリストを渡して次のUnitDelayまたはOutportブロックのリストで打ち切り
  
  // node_list内のpeinfoの情報のみを変更
  // blgraphは一切変更しない

  // 1コア目の始点ブロックのリストを作成
  for(i = 0;i < node_list_size;i++){
    node = node_list[i];
    if(node->p_in_edge == NULL){
      inport_list.push_back(node->p_block->name());
    }
  }
  
  // 最終ステップのコア割り当てを実行
  // 終端ブロックのリストを作成
  // 終端ブロックを先にcore1に割り当て
  fin_core = core_num - 1;
  for(i = 0;i < node_list_size;i++){
    node = node_list[i];
    if(node->p_out_edge == NULL && judge_core_info(node,-1)){
      str = node->p_block->name();
      outport_list.push_back(str);
      add_core_info(1,node,fin_core);
      //add_core_info(0,node,fin_core);
      //node_list[i]->p_block->peinfo("1");
    }
  }
	  
  // 1コア目の割り当て
  // allocate_coreの引数はグラフ、コア、終点リスト、始点リスト
  allocate_core(graph,0,inport_list,ud_list[0]);

  cout << "core0 finish" << endl;
  
  // 2コア目の割り当て
  allocate_core(graph,fin_core,ud_list[0],outport_list);
  
  cout << "core" << core_num - 1 <<  " finish" << endl;
  
  // 3コア以上に分割している場合
  // ud_listが2つ以上あるのでそれに応じてコア割り当てを行っていく
  for(i = 1;i < core_num - 1;i++){
    allocate_core(graph,i,ud_list[i-1],ud_list[i]);
  }
	
  //コア割り当て終了
  
  print_core_info(1,output_filename);
  
  cout << "for debug" << endl;
  for(i = 0; i < (int)ud_list[0].size();i++){
    cout << ud_list[0][i] << endl;
  }
  

  // 正順トレースと逆順トレースを比較
  if(debug_flag == 1){
    // コア0の逆卜レース
    confirm_cycle_lag(r_graph,0,ud_list[0],inport_list);
    
    cout << "finish core0 reverse trace" << endl;
    //print_core_info(0,output_filename);

    if(file_id > 1){//unitdelayリストの数が2つ以上のとき
      for(i = 1;i < core_num - 1;i++){
	//問題発生
	confirm_cycle_lag(r_graph,i,ud_list[i],ud_list[i-1]);
      }
    }
    // コア1の逆卜レース
    confirm_cycle_lag(r_graph,fin_core,outport_list,ud_list[fin_core - 1]);
    for(i = 0; i < node_list_size;i++){
      for(j = 0;j < (int)ud_list[0].size();j++){
	if(ud_list[0][j] == node_list[i]->p_block->name()){
	  add_core_info(0,node_list[i],fin_core);
	}
      }
    }
    
    //最後のコアのみ終端ブロックにコア情報を追加する必要あり
    for(i = 0;i < node_list_size;i++){
      node = node_list[i];
      for(j = 0;j < (int)outport_list.size();j++){
	if(node->p_block->name() == outport_list[j]){
	  add_core_info(0,node,fin_core);
	  //add_core_info(0,node,fin_core);
	  //node_list[i]->p_block->peinfo("1");
	}
      }
    }
    
    cout << "finish core1 reverse trace" << endl;
    //print_core_info(0,output_filename);
    
    //比較実行
    compare_forward_reverse_order();
  }
  periodic_deviation_for_multi_input(graph,ud_list);
}


// allocate_core:再帰関数←別で再帰部分は用意
// 入力：BLgraph、コア割り当て用クラス、始点ブロックリスト、終点ブロックリスト
// 入力：c_place 現在探索中のブロック
// sblk_listから再帰関数trace_graphを順次呼び出し
void allocate_core(BLGraph graph,int core,vector<string> sblk_list,vector<string> eblk_list)
{
  int i,j;		//ループ用
  blnode_T *node;	//nodeを一時的に保管するため
  
  for(i = 0;i < (int)sblk_list.size();i++){		//始点ブロックリストの数だけtrace_graphを呼び出す
    for(j = 0;j < node_list_size;j++){			//それらのブロック名がnode_list内のブロック名と合致した場合のみ実行
      node = node_list[j];
      if(node->p_block->name() == sblk_list[i]){
	if(judge_core_info(node,-1)){	//コア割り当てされていなければコア割り当てを実行しtrace_graphを呼び出し
	  //add_core_info(node,core);
	  trace_graph(graph,core,eblk_list,node);//trace_graphを呼び順次コア割り当て情報を追加
	}else{		//コア割り当てが行われていた場合それが始点であることはないはずなのでwarning
	  cout << "warning: already allocate start_node to other core!" << endl;
	  cout << "cancel calling trace graph with " << sblk_list[i] << endl;
	}
	break;
      }
    }
  }
}

// trace_graph：再帰関数
// 順次node_listのpeinfo情報を正しいコア割り当てに変更
void trace_graph(BLGraph graph,int core,vector<string> eblk_list,blnode_T *node)
{
  int i;
  blnode_T *tmp_node;
  bledge_T *edge;
  string tmp_str;
  
  //自ノードの確認
  for(i = 0;i < (int)eblk_list.size();i++){
    if(node->p_block->name() == eblk_list[i]){
      break;
    }
  }
  //自ノードが終端ブロック内になければ
  //自ノードにコア割り当てを行い、探索を継続
  if(i == (int)eblk_list.size()){
    cout << "startnode: " << node->p_block->name() << endl;		//デバッグ用
    tmp_node = node;
    edge = tmp_node->p_out_edge;
    add_core_info(1,tmp_node,core);
    while(edge != NULL){  // ノードに対する全てのエッジを探索
      tmp_node = edge->p_t_node;  
      // エッジの先に終端ブロック(挿入したUnitDelay)じゃなければ割り当てに追加
      // その後、trace_graphを再帰呼び出し
      tmp_str = tmp_node->p_block->name();
      if(judge_core_info(tmp_node,-1)){
	trace_graph(graph,core,eblk_list,tmp_node);//trace_graphを呼び順次コア割り当て情報を追加
      }else{
	if(judge_core_info(tmp_node,core) == 1){
	  cout << "Core assignment has already terminated normally." << endl;
	}else{
	  //add_core_info(0,tmp_node,core);
	  cout << "trace_graph: " << tmp_str << endl;
	  cout << "warning: already allocate this node to other core!" << endl;
	}
      }
      edge = edge->p_out_edge;
    }
  }
}

// 周期遅れ確認用の逆トレース呼び出し
void confirm_cycle_lag(BLGraph graph,int core,vector<string> sblk_list,vector<string> eblk_list)
{
  int i,j;				//ループ用
  blnode_T *node;	//nodeを一時的に保管するため
  
  for(i = 0;i < (int)sblk_list.size();i++){		//始点ブロックリストの数だけr_trace_graphを呼び出す
    for(j = 0;j < node_list_size;j++){	//それらのブロック名がnode_list内のブロック名と合致した場合のみ実行
      node = r_node_list[j];
      if(node->p_block->name() == sblk_list[i]){
	if(judge_core_info(node,-1)){	//コア割り当てされていなければコア割り当てを実行しtrace_graphを呼び出し
	  //add_core_info(0,node,core);
	  r_trace_graph(graph,core,eblk_list,node);//trace_graphを呼び順次コア割り当て情報を追加
	}else{		//コア割り当てが行われていた場合それが始点であることはないはずなのでwarning
	  if(node->p_in_edge == NULL){
	    cout << "This block has neither input nor output." << endl;
	  }else{
	    cout << "warning: already allocate start_node to other core!" << endl;
	    cout << "cancel calling trace graph with " << sblk_list[i] << endl;
	  }
	}
	break;
      }
    }
  }
}

// 周期遅れ確認用の逆トレース
void r_trace_graph(BLGraph graph,int core,vector<string> eblk_list,blnode_T *node)
{
  int i;
  blnode_T *tmp_node;
  bledge_T *edge;
  string tmp_str;
  
  //自ノードの確認
  for(i = 0;i < (int)eblk_list.size();i++){
    if(node->p_block->name() == eblk_list[i]){
      //add_core_info(0,node,core);
      break;
    }
  }
  //自ノードが終端ブロック内になければ
  //自ノードにコア割り当てを行い、探索を継続
  if(i == (int)eblk_list.size()){
    cout << "startnode: " << node->p_block->name() << endl;		//デバッグ用
    tmp_node = node;
    edge = tmp_node->p_in_edge;
    //add_core_info(0,tmp_node,core);
    while(edge != NULL){  // ノードに対する全てのエッジを探索
      tmp_node = edge->p_s_node;  
      // エッジの先に終端ブロック(挿入したUnitDelay)じゃなければ割り当てに追加
      // その後、trace_graphを再帰呼び出し
      tmp_str = tmp_node->p_block->name();
      if(judge_core_info(tmp_node,-1)){
	add_core_info(0,tmp_node,core);
	r_trace_graph(graph,core,eblk_list,tmp_node);//trace_graphを呼び順次コア割り当て情報を追加
      }else{
	if(judge_core_info(tmp_node,core) == 1){
	  cout << "Core assignment has already terminated normally." << endl;
	}else{
	  add_core_info(0,tmp_node,core);
	  cout << "trace_graph: " << tmp_str << endl;
	  cout << "peinfo " << tmp_node->p_block->peinfo() << endl;
	  cout << "warning: already allocate this node to other core!" << endl;
	}
      }
      edge = edge->p_in_edge;
    }
  }
}

// node_listとr_node_listのコア割り当て結果を比較
int compare_forward_reverse_order()
{
  int i;
  block_T *blk,*cp_blk;
	
  // そんなことはないと思うが,,,
  if(node_list_size != r_node_list_size){
    return 0;
  }
  for(i = 0;i < (int)node_list_size;i++){
    blk = node_list[i]->p_block;
    cp_blk = r_node_list[i]->p_block;
    if(blk->name() == cp_blk->name()){
      if(blk->peinfo() != cp_blk->peinfo()){
	// コア割り当て情報不一致
	cout << "error" << endl;
	cout << blk->name() << endl;
	cout << blk->peinfo() << cp_blk->peinfo() << endl;
      }else if(blk->peinfo() == cp_blk->peinfo()){
	//コア割り当て情報一致
      }else{
	cout << "ok" << endl;
      }
    }else{
      cout << "It can not be..." << endl;
    }
  }
  return 1;
}

// 2入力以上あるブロックの周期ずれ確認
// 問題がなければ1,問題が発生したら0を返す
int periodic_deviation_for_multi_input(BLGraph graph,vector<vector<string> > ud_list)
{
  int i,j;	// ループ用変数
  int tmp;
  vector<string> tmp_ud_list;
  
  vector<int> main_ud_num_list;
  
  int main_error_flag = 0;
  
  cout << "ud_list size" << ud_list.size() << endl;
  
  //ud_listの整形
  //2次元Vectorから1次元Vectorへ
  for(i = 0;i < ud_list.size();i++){
    for(j = 0;j < ud_list[i].size();j++){
      tmp_ud_list.push_back(ud_list[i][j]);
    }
  }
  cout << "finish creating ud_list which is one dimension" << endl;
  
  // 周期遅れ確認対象のノードを抽出
  for(i = 0;i < node_list_size;i++){
    // 入力が2以上のブロックを厳選
    if(count_in_edge(node_list[i]) > 1){
      check_nodes.push_back(node_list[i]);
      delay_list.push_back(-1);
    }
  }
  
  for(i = 0;i < (int)check_nodes.size();i++){
    cout << check_nodes[i]->p_block->name() << endl;
  }
  
  cout << "Extraction of target block completed" << endl;
  
  // 周期遅れ確認関数を呼び出し
  for(i = 0;i < (int)check_nodes.size();i++){
    cout << "check: " << check_nodes[i]->p_block->name() << endl; 
    tmp = counts_number_through_UnitDelay(graph,tmp_ud_list,check_nodes[i],0);
    delay_list[i] = tmp;
    main_ud_num_list.push_back(tmp);
    cout << "ok" << endl;
  }
  cout << check_nodes.size() << "------" << delay_list.size() << endl;
  for(i = 0;i < (int)check_nodes.size();i++){
    if(delay_list[i] != -1){
      cout << i << ": " << check_nodes[i]->p_block->name() << "-----" << delay_list[i] << endl;
    }else{
      cout << "error: " << check_nodes[i]->p_block->name() << "-----10" << endl;
      main_error_flag = 1;
    }
  }
  
  // main_ud_num_listの扱いがおかしいかな
  //main_error_flag = check_vector(main_ud_num_list);
  if(main_error_flag == 1){
    return 1;
  }else{
    return 0;
  }
}

// ud_list内のUnitDelayを通過した数を返す再帰関数
// returnは現在通過したUnitDelayの数
int counts_number_through_UnitDelay(BLGraph graph,vector<string> ud_list,blnode_T *node,int current_ud_num)
{
  int i;
  
  blnode_T *current_node; //確認されるノード
  bledge_T *edge;
  vector<int> ud_num_list;
  vector<int> arr;

  int tmp_num;
  int next_ud_num; // 次の再帰呼出しに渡す遅延数
  string tmp_str;
  
  int prev_flag = 0;
  int exist_ud_flag = 0;

  // デバッグ用
  //cout << node->p_block->name() << endl;
  edge = node->p_in_edge;
  //cout << node->p_block->name() << node->p_block->name() << endl;
  
  next_ud_num = current_ud_num;
  
  while(edge != NULL){
    current_node = edge->p_s_node;
    // 現在のブロックがUnitDelayなら数をインクリメント
    if(current_node->p_block->blocktype() == "UnitDelay"){
      for(i = 0;i < (int)ud_list.size();i++){
	if(current_node->p_block->name() == ud_list[i]){
	  next_ud_num = current_ud_num + 1;
	  exist_ud_flag = 1;
	  break;
	}
      }
    }
    
    // 他の2入力のブロックに当たったら遅延数を再利用
    for(i = 0;i < (int)check_nodes.size();i++){
      if(current_node->p_block->name() == check_nodes[i]->p_block->name() && delay_list[i] != -1){
	prev_flag = 1;
	break;
      }
    }
    
    if(prev_flag){ //既出ブロックに当たったら
      tmp_num = delay_list[i];
      ud_num_list.push_back(tmp_num);
      prev_flag = 0;
    }else if(current_node->p_block->blocktype() == "UnitDelay" && exist_ud_flag == 0){ //ud_listに無いUnitDelayを発見した場合
      ud_num_list.push_back(next_ud_num);
    }else{ //何回も繰り返される処理
      tmp_num = counts_number_through_UnitDelay(graph,ud_list,current_node,next_ud_num);
      ud_num_list.push_back(tmp_num);
    }
    //次ループに向けたエッジ更新
    edge = edge->p_in_edge;
  }

  // それぞれのエッジから辿れるUnitDelayの数が等しければその数を返す
  // デバッグ用の各ポートの遅延数を出力
  if(check_vector(ud_num_list)){// 各入力の遅延数が同じの場合 
    //以下デバッグ用コード
    //cout << "counts... finish" << node->p_block->name() << endl;
    //for(i = 0;i < (int)ud_num_list.size();i++){
    //  cout << ud_num_list[i] << endl;
    //}
    ud_num_list.swap(arr);
    return next_ud_num;
  }else{  //遅延数が異なる場合の処理
    //以下デバッグ用コード
    //cout << "oh..." << node->p_block->name() << endl;
    //for(i = 0;i < (int)ud_num_list.size();i++){
      //cout << ud_num_list[i] << endl;
    //}
    ud_num_list.swap(arr);
    return -1;
  }
}

// vector内の値が全て同じかそうでないかを返す関数
// 全て同じなら1,一つでも異なれば0
// vectorの中身が空なら1
int check_vector(vector<int> list)
{
  int i;
  int tmp_num;
  
  int error_flag = 0;
  
  // listの中身がからの時1を返す
  if((int)list.size() > 0){
    tmp_num = list[0];
  }else{
    return 1;
  }
  
  for(i = 1;i < (int)list.size();i++){
    if(list[i] != tmp_num){
      error_flag = 1;
      break;
    }
  }
  if(error_flag == 1){
    return 0;
  }else if(error_flag == 0){
    return 1;
  }else{
    return 0;
  }
}

//string型からint型へ
int stoi_me(string str)
{
  return atoi(str.c_str());
}

//int型からstring型へ
string itos_me(int num)
{
  std::ostringstream stream;
  stream << num;
  string result = stream.str();
	
  return result;
}

//peinfo確認用
//引数のコア割り当て情報と合っていれば1
//間違っていれば0
int judge_core_info(blnode_T *node,int core)
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
	
  //peinfo情報確認
  if(i_tmp == core){
    return 1;
  }else{
    return 0;
  }
}

//peinfo追加用
//成功すれば1,失敗すれば0を返す
//変更するのはグローバルにあるnode_listとr_node_list
//flag = 1:node_list
//flag = 0:r_node_list
int add_core_info(int flag,blnode_T *node,int core)
{
  string str_tmp;
  //stringstream ss_tmp;
  string blk_name;
  int i;
	
  //ss_tmp << itos_me(core);
  //str_tmp = ss_tmp.str();
  str_tmp = itos_me(core);
  blk_name = node->p_block->name();
	
  if(flag == 1){
    for(i = 0;i < node_list_size;i++){
      if(node_list[i]->p_block->name() == blk_name){
	node_list[i]->p_block->peinfo(str_tmp);
	return 1;//途中で見つければ成功として1を返す
      }
    }
  }else{
    for(i = 0;i < node_list_size;i++){
      if(node_list[i]->p_block->name() == blk_name){
	r_node_list[i]->p_block->peinfo(str_tmp);
	return 1;//途中で見つければ成功として1を返す
      }
    }
  }
  return 0;//最後まで見つけられなければ0を返す
}

// 引数は正順時のコア割り当て情報なら1
// 逆順のコア割り当て情報なら0
void print_core_info(int flag,char *filename)
{
  int i;	//ループ用
  
  //引数の3つ目が設定されていればその名前のファイルへ出力
  //なければ標準出力へ
  if(output_flag == 0){
    //標準出力へ
    //add_block_infoの入力できる形へ
    if(flag == 1){
      for(i = 0;i<node_list_size;i++){
	cout << node_list[i]->p_block->name() << ",," << node_list[i]->p_block->peinfo() << endl;
      }
    }else{
      for(i = 0;i<node_list_size;i++){
	cout << r_node_list[i]->p_block->name() << ",," << r_node_list[i]->p_block->peinfo() << endl;
      }
    }
  }else{
    //blxmlにnode_listの情報を追加
    ofstream result(filename);
    if(result.fail()){
      cerr << "failed." << endl;
      exit(0);
    }
    if(flag == 1){
      for(i = 0;i<node_list_size;i++){
	result << node_list[i]->p_block->name() << ",," << node_list[i]->p_block->peinfo() << endl;
      }
    }else{
      for(i = 0;i<node_list_size;i++){
	result << r_node_list[i]->p_block->name() << ",," << r_node_list[i]->p_block->peinfo() << endl;
      }
    }
  }
}

// 入力側エッジの本数をカウントし返す
int count_in_edge(blnode_T *node)
{
  int count = 0;
  bledge_T *edge;
  
  edge = node->p_in_edge;
  
  while(edge != NULL){
    count++;
    edge = edge->p_in_edge;
  }
  
  return count;
}

//オプションの付け方の説明
//-h:ヘルプ
void print_usage()
{
  cout << "-i:input-BLXML" << endl;
  cout << "-o:output-BLXML" << endl;		
  cout << "-c:コア数(これをもとにUnitDelayリス卜の数を決定)" << endl;
  cout << "-u:unitdelay-list" << endl;
  cout << "-d:デバッグモード" << endl;
}
