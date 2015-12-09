#include <iostream>
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
  FILE* fp_out = freopen("linelist.dat", "w", stdout);
  
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
  equation state(0,"green");
  equation out(0,"red"); 
  
  /*それぞれのcsv出力用*/
  SimulinkModel::XSD::blocks_T state_blks = xrd.xml_blocks();
  SimulinkModel::XSD::blocks_T out_blks = xrd.xml_blocks();
  
  /*状態方程式・出力方程式の探索*/
  search_blocks(root_blks,&state,&out);
  search_output(root_blks,"UnitDelay",&out);
  
  /*blk_listの中身を表示*/
  std::vector<std::string>::iterator blk_list_si;
  cout << "state" << endl;
  for(blk_list_si = state.vec_begin();blk_list_si != state.vec_end();blk_list_si++){
	  cout << *blk_list_si << endl;
  }
  std::vector<std::string>::iterator blk_list_oi;
  cout << "out" << endl;
  for(blk_list_oi = out.vec_begin();blk_list_oi != out.vec_end();blk_list_oi++){
	  cout << *blk_list_oi << endl;
  }
  
  fclose(fp_out);
  /*選ばれたブロックのpeinfo色情報を付加*/
  color_set(state_blks,&state);
  color_set(out_blks,&out);
  
  /*xmlを出力*/
  //print_xml(root_blks);
  
  /*色付けツール用にcsvファイルを出力*/
  print_csv(state_blks,"result_state.csv");
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
void print_csv(SimulinkModel::XSD::blocks_T &blks,const char *filename)
{
	ofstream ofs(filename);
	SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
	SimulinkModel::XSD::blocks_T::block_iterator bi;
	for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
		ofs << bi->name() << "," << "," << bi->peinfo() << endl;
	}
}
/*sumとunitdelayの組み合わせを検索してそこから状態又は出力方程式を探す関数を呼び出す*/
void search_blocks(SimulinkModel::XSD::blocks_T &blks,equation *state,equation *out)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  for( bi = blk_seq.begin(); bi != blk_seq.end(); bi++){
    if( bi->blocktype() == "SubSystem" ){
      SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
      SimulinkModel::XSD::block_T::blocks_iterator bsi;
      for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++)
	search_blocks(*bsi,state,out);
    }
    else {		/*積分ブロックの探索*/
      if(bi->blocktype() == "UnitDelay"){
	       SimulinkModel::XSD::block_T::input_sequence ip_seq = bi->input();
	       SimulinkModel::XSD::block_T::input_iterator ii;
	       for(ii = ip_seq.begin();ii != ip_seq.end();ii++){
	         SimulinkModel::XSD::ioport_T::connect_sequence con_seq = ii->connect();
	         SimulinkModel::XSD::ioport_T::connect_iterator ci;
	         for(ci = con_seq.begin();ci != con_seq.end();ci++){
	           SimulinkModel::XSD::blocks_T::block_sequence blk2_seq = blks.block();
	           SimulinkModel::XSD::blocks_T::block_iterator bi2;
	           for(bi2 = blk2_seq.begin();bi2 != blk2_seq.end();bi2++){
	             if(bi2->name() == ci->block() && bi2->blocktype() == "Sum"){
					cout << bi->name() << endl;
					/*状態方程式はunitdelayから探索*/
					before_block(blks,bi->name(),state);
					/*出力方程式はsumまで探索*/
					//after_block(blks,bi2->name(),out);
	             }
	           }
	         }
	       }
       }else if(bi->blocktype() == "Integrator"){
	         cout << bi->name() << endl;
        }
     /*積分ブロックの探索ここまで*/
     }
  }
}

/*ブロック遡り関数*/
/*状態方程式を検索するために使用*/
void before_block(SimulinkModel::XSD::blocks_T &blks,string target_blk,equation *state)
{
	SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
	SimulinkModel::XSD::blocks_T::block_iterator bi;
	for( bi = blk_seq.begin(); bi != blk_seq.end(); bi++){
		if(bi->name() == target_blk){	
			SimulinkModel::XSD::block_T::input_sequence ip_seq = bi->input();
			SimulinkModel::XSD::block_T::input_iterator ii;
			for(ii = ip_seq.begin();ii != ip_seq.end();ii++){
				SimulinkModel::XSD::ioport_T::connect_sequence con_seq = ii->connect();
				SimulinkModel::XSD::ioport_T::connect_iterator ci;
				for(ci = con_seq.begin();ci != con_seq.end();ci++){
					std::string tmp(ci->block());
					if(state->get_flagval() == 0){
						state->add_blk(tmp);
						before_block(blks,tmp,state);
						state->set_flagval();
					}else{
						if(state->find_l(tmp) == 0){
							state->add_blk(tmp);
							before_block(blks,tmp,state);
						}
					}
				}
			}
			break;
		}
	} 
}

/*ブロック辿り関数*/
/*現在使用されていない*/
void after_block(SimulinkModel::XSD::blocks_T &blks,string target_blk,equation *out)
{
	SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
	SimulinkModel::XSD::blocks_T::block_iterator bi;
	for( bi = blk_seq.begin(); bi != blk_seq.end(); bi++){
		std::string cmpname(bi->name());
		if(bi->name() == target_blk && rtnNameToType(blks,target_blk) != "Outport"){	
			cout << "test  " << rtnNameToType(blks,cmpname) << endl;
			SimulinkModel::XSD::block_T::output_sequence op_seq = bi->output();
			SimulinkModel::XSD::block_T::output_iterator oi;
			for(oi = op_seq.begin();oi != op_seq.end();oi++){
				SimulinkModel::XSD::ioport_T::connect_sequence con_seq = oi->connect();
				SimulinkModel::XSD::ioport_T::connect_iterator ci;
				for(ci = con_seq.begin();ci != con_seq.end();ci++){
					std::string tmp(ci->block());
					if(out->get_flagval() == 0){
						if(rtnNameToType(blks,cmpname) != "UnitDelay"){
							out->add_blk(tmp);
							after_block(blks,tmp,out);
							out->set_flagval();
						}
					}else{
						SimulinkModel::XSD::block_T::input_sequence ip_seq = bi->input();
						SimulinkModel::XSD::block_T::input_iterator ii;
						int sum_flag = 0;
						if(rtnNameToType(blks,cmpname) == "UnitDelay"){
							for(ii = ip_seq.begin();ii != ip_seq.end();ii++){
								SimulinkModel::XSD::ioport_T::connect_sequence con_seq = ii->connect();
								SimulinkModel::XSD::ioport_T::connect_iterator ci;
								for(ci = con_seq.begin();ci != con_seq.end();ci++){
									std::string search_sum(ci->block());
									if(rtnNameToType(blks,search_sum) == "Sum"){
										sum_flag = 1;
										goto SOTO;
									}
								}
							}
						}
						SOTO:
						if(out->find_l(tmp) == 0 && ii == ip_seq.end() && sum_flag == 0){
							cout << "ok" << endl;
							out->add_blk(tmp);
							after_block(blks,tmp,out);
						}
					}
				}
			}
			break;
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
					}else if(out->get_flagval() == 0){
						out->add_blk(tmp);
						follow_block_from_last(blks,out,tmp,target_blk);
						out->set_flagval();
					}else{
						if(out->find_l(tmp) == 0){
							out->add_blk(tmp);
							follow_block_from_last(blks,out,tmp,target_blk);
						}
					}
				}
			}
		}NEXT: ;
	}
}

/*モデルの最後から指定されたブロックまで戻る関数*/
void follow_block_from_last(SimulinkModel::XSD::blocks_T &blks,equation *out,string target_blk,string exblk)
{
	SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
	SimulinkModel::XSD::blocks_T::block_iterator bi;
	for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
		if(bi->name() == target_blk){
			SimulinkModel::XSD::block_T::input_sequence ip_seq = bi->input();
			SimulinkModel::XSD::block_T::input_iterator ii;
			for(ii = ip_seq.begin();ii != ip_seq.end();ii++){
				SimulinkModel::XSD::ioport_T::connect_sequence con_seq = ii->connect();
				SimulinkModel::XSD::ioport_T::connect_iterator ci;
				for(ci = con_seq.begin();ci != con_seq.end();ci++){
					std::string tmp(ci->block());
					if(rtnNameToType(blks,tmp) == exblk){
						goto END;
					}else if(out->get_flagval() == 0){
						out->add_blk(tmp);
						follow_block_from_last(blks,out,tmp,exblk);
						out->set_flagval();
					}else{
						if(out->find_l(tmp) == 0){
							out->add_blk(tmp);
							follow_block_from_last(blks,out,tmp,exblk);
						}
					}
				}END: ;
			}
		}
	}
}

/*ブロック名からブロックタイプを返す関数*/
string rtnNameToType(SimulinkModel::XSD::blocks_T &blks,string name)
{
	SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
	SimulinkModel::XSD::blocks_T::block_iterator bi;
	for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
		std::string tmp(bi->name());
		if(tmp == name){
			std::string rtnType(bi->blocktype());
			return rtnType;
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
		std::string tmp(bi->name());
		if(set->find_l(tmp) == 1){
			bi->peinfo() = set->get_colorval();
		}
	}
	/*変更点更新のため*/
	blks.block(blk_seq);
}
