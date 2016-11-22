#include "BLGraph.hxx"
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>

#include <algorithm>

#include <xercesc/dom/DOM.hpp>


using namespace std;
using namespace SimulinkModel;
using namespace SimulinkModel::XSD;
using namespace Simulink;
using namespace Simulink::XML;

using namespace BLG;

//コア割り当て保存クラス
class tmp_core {
public:
  tmp_core(int num) //コンストラクタ
  {
    core_num = num;
  }
  int get_num(){return core_num;}
  void add_block(std::string name){blk_list.push_back(name);}
  void update_path(std::vector <std::string> list){blk_list = list;}
  typedef std::vector<std::string>::iterator iterator;
  iterator vec_begin(){return blk_list.begin();}
  iterator vec_end(){return blk_list.end();}
  int judge_blk(string blk_name)
  {
    vector<string>::iterator blki; 
    blki = find(blk_list.begin(),blk_list.end(),blk_name);
    if(blki == blk_list.end()){
      return 0;
    }else{
      return 1;
    }
  }
private:
  int core_num;
  std::vector <std::string> blk_list;
};

//void allocate_core(BLGraph graph,tmp_core core,vector<string> sblk_list,vector<string> eblk_list);
//void trace_graph(BLGraph graph,tmp_core core,vector<string> eblk_list,blnode_T *node);

void allocate_core(BLGraph graph,vector<string> sblk_list,vector<string> eblk_list);
void trace_graph(BLGraph graph,vector<string> eblk_list,blnode_T *node);


// コアの数だけクラスを生成
// 暫定的に一つ一つ定義
tmp_core core0(0);
tmp_core core1(1);

int main(int argc, char *argv[])
{
  char filename[64];
  int i;//ループ用変数
	
	//FILE* fp_out;
	
  block_T::performance_sequence ps;
  block_T::performance_iterator pi;
	
  blnode_T *node;
  vector<blnode_T*> node_list;
	
  vector<string>::iterator blki;
  vector<string> inport_list;
  vector<string> outport_list;
  vector<string> ud_list;

  string str;
  int p;
	
  if(argc < 3){
    printf("usage: ./tmp_pipeline <input-BLXML(.xml)> <UnitDelay-list(.csv)> [outputfile(.csv)]");
    exit(1);
  }

  cout << "start reading." << endl;
  cout << "filename is " << argv[1] << endl;
  strcpy(filename,argv[1]);
  Reader xrd(filename); //XMLファイルを読み込み
  cout << "finish reading XML." << endl;
	
  BLGraph graph(xrd); //BLGragh作成完了
  cout << "finish creating graph." << endl;
	
  node_list = graph.getNodeVector(); //nodeリストを取得

  strcpy(filename,argv[2]);
  ifstream file(filename);

  //挿入したUnitDelayのリストを取得
  while(getline(file, str)){
    //コメント行は排除
    if( (p = str.find("//")) != str.npos ) continue;
    ud_list.push_back(str);
  }
  // UnitDelayのリストを取得完了


	
  // 再帰的にコア割り当てを決める
  // inportブロック(入力なし)のリストを渡して追加されたUnitDelayにぶつかったら打ち切り
  // 2コア目以降はUnitDelayのリストを渡して次のUnitDelayまたはOutportブロックのリストで打ち切り

  // 1コア目の始点ブロックのリストを作成
  for(i = 0;(unsigned int)i < node_list.size();i++){
    node = node_list[i];
    if(node->p_in_edge == NULL){
      inport_list.push_back(node->p_block->name());
    }
  }
  // 1コア目の割り当て
  allocate_core(graph,inport_list,ud_list);

  cout << "core0 finish" << endl;
  cout << argc << endl;

  //引数の3つ目が設定されていればその名前のファイルへ出力
  //なければ標準出力へ
  if(argc < 4){
    for(blki = core0.vec_begin();blki != core0.vec_end();blki++){
      cout << "dame" << endl;
      cout << *blki << ",," << core0.get_num() << endl;
    }
  }else if(argc == 4){
    strcpy(filename,argv[3]);
    ofstream result(filename);
    
    if(file.fail()){
      cerr << "failed." << endl;
      exit(0);
    }
    for(blki = core0.vec_begin();blki != core0.vec_end();blki++){
      result << *blki << ",," << core0.get_num() << endl;
    }
  }else{}

  // 2コア目の終端ブロックのリストを作成
  // 終端ブロックを先にcore1に割り当て
  for(i = 0;i < node_list.size();i++){
    node = node_list[i];
    if(node->p_out_edge == NULL){
      str = node->p_block->name();
      core1.add_block(str);
      outport_list.push_back(str);
    }
  }
  // 2コア目の割り当て
  allocate_core(graph,ud_list,outport_list);

  //引数の3つ目が設定されていればその名前のファイルへ出力
  //なければ標準出力へ
  if(argc < 3){
    for(blki = core0.vec_begin();blki != core0.vec_end();blki++){
      cout << *blki << ",," << core0.get_num() << endl;
    }
  }else if(argc == 3){
    strcpy(filename,argv[3]);
    ofstream result(filename);
    if(file.fail()){
      cerr << "failed." << endl;
      exit(0);
    }
    for(blki = core1.vec_begin();blki != core1.vec_end();blki++){
      result << *blki << ",," << core1.get_num() << endl;
    }
  }else{}
}


// allocate_core:再帰関数←別で再帰部分は用意
// 入力：BLgraph、コア割り当て用クラス、始点ブロックリスト、終点ブロックリスト
// 入力：c_place 現在探索中のブロック
// sblk_listから再帰関数trace_graphを順次呼び出し
void allocate_core(BLGraph graph,vector<string> sblk_list,vector<string> eblk_list)
{
  int i,j;
  vector<blnode_T*> node_list;
  blnode_T *node;
  vector<string>::iterator blki; // ブロックリスト用のイテレータ

  node_list = graph.getNodeVector(); //nodeリストを取得
  
  for(i = 0;i < sblk_list.size();i++){
    for(j = 0;j < node_list.size();j++){
      node = node_list[j];
      if(node->p_block->name() == sblk_list[i]){
	core.add_block(sblk_list[i]);
	trace_graph(graph,eblk_list,node);
	break;
      }
    }
  }
}

// trace_graph：再帰関数
// 順次tmp_coreクラスにブロックを追加
void trace_graph(BLGraph graph,vector<string> eblk_list,blnode_T *node)
{
  int i;
  vector<blnode_T*> node_list;
  blnode_T *tmp_node;
  bledge_T *edge;
  string tmp_str;

  cout << node->p_block->name() << endl;
  node_list = graph.getNodeVector(); //nodeリストを取得
  tmp_node = node;
  edge = tmp_node->p_out_edge;
  while(edge != NULL){  // ノードに対する全てのエッジを探索
    tmp_node = edge->p_t_node;  
    for(i = 0;i < eblk_list.size();i++){
      // エッジの先に終端ブロック(挿入したUnitDelay)じゃなければ割り当てに追加
      // その後、trace_graphを再帰呼び出し
      tmp_str = tmp_node->p_block->name();
      if(tmp_str != eblk_list[i] && core.judge_blk(tmp_str) == 0){
	core.add_block(tmp_str);
	cout << tmp_str << endl;
	trace_graph(graph,core,eblk_list,tmp_node);
      }else if(core.judge_blk(tmp_str) == 1){
	break;
      }
    }
    edge = edge->p_out_edge;
  }
}

