//今のところうまく行っていない（３/３０）
//ダイクストラ法による最長パス探索が可能（4/6）

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

void sum_path(BLGraph graph,blnode_T *node,vector<string> blk_list,int cost,int loop_flag);
int judge_blk(vector<string> blk_list,string blk_name);
int stoi_me(string str);
string to_string_me(int num);

//全体のnode list
vector<blnode_T*> node_list;

//最長パス保存用
vector<string> critical_path;
int max_cost;

int main(int argc, char *argv[])
{
	char filename[64];
	int cnt = 0;
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
	cout << "finish reading XML." << endl;
	
	BLGraph graph(xrd); //BLGragh作成完了
	cout << "finish creating graph." << endl;
	
	node_list = graph.getNodeVector(); //nodeリストを取得(node_listはグローバル変数なことに注意)
	
	//これはうまくいった
	node = node_list[0];
	for(j = 0;j != node_list.size();j++){//各始点ブロックごとにコストを初期化
		node_list[j]->p_block->peinfo("-1");
	}
	vector<string> blk_list;
	//sum_path(graph,node,blk_list,0,0);
	
	ofstream ofs("result.dat");
	ofs << "critical path list" << endl;
	ofs.close();
	
	max_cost = 0;
	
	//ダイクストラ法を用いたクリティカル・パス計算
	for(i = 0;i != node_list.size();i++){
		node = node_list[i];
		if(node->p_in_edge == NULL || node->p_block->blocktype() == "UnitDelay"){//入力のないブロック及びUnitDelayのみ始点ブロック
			cout << "start node : " << node->p_block->name() << endl;
			for(j = 0;j != node_list.size();j++){//各始点ブロックごとにコストを初期化
				node_list[j]->p_block->peinfo("-1");
			}
			vector<string> blk_list;
			//開始ブロックのコスト計算
			ps = node->p_block->performance();
			if(ps.begin() == ps.end()){//performanceがない場合
				cost = 0;
			}else{
				for(pi = ps.begin();pi != ps.end();pi++){//performanceがある場合
					if(pi->type() == "task"){
						cost = (int)(pi->typical());
					}
				}
			}
			sum_path(graph,node,blk_list,cost,0);
		}
	}
	cout << "tansaku owari" << endl;
	
	cout << "result : " << max_cost << endl;
	ofstream ofs2("c_path.csv");
	for(blki = critical_path.begin();blki != critical_path.end();blki++){
		cout << *blki << " -> ";
		ofs2 << *blki << endl;
		//cout << endl;
	}
	ofs2.close();
	return 0;
}

void sum_path(BLGraph graph,blnode_T *node,vector<string> blk_list,int cost,int loop_flag)
{
	bledge_T *edge;
	block_T::performance_sequence ps;
	block_T::performance_iterator pi;
	
	vector<string>::iterator blki;
	
	int tmp_cost = 0;
	int i;
	
	stringstream ss_tmp;
	int i_tmp;
	
	//cout << "node: " << node->p_block->name() << endl;
	
	if(node->p_out_edge != NULL && node->p_block->blocktype() != "UnitDelay"){//あとでUnitDelayに関する記述を追加
		//ループ検知用
		//二回連続でblk_listに登録されているブロックを踏んだら
		//そこでそのパスは探索終了
		if(judge_blk(blk_list,node->p_block->name()) == 1){
			cout << "一度とおりました" << endl;
		}else{
			blk_list.push_back(node->p_block->name());
			edge = node->p_out_edge;
			while(edge != NULL){
				node = edge->p_t_node;
				ps = node->p_block->performance();
				if(ps.begin() == ps.end()){//performanceタグがなかった場合
					tmp_cost = cost;
				}else{//performanceタグがあった場合
					for(pi = ps.begin();pi != ps.end();pi++){
						if(pi->type() == "task"){
							tmp_cost = cost + (int)(pi->typical());
						}
					}
				}
				for(i = 0;i != node_list.size();i++){
					ss_tmp << node_list[i]->p_block->peinfo();
					i_tmp = stoi_me(ss_tmp.str());
					ss_tmp.str("");
					ss_tmp.clear(stringstream::goodbit);//ここまでの四行でpeinfoの情報を読み取り
					//対象ノードに現在設定されているコストより現パスのコストが低い場合はそこで打ち切り
					if(node->p_block->name() == node_list[i]->p_block->name() && tmp_cost > i_tmp){
						string str = to_string_me(tmp_cost);
						node_list[i]->p_block->peinfo(str);
						sum_path(graph,node,blk_list,tmp_cost,loop_flag);
					}
				}
				edge = edge->p_out_edge;//次のループのためにエッジ更新
			}
		}
	}else{
		ofstream ofs("result.dat",std::ios::app);
		
		//終端ブロックもしくはUnitDelayブロックにぶつかったらそのブロックのコストを足して表示
		for(blki = blk_list.begin();blki != blk_list.end();blki++){
			ofs << *blki << " -> ";
			//cout << endl;
		}
		ofs << node->p_block->name();
		ps = node->p_block->performance();
		if(node->p_block->blocktype() == "UnitDelay"){
			for(pi = ps.begin();pi != ps.end();pi++){
				if(pi->type() == "update"){
					cost += (int)(pi->typical());
				}
			}
		}else{
			for(pi = ps.begin();pi != ps.end();pi++){
				if(pi->type() == "task"){
					cost += (int)(pi->typical());
				}
			}
		}
		if(max_cost < cost){//現状のクリティカル・パスより大きければ更新
			max_cost = cost;
			critical_path = blk_list;
		}
			
		ofs <<"  "<< "cost:" << cost << endl;
		ofs.close();
	}
}

//blk_list内に指定のブロックが存在しているか判定
//真(入っていたら):1
//偽(入っていなかったら):0
int judge_blk(vector<string> blk_list,string blk_name)
{
	vector<string>::iterator blki;
	
	blki = find(blk_list.begin(),blk_list.end(),blk_name);
	if(blki == blk_list.end()){
		return 0;
	}else{
		return 1;
	}
}

int stoi_me(string str)
{
	return atoi(str.c_str());
}

string to_string_me(int num)
{
	std::ostringstream stream;
	stream << num;
	string result = stream.str();
	
	return result;
}
