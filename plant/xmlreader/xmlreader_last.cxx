#include <iostream>
#include <fstream>
#include <xercesc/dom/DOM.hpp>
#include <xsd/cxx/xml/string.hxx>
#include <vector>
#include <algorithm>
#include "xmlreader.hxx"

int main(int argc, char *argv[])
{
  Simulink::XML::Reader xrd;
  if(argc < 2){
    print_usage(argv[0]);
    return 0;
  }

  /* ファイルに出力用 */
  //FILE* fp_out = freopen("linelist.dat", "w", stdout);
  
  xrd.load_xml(argv[1]);
  if (!xrd){
    cerr << "Failed to load XML" << endl;
    print_usage(argv[0]);
    return 1;
  }
  
  SimulinkModel::XSD::blocks_T root_blks = xrd.xml_blocks();
  
  /* クラス定義
   * state:状態方程式
   * out  :出力方程式
   */
  equation state(0,"green");//no use
  equation out(0,"red"); 
  
  /*それぞれのcsv出力用*/
  SimulinkModel::XSD::blocks_T state_blks = xrd.xml_blocks();//no use
  SimulinkModel::XSD::blocks_T out_blks = xrd.xml_blocks();
  
  /*状態方程式・出力方程式の探索*/
  SimulinkModel::XSD::blocks_T sub_blks = root_blks;

  cout << "start to find update-equations" << endl;
  sub_search_blocks(root_blks,sub_blks);
  cout << "complete" << endl;

  cout << "start to find output-equations" << endl;
  search_output(root_blks,"UnitDelay",&out);
  cout << "complete" << endl;
  /*状態方程式・出力方程式の探索終了*/
  
  /*該当ブロックのpeinfo色情報を付加*/
  /*状態方程式は関数内で実行*/
  //color_set(state_blks,&state);
  color_set(out_blks,&out);

  //fclose(fp_out);
  /*xmlを出力(デバッグ用)*/
  //print_xml(out_blks);
  
  /*色付けツール用にcsvファイルを出力*/
  /*状態方程式は関数内で実行*/
  //print_csv(state_blks,"result_state.csv");
  print_csv(out_blks,"result_out.csv");
}

void print_usage(char *progname)
{
  cerr << "Usage: " << progname << " <input-xml>" << endl;
}

/*xmlファイルに出力する用の関数*/
void print_xml(SimulinkModel::XSD::blocks_T &blks)
{
  xml_schema::namespace_infomap map;
  map["SM"].name = "http://example.com/SimulinkModel"; // namespace is "SM"
  map["SM"].schema = "SimulinkModel.xsd"; // SimulinkModel XML Schema
  ::std::ofstream os ("result.xml");
  blocks (os,blks,map);
}

/*csv形式にして必要情報を出力*/
/*出力方程式で使用*/
void print_csv(SimulinkModel::XSD::blocks_T &blks,const char *filename)
{
  ofstream ofs(filename,ios::app);
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
    if(bi->blocktype() == "SubSystem"){
      SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
      SimulinkModel::XSD::block_T::blocks_iterator bsi;
      ofs << bi->name() << "," << "," << bi->peinfo() << endl;
      for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++){
	print_csv(*bsi,filename);
      }
    }else{
      ofs << bi->name() << "," << "," << bi->peinfo() << endl;
    }
  }
}

/*cout先は各UnitDelay名のcsvファイル*/
/*状態方程式で使用*/
void print_each_csv(SimulinkModel::XSD::blocks_T &blks)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
    if(bi->blocktype() == "SubSystem"){
      SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
      SimulinkModel::XSD::block_T::blocks_iterator bsi;
      cout << bi->name() << "," << "," << bi->peinfo() << endl;
      for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++){
	print_each_csv(*bsi);
      }
    }else{
      cout << bi->name() << "," << "," << bi->peinfo() << endl;
    }
  }
}

/*sumとunitdelayの組み合わせを検索してそこから状態又は出力方程式を探す関数を呼び出す*/
/*SubSystem内探索にも対応*/
/*元のブロックも渡す*/
void sub_search_blocks(SimulinkModel::XSD::blocks_T &blks,SimulinkModel::XSD::blocks_T &sub_blks)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = sub_blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  char filename[64];
  cout << "sub_search_blocks" << endl;
  for( bi = blk_seq.begin(); bi != blk_seq.end(); bi++){
    if( bi->blocktype() == "SubSystem" ){
      SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
      SimulinkModel::XSD::block_T::blocks_iterator bsi;
      for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++)
	sub_search_blocks(blks,*bsi);
    }else{
      if(bi->blocktype() == "Integrator" || bi->blocktype() == "UnitDelay"){
	/*状態方程式はunitdelayから探索*/
	/*状態方程式ごとにstateを作成する(上書きすればいいかな)*/
	/*それを元にここからprint_csvまで呼び出す*/
	equation state(0,"green");
	state.add_blk(bi->name());
	sub_before_block(blks,sub_blks,bi->name(),&state,1);
	cout << "search complete" << endl;
	/*標準出力に今までcsvの内容を出力しそれをcsvに突っ込む*/
	string tmp(bi->name());
	const char *tmp2 = tmp.c_str();
	sprintf(filename,"result_%s.csv",tmp2);
	SimulinkModel::XSD::blocks_T Fcolor = blks;
	streambuf* last = cout.rdbuf();
	color_set(Fcolor,&state);
	ofstream ofs(filename,ios_base::out);
	cout.rdbuf(ofs.rdbuf());
	print_each_csv(Fcolor);
	ofs.close();
	cout.rdbuf(last);
	cout << "write complete" << endl;
      }
    }
  }
}

/*ブロック遡り関数*/
/*状態方程式を検索するために使用*/
/*SubSystem対応*/
void sub_before_block(SimulinkModel::XSD::blocks_T &blks,SimulinkModel::XSD::blocks_T &sub_blks,string target_blk,equation *state,int flag)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = sub_blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  for( bi = blk_seq.begin(); bi != blk_seq.end(); bi++){
    /*SubSystem内の処理*/
    if(bi->name() == target_blk){
      if(bi->blocktype() == "UnitDelay" && flag == 0){
	cout << "UnitDelayにぶつかりました" << endl;
	break;
      }
      if(bi->blocktype() == "Integrator" && flag == 0){
	cout << "Integratorにぶつかりました" << endl;
	break;
      }
      if(bi->blocktype() == "Inport"){
	if(rtnIn(blks,bi->name())){
	  break;
	}
      }
      flag = 0;	
      SimulinkModel::XSD::block_T::input_sequence ip_seq = bi->input();
      SimulinkModel::XSD::block_T::input_iterator ii;
      if(ip_seq.begin() == ip_seq.end() && bi->blocktype() == "Inport"){
	/*SubSystem内のinportに達したら次にSubSystemのinportからまた探索開始*/
	std::string subsys = rtnSubSys(blks,bi->name(),bi->name());
	if(rtnNameToType(blks,subsys) == "SubSystem"){
	  SimulinkModel::XSD::blocks_T up = blks;
	  SimulinkModel::XSD::blocks_T up2 = blks;
	  rtnupSys(up,up2,subsys);
	  select_port_before(blks,up,subsys,bi->name(),state);
	}
      }else{
	/*Inportブロック以外の入力がないブロックにぶつかった場合*/
	for(ii = ip_seq.begin();ii != ip_seq.end();ii++){
	  SimulinkModel::XSD::ioport_T::connect_sequence con_seq = ii->connect();
	  SimulinkModel::XSD::ioport_T::connect_iterator ci;
	  for(ci = con_seq.begin();ci != con_seq.end();ci++){
	    std::string tmp(ci->block());
	    cout << tmp<< endl;
	    if(rtnNameToType(blks,tmp) == "SubSystem"){
	      SimulinkModel::XSD::blocks_T sub = blks;
	      rtnsubBlocks(sub,tmp);
	      std::string con_blk(ci->port());
	      state->add_blk(con_blk);
	      sub_before_block(blks,sub,con_blk,state,0);
	    }
	    else if(state->get_flagval() == 0){
	      state->add_blk(tmp);
	      state->set_flagval();
	      sub_before_block(blks,sub_blks,tmp,state,0);
	    }else{
	      if(state->find_l(tmp) == 0){
		state->add_blk(tmp);
		sub_before_block(blks,sub_blks,tmp,state,0);
	      }
	    }
	  }
	}
      }
      break;
    }
    else if(bi->blocktype() == "SubSystem"){
      SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
      SimulinkModel::XSD::block_T::blocks_iterator bsi;
      for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++){
	sub_before_block(blks,*bsi,target_blk,state,flag);
      }
    }
  }
}

/*subsystemのportに対応するための関数*/
void select_port_before(SimulinkModel::XSD::blocks_T &blks, SimulinkModel::XSD::blocks_T &sub_blks, string sys, string port, equation *state)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = sub_blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
    if(bi->name() == sys){
      SimulinkModel::XSD::block_T::input_sequence ip_seq = bi->input();
      SimulinkModel::XSD::block_T::input_iterator ii;
      for(ii = ip_seq.begin();ii != ip_seq.end();ii++){
	if(ii->port() == port){
	  SimulinkModel::XSD::ioport_T::connect_sequence con_seq = ii->connect();
	  SimulinkModel::XSD::ioport_T::connect_iterator ci;
	  for(ci = con_seq.begin();ci != con_seq.end();ci++){
	    string tmp(ci->block());
	    if(rtnNameToType(blks,tmp) == "SubSystem"){
	      SimulinkModel::XSD::blocks_T sub = blks;
	      cout << "deteru" << endl;
	      rtnsubBlocks(sub,tmp);
	      std::string con_blk(ci->port());
	      state->add_blk(con_blk);
	      sub_before_block(blks,sub,con_blk,state,0);
	    }
	    else if(state->find_l(tmp) == 0){
	      state->add_blk(tmp);
	      sub_before_block(blks,sub_blks,ci->block(),state,0);
	    }
	  }
	}
      }
    }
  }
}

/*出力方程式を検索するために使用*/
/*outputを検索してfollow_block_from_lastを呼び出す*/
void search_output(SimulinkModel::XSD::blocks_T &blks,std::string target_blk,equation *out)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
    if(bi->blocktype() == "Outport"){
      std::string addout(bi->name());
      if(out->get_flagval() == 0){
	out->add_blk(addout);
	out->set_flagval();
      }else if(out->find_l(addout) == 0){
	out->add_blk(addout);
      }
      SimulinkModel::XSD::block_T::input_sequence ip_seq = bi->input();
      SimulinkModel::XSD::block_T::input_iterator ii;
      for(ii = ip_seq.begin();ii != ip_seq.end();ii++){
	SimulinkModel::XSD::ioport_T::connect_sequence con_seq = ii->connect();
	SimulinkModel::XSD::ioport_T::connect_iterator ci;
	for(ci = con_seq.begin();ci != con_seq.end();ci++){
	  std::string tmp(ci->block());
	  if(rtnNameToType(blks,tmp) == target_blk){
	    goto NEXT;
	  }else if(rtnNameToType(blks,tmp) == "SubSystem"){
	    SimulinkModel::XSD::blocks_T sub = blks;
	    cout << "deteru" << endl;
	    rtnsubBlocks(sub,tmp);
	    std::string con_blk(ci->port());
	    out->add_blk(con_blk);
	    sub_out_before_block(blks,sub,con_blk,out);
	  }else if(out->get_flagval() == 0){
	    out->add_blk(tmp);
	    sub_out_before_block(blks,blks,tmp,out);
	    out->set_flagval();
	  }else{
	    if(out->find_l(tmp) == 0){
	      out->add_blk(tmp);
	      sub_out_before_block(blks,blks,tmp,out);
	    }
	  }
	}
      }
    }NEXT: ;
  }
}

/*出力方程式の該当ブロックを探索*/
void sub_out_before_block(SimulinkModel::XSD::blocks_T &blks,SimulinkModel::XSD::blocks_T &sub_blks,string target_blk,equation *state)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = sub_blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  cout << "subbeforeblock" << target_blk << endl;
  for( bi = blk_seq.begin(); bi != blk_seq.end(); bi++){
    /*SubSystem内の処理*/
    if(bi->name() == target_blk){
      if(bi->blocktype() == "UnitDelay"){
	cout << "UnitDelayにぶつかりました" << endl;
	break;
      }
      if(bi->blocktype() == "Integrator"){
	cout << "Integratorにぶつかりました" << endl;
	break;
      }
      SimulinkModel::XSD::block_T::input_sequence ip_seq = bi->input();
      SimulinkModel::XSD::block_T::input_iterator ii;
      if(ip_seq.begin() == ip_seq.end() && bi->blocktype() == "Inport"){
	/*SubSystem内のinportに達したら次にSubSystemのinportからまた探索開始*/
	std::string subsys = rtnSubSys(blks,bi->name(),bi->name());
	if(rtnNameToType(blks,subsys) == "SubSystem"){
	  SimulinkModel::XSD::blocks_T up = blks;
	  SimulinkModel::XSD::blocks_T up2 = blks;
	  rtnupSys(up,up2,subsys);
	  //sub_out_before_block(blks,up,subsys,state);
	  SimulinkModel::XSD::blocks_T::block_sequence up_seq = up.block();
	  SimulinkModel::XSD::blocks_T::block_iterator upi;
	  for(upi = up_seq.begin();upi != up_seq.end();upi++){
	    if(upi->name() == subsys){
	      SimulinkModel::XSD::block_T::input_sequence ip2_seq = upi->input();
	      SimulinkModel::XSD::block_T::input_iterator ii2;
	      for(ii2 = ip2_seq.begin();ii2 != ip2_seq.end();ii2++){
		if(bi->name() == ii2->port()){
		  SimulinkModel::XSD::ioport_T::connect_sequence con_seq = ii2->connect();
		  SimulinkModel::XSD::ioport_T::connect_iterator ci;
		  for(ci = con_seq.begin();ci != con_seq.end();ci++){
		    std::string con_name(ci->block());
		    if(rtnNameToType(blks,con_name) == "SubSystem"){
		      sub_out_before_block(blks,up,ci->port(),state);
		    }else{
		      sub_out_before_block(blks,up,subsys,state);
		    }
		  }
		}
	      }
	    }
	  }
	}
      }else{
	for(ii = ip_seq.begin();ii != ip_seq.end();ii++){
	  SimulinkModel::XSD::ioport_T::connect_sequence con_seq = ii->connect();
	  SimulinkModel::XSD::ioport_T::connect_iterator ci;
	  for(ci = con_seq.begin();ci != con_seq.end();ci++){
	    std::string tmp(ci->block());
	    if(rtnNameToType(blks,tmp) == "SubSystem"){
	      SimulinkModel::XSD::blocks_T sub = blks;
	      cout << "deteru" << endl;
	      rtnsubBlocks(sub,tmp);
	      std::string con_blk(ci->port());
	      state->add_blk(con_blk);
	      sub_out_before_block(blks,sub,con_blk,state);
	    }
	    else if(state->get_flagval() == 0){
	      state->add_blk(tmp);
	      state->set_flagval();
	      sub_out_before_block(blks,sub_blks,tmp,state);
	    }else{
	      if(state->find_l(tmp) == 0){
		state->add_blk(tmp);
		sub_out_before_block(blks,sub_blks,tmp,state);
	      }
	    }
	  }
	}
      }
      break;
    }
    else if(bi->blocktype() == "SubSystem"){
      SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
      SimulinkModel::XSD::block_T::blocks_iterator bsi;
      for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++)
	sub_out_before_block(blks,*bsi,target_blk,state);
    }
  }
} 

/*SubSystem名を受け取ってblocks_T型を返す関数*/
void rtnsubBlocks(SimulinkModel::XSD::blocks_T &blks,string name)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
    if(bi->blocktype() == "SubSystem"){
      if(bi->name() == name){
	SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
	SimulinkModel::XSD::block_T::blocks_iterator bsi;
	for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++){
	  blk_seq = bsi->block();
	  blks.block(blk_seq);
	}
	break;
      }else{
	SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
	SimulinkModel::XSD::block_T::blocks_iterator bsi;
	for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++){
	  rtnsubBlocks(*bsi,name);
	}
      }
    }
  }
}

/*ブロック名を受け取りそのブロックがいる階層を返す関数*/
void rtnupSys(SimulinkModel::XSD::blocks_T &blks,SimulinkModel::XSD::blocks_T &blks2,string name)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks2.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
    if(bi->blocktype() == "SubSystem"){
      if(bi->name() == name){
		blks.block(blk_seq);
      }else{
	SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
	SimulinkModel::XSD::block_T::blocks_iterator bsi;
	for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++){
	  rtnupSys(blks,*bsi,name);
	}
      }
    }
  }
}

/*ブロック名を引数にブロックタイプを返す関数*/
string rtnNameToType(SimulinkModel::XSD::blocks_T &blks,string name)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  std::string tmp2;
  for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
    if(bi->blocktype() == "SubSystem"){
      std::string subsys(bi->name());
      if(bi->name() == name){
	std::string sysType(bi->blocktype());
	cout << "yes!!" << endl;
	return sysType;
      }else{
	SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
	SimulinkModel::XSD::block_T::blocks_iterator bsi;
	for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++){
	  tmp2 = rtnNameToType(*bsi,name);
	  if(tmp2 != "0"){
	    return tmp2;
	  }
	}
      }
    }else{
      std::string tmp(bi->name());
      if(tmp == name){
	std::string rtnType(bi->blocktype());
	return rtnType;
      }
    }
  }
  return "0";
}

/*Inportブロック名を受け取りSubSystem名を返す*/
/*みつからなかったら０を返してくれる*/
string rtnSubSys(SimulinkModel::XSD::blocks_T &blks,string blockname,string sys)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
    std::string tmp(bi->name());
    if(bi->blocktype() == "SubSystem"){
      SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
      SimulinkModel::XSD::block_T::blocks_iterator bsi;
      for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++){
	std::string tmp2 = rtnSubSys(*bsi,blockname,tmp);
	if(tmp2 != "0"){
	  return tmp2;
	}
      }
    }else if(tmp == blockname){
      return sys;
    }
  }
  return "0";
}

/*指定したブロックが指定したシステム内にあるかどうかを確認*/
/*あったら1なかったら0*/
/*Inportが一番外枠のInportかどうかチェックするために使用*/
int rtnIn(SimulinkModel::XSD::blocks_T &blks,string name)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
    if(bi->name() == name){
      return 1;
    }else{
      return 0;
    }
  }
}

/*引数のXMLのpeinfoに色付け用の情報を付加する関数*/
void color_set(SimulinkModel::XSD::blocks_T &blks,equation *set)
{
  std::vector<std::string>::iterator blk_list_i;
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
    if(bi->blocktype() == "SubSystem"){
      SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
      SimulinkModel::XSD::block_T::blocks_iterator bsi;
      bi->peinfo(set->get_colorval());
      for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++){
	// このループは一度しか行われない<sm:blocks>
	color_set(*bsi,set);
      }
      bi->blocks(blks_seq);
    }else{
      std::string tmp(bi->name());
      if(set->find_l(tmp) == 1){
	bi->peinfo(set->get_colorval());
      }
    }
  }
  /*変更点更新のため*/
  blks.block(blk_seq);
}
