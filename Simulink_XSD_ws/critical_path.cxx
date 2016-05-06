#include "BLGraph.hxx"
#include <iostream>
#include <fstream>
#include <memory>

#include <algorithm>

#include <xercesc/dom/DOM.hpp>

#define MAX_CNT 100

using namespace std;
using namespace SimulinkModel;
using namespace SimulinkModel::XSD;
using namespace Simulink;
using namespace Simulink::XML;

using namespace BLG;

int max_cost = 0;
vector<string> max_path;


void sum_path(BLGraph graph,blnode_T *node,vector<string> blk_list,int cost,int loop_flag);
int judge_blk(vector<string> blk_list,string blk_name);  

int main(int argc, char *argv[])
{
	char filename[64];
	int cnt = 0;
	int cost = 0;//pathのコスト計算用
	
	block_T::performance_sequence ps;
	block_T::performance_iterator pi;
		
	vector<string>::iterator blki;
	  
	cout << "start reading." << endl;
	cout << "filename is " << argv[1] << endl;
	strcpy(filename,argv[1]);
	Reader xrd(filename); //XMLファイルを読み込み
	cout << "finish reading XML." << endl;
	
	BLGraph graph(xrd); //BLGragh作成完了
	cout << "finish creating graph." << endl;
	
	//path一つに対してコストを計算
	// p_out_edgeをたどりつづけるテスト
	vector<blnode_T*> node_list(graph.getNodeVector());
	blnode_T *node = node_list[0];
	cout << "node: " << node->p_block->name() << endl;
	cout << " in_addr: " << node->p_in_edge << endl;
	cout << "out_addr: " << node->p_out_edge << endl;
	while(node->p_out_edge != NULL && cnt++ < MAX_CNT){
		node = node->p_out_edge->p_t_node;
		cout << "node: " << node->p_block->name() << endl;
		cout << "type:" << node->p_block->blocktype() << endl;
		if(	node->p_block->blocktype() != "Inport" &&
			node->p_block->blocktype() != "Mux"
			){
			ps = node->p_block->performance();
			for(pi = ps.begin();pi != ps.end();pi++){
				if(pi->type() == "task"){
					cost += (int)(pi->typical());
				}
			}
		}
		cout << node->p_block->name() << ": " << cost << endl;
	}
	cout << "cost:" << cost << endl;
	
	//再帰文を用いた全パスのコスト計算
	//node = node_list[0];
	cout << "start node" << node->p_block->name() << endl;
	//FILE* fp_out = freopen("linelist.dat", "w", stdout);
	vector<string> blk_list;
	//sum_path(graph,node,blk_list,0,0);
	
	//すべての探索開始ブロックからのクリティカル・パスを探索
	int i = 0;
	while(node_list[i] != NULL){
		node = node_list[i];
		cout << "start node" << i << ": "<< node->p_block->name() << endl;
		if(node->p_block->name() == "UnitDelay"){
			sum_path(graph,node,blk_list,0,0);
		}else if(node->p_block->input().begin() == node->p_block->input().end()){
			sum_path(graph,node,blk_list,0,0);
		}
		i++;
	}

	cout << "owari" << endl;
	cout << "max_cost: " << max_cost <<endl;
	for(blki = max_path.begin();blki != max_path.end();blki++){
			cout << *blki << " -> ";
			//cout << endl;
	}
	//fclose(fp_out);
	return 0;
}

void sum_path(BLGraph graph,blnode_T *node,vector<string> blk_list,int cost,int loop_flag)
{
	bledge_T *edge;
	block_T::performance_sequence ps;
	block_T::performance_iterator pi;
	
	vector<string>::iterator blki;
	
	int tmp_cost = 0;
	
	if(node->p_block->name() == "UnitDelay"){
		ps = node->p_block->performance();
		blk_list.push_back(node->p_block->name());
		for(pi = ps.begin();pi != ps.end();pi++){
			if(pi->type() == "update"){
				cost += (int)(pi->typical());
			}
		}
		if(max_cost < cost){
			max_cost = cost;
			max_path = blk_list;
			//cout << "cost:" << cost << endl;
		}
	}else if(node->p_out_edge != NULL){
		//ループ検知用
		//二回連続でblk_listに登録されているブロックを踏んだら
		//そこでそのパスは探索終了
		if(judge_blk(blk_list,node->p_block->name()) == 1){
			cout << "一度とおりました" << endl;
		}else{
			blk_list.push_back(node->p_block->name());
			edge = node->p_out_edge;
			while(edge != NULL){
				//cout << node->p_block->name() << endl;
				node = edge->p_t_node;
				ps = node->p_block->performance();
				if(ps.begin() == ps.end()){
					//cout << "no performance: " << node->p_block->name() << endl; 
					tmp_cost = cost+1;
				}else{
					for(pi = ps.begin();pi != ps.end();pi++){
						if(pi->type() == "task"){
							//cout << ps.begin()->typical() << endl;
							tmp_cost = cost + (int)(pi->typical());
						}
					}
				}
				//cout << node->p_block->name() << ": " << tmp_cost << endl;
				sum_path(graph,node,blk_list,tmp_cost,loop_flag);
				edge = edge->p_out_edge;
			}
		}
	}else{
		//for(blki = blk_list.begin();blki != blk_list.end();blki++){
			//cout << *blki << " -> ";
			////cout << endl;
		//}
		blk_list.push_back(node->p_block->name());
		ps = node->p_block->performance();
		for(pi = ps.begin();pi != ps.end();pi++){
			if(pi->type() == "task"){
				cost += (int)(pi->typical());
			}
		}
		if(max_cost < cost){
			//cout << "cost:" << cost << endl;
			max_cost = cost;
			max_path = blk_list;
		}
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
