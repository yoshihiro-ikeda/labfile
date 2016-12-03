//11/29仕様変更
//trace_graphでは
//自ノードの検知→
//コア情報追加→
//次ノードでtrace_graphを呼び出し
//それに伴いallocate_core内でのadd_core_infoを削除

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
int stoi_me(string str);
string itos_me(int num);
int judge_core_info(blnode_T *node,int core);
int add_core_info(blnode_T *node,int core);
void print_usage();


//全体のnode list
vector<blnode_T*> node_list;
int node_list_size;

//flag類
int output_flag = 0;		// output用フラッグ:0の時標準出力へ1の時ファイルへ
int debug_flag = 0;			// debug用フラッグ:周期遅れになっていないブロックの一覧を出力

int main(int argc, char *argv[])
{
  char input_filename[64];
  char output_filename[64];
  char udlist_filename[4][64];
  int i;//ループ用変数
	
	//FILE* fp_out;

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
  while((opts=getopt(argc,argv,"hc:i:o:u:d"))!=-1){
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
  cout << "finish reading XML." << endl;
	
  BLGraph graph(xrd); //BLGragh作成完了
  cout << "finish creating graph." << endl;
	
  node_list = graph.getNodeVector(); //nodeリストを取得
  node_list_size = node_list.size();

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
  // 1コア目の割り当て
  // allocate_coreの引数はグラフ、コア、終点リスト、始点リスト
  allocate_core(graph,0,inport_list,ud_list[0]);

  cout << "core0 finish" << endl;
  
  // 最終ステップのコア割り当てを実行
  // 終端ブロックのリストを作成
  // 終端ブロックを先にcore1に割り当て
  fin_core = core_num - 1;
  for(i = 0;i < node_list_size;i++){
    node = node_list[i];
    if(node->p_out_edge == NULL && judge_core_info(node,-1)){
      str = node->p_block->name();
      outport_list.push_back(str);
      add_core_info(node,fin_core);
      //node_list[i]->p_block->peinfo("1");
    }
  }
  // 2コア目の割り当て
  allocate_core(graph,fin_core,ud_list[0],outport_list);
  
  cout << "core" << core_num - 1 <<  " finish" << endl;
  
  // 3コア以上に分割している場合
  // ud_listが2つ以上あるのでそれに応じてコア割り当てを行っていく
  for(i = 1;i < core_num - 1;i++){
		allocate_core(graph,i,ud_list[i-1],ud_list[i]);
	}
	
	//コア割り当て終了
	
  //node_listのpeinfo情報をコマンドラインに出力orコア割り当て情報を追加したblxmlを出力
	//
  //引数の3つ目が設定されていればその名前のファイルへ出力
  //なければ標準出力へ
  if(output_flag == 0){
    //標準出力へ
    //add_block_infoの入力できる形へ
    for(i = 0;i<node_list_size;i++){
			cout << node_list[i]->p_block->name() << ",," << node_list[i]->p_block->peinfo() << endl;
		}
  }else{
		//blxmlにnode_listの情報を追加
    ofstream result(output_filename);
    if(result.fail()){
      cerr << "failed." << endl;
      exit(0);
    }
    for(i = 0;i<node_list_size;i++){
			result << node_list[i]->p_block->name() << ",," << node_list[i]->p_block->peinfo() << endl;
		}
	}
}


// allocate_core:再帰関数←別で再帰部分は用意
// 入力：BLgraph、コア割り当て用クラス、始点ブロックリスト、終点ブロックリスト
// 入力：c_place 現在探索中のブロック
// sblk_listから再帰関数trace_graphを順次呼び出し
void allocate_core(BLGraph graph,int core,vector<string> sblk_list,vector<string> eblk_list)
{
  int i,j;				//ループ用
  blnode_T *node;	//nodeを一時的に保管するため
  
  for(i = 0;i < (int)sblk_list.size();i++){		//始点ブロックリストの数だけtrace_graphを呼び出す
    for(j = 0;j < node_list_size;j++){	//それらのブロック名がnode_list内のブロック名と合致した場合のみ実行
      node = node_list[j];
      if(node->p_block->name() == sblk_list[i]){
				if(judge_core_info(node,-1)){										//コア割り当てされていなければコア割り当てを実行しtrace_graphを呼び出し
					//add_core_info(node,core);
					trace_graph(graph,core,eblk_list,node);//trace_graphを呼び順次コア割り当て情報を追加
				}else{															//コア割り当てが行われていた場合それが始点であることはないはずなのでwarning
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
		add_core_info(tmp_node,core);
		while(edge != NULL){  // ノードに対する全てのエッジを探索
			tmp_node = edge->p_t_node;  
			// エッジの先に終端ブロック(挿入したUnitDelay)じゃなければ割り当てに追加
			// その後、trace_graphを再帰呼び出し
      tmp_str = tmp_node->p_block->name();
      if(judge_core_info(tmp_node,-1)){
				trace_graph(graph,core,eblk_list,tmp_node);//trace_graphを呼び順次コア割り当て情報を追加
			}else{
				if(judge_core_info(tmp_node,core) == 0){
					cout << "trace_graph: " << tmp_str << endl;
					cout << "warning: already allocate this node to other core!" << endl;
					
				}
			}
			edge = edge->p_out_edge;
		}
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
//変更するのはグローバルにあるnode_list
int add_core_info(blnode_T *node,int core)
{
	string str_tmp;
	//stringstream ss_tmp;
	string blk_name;
	int i;
	
	//ss_tmp << itos_me(core);
	//str_tmp = ss_tmp.str();
	str_tmp = itos_me(core);
	blk_name = node->p_block->name();
	
	for(i = 0;i < node_list_size;i++){
		if(node_list[i]->p_block->name() == blk_name){
			node_list[i]->p_block->peinfo(str_tmp);
			return 1;//途中で見つければ成功として1を返す
		}
	}
	return 0;//最後まで見つけられなければ0を返す
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
