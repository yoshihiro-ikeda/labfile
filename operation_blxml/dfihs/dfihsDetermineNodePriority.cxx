//タスクの優先度を決定するためのクリティカル・パスを探索する関数群

#include "dfihs.hxx"

/* 関数内グローバル変数 */
/* 最長パス保存用 */
critical_path_node cnode(0);
critical_path_node empty(0);
/* 全体のnode list */
vector<blnode_T*> node_list;
int node_list_size;

/* 探索される階層 */
string subsys;
int subsys_size;

////////////////////
// search_critical_path
// [概要] あるノードからの指定された階層内でのクリティカル・パスを探索
// [引数] BLGraph,探索開始ノード,探索階層scp_subsys
// [返り値] criticalpathのクラス
// [備考] 
// search_critical_pathを実行後、earh_node_costをすぐ呼び出してください
// 探索階層を指定しない場合、システム全体で探索をかけます
critical_path_node search_critical_path(BLGraph graph,blnode_T *node,string scp_subsys)
{
  blnode_T *search_node;
  blnode_T *next_node;
  bledge_T *out_edge;
  
  int current_cost = 0;//現在のコスト計算用
  vector<blnode_T*> current_node_list;
  
  int i;
  
  current_cost = getNodePerformance(node,1);
  current_node_list.push_back(node);
  cnode = empty;
  
  node_list = graph.getNodeVector();   
  node_list_size = (int)node_list.size();
  
  subsys = scp_subsys;
  subsys_size = (int)scp_subsys.size();
  
  //各始点ブロックごとにコストを初期化
  for(i = 0;i != (int)node_list.size();i++){
    node_list[i]->p_block->peinfo("-1");
  }

  out_edge = node->p_out_edge;
  
  if(out_edge == NULL){
		if(node->p_block->blocktype() != "SubSystem"){
			cnode.update_cost(current_cost);
			cnode.update_path(current_node_list);
			return cnode;
		}
		for(i = 0; i < node_list_size;i++){
			search_node = node_list[i];
			if(search_node->p_out_edge != NULL && search_node->p_in_edge == NULL && judge_outside(search_node) == 0){
				sum_path(graph,search_node,current_node_list,current_cost);
			}
    }
  }else{
    while(out_edge != NULL){
			next_node = out_edge->p_t_node;
			sum_path(graph,next_node,current_node_list,current_cost);
			out_edge = out_edge->p_out_edge;
    }
  }
  return cnode;
}



void sum_path(BLGraph graph,blnode_T *node,vector<blnode_T*> current_node_list,int cost)
{
  bledge_T *edge;
  blnode_T *next_node;
	
  int tmp_cost = 0;
  int last_cost = 0;
  
  if(		node->p_out_edge != NULL
				//&& node->p_block->blocktype() != "UnitDelay" 
				//&& node->p_block->blocktype() != "DiscreteIntegrator"
		 ){//あとでUnitDelayに関する記述を追加
    //ループ検知用
    //二回連続でblk_listに登録されているブロックを踏んだら
    //そこでそのパスは探索終了
    //指定されたサブシステム外だったら探索終了
    if(judge_already_search(current_node_list,node) || judge_outside(node)){
			last_cost = getNodePerformance(node,0);
			cost += last_cost;
			if(cnode.get_cost() < cost){//現状のクリティカル・パスより大きければ更新
				cnode.update_cost(cost);
				cnode.update_path(current_node_list);
			}
    }else{
      //エッジの数だけsum_path関数を呼び出し
      edge = node->p_out_edge;
      current_node_list.push_back(node);//次のノードをcurrent_node_listに追加
			tmp_cost = cost + getNodePerformance(node,0);//次のノードのコストを加算
			if(tmp_cost > getpeinfo(node)){
				setpeinfo(node,tmp_cost);
				while(edge != NULL){
					next_node = edge->p_t_node;
					if(!judge_outside(next_node)){
						sum_path(graph,next_node,current_node_list,tmp_cost);
					}
					// 他の探索ルートによるそのノードのコストより高ければ探索続行	
					edge = edge->p_out_edge;//次のループのためにエッジ更新
				}//ループ終了
			}else{
				cout << "finish node" << node->p_block->name() << endl;
				cout << tmp_cost << ":" << getpeinfo(node) << endl;
			}
    }
  }else{ 
		//現在のノードが終端の時
    // 終端ノードのコストを追加
    last_cost = getNodePerformance(node,0);
    cost += last_cost; 
    if(cnode.get_cost() < cost){//現状のクリティカル・パスより大きければ更新
      cnode.update_cost(cost);
      cnode.update_path(current_node_list);
    }
  }
}

int judge_already_search(vector<blnode_T*> current_node_list,blnode_T* node)
{
	int i;
	for(i = 0;i < (int)current_node_list.size();i++){
		if(current_node_list[i]->p_block->name() == node->p_block->name()){
			return 1;
		}
	}
	return 0;
}

//outside ka douka
//soto：1
//in：0
int judge_outside(blnode_T* node)
{
  string current = node->p_block->name();
  string current_sys;
  if((int)current.size() > subsys_size){
    current_sys = current.erase(subsys_size);
  }else{
		return 1;
  }
  
  if(subsys == current_sys || subsys == current){
		return 0;
  }else{
		return 1;
  }
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
    	|| node->p_block->blocktype() == "ToWorkspace"){
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

// ノードを入力としてエッジの本数を返す
// 直属のタスク数をカウントするためには
// outportタグ内のconnectタグの数をカウントしたほうが正確かも
int getEdgeNum(blnode_T *node)
{
  bledge_T *edge;
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

vector<BLNPlus> sortNodesByPriority(vector<BLNPlus> blgp)
{
	vector<BLNPlus>::iterator i;
	vector<BLNPlus>::iterator rem_i;
	vector<BLNPlus>::iterator sort_tmp;
	
	vector<int> sameCpValue;
	
	int count = 0;
	/* クリティカル・パス長でソート */
	sort(blgp.begin(),blgp.end(),BLNPlus::compareNodeId1);
	/* 直属のタスク数でソート */
	for(i = blgp.begin();i != blgp.end();i++){
		cout << ((*i).getblnode())->p_block->name() << endl;
	}
	blgp[1].setid2(3);
	//blgp[2].setid1(427);
	for(i = blgp.begin();i != blgp.end();i++){
		if(i == blgp.begin()){
			rem_i = i;
			continue;
		}
		cout << "------------------------------------------" << endl;
		cout << "i:" << ((*i).getblnode())->p_block->name() << endl;
		//cout << "rem_i:" << ((*rem_i).getblnode())->p_block->name() << endl;
		//CP値が異なるところになったらrem_iからiの一つ前までの間でソート
		if((*i).getid1() != (*rem_i).getid1()){
			cout << "koko" << endl;
			i--;
			cout << "i:" << ((*i).getblnode())->p_block->name() << endl;
			cout << "rem_i:" << ((*rem_i).getblnode())->p_block->name() << endl;
			if((*rem_i).getblnode() != (*i).getblnode()){
				rem_i++;
				sort_tmp = rem_i;
				rem_i--;
				cout << "sort_tmp:" << ((*sort_tmp).getblnode())->p_block->name() << endl;
				if((*sort_tmp).getblnode() == (*i).getblnode()){
					cout << "koko2" << endl;
					if((*rem_i).getid2() < (*i).getid2()){
						iter_swap(rem_i,i);
					}
				}
				else
					sort(rem_i,i,BLNPlus::compareNodeId2);
			}
			i++;
			rem_i = i;
		}
		count++;
	}
	return blgp;
}


