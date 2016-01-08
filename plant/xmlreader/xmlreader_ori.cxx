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

  /* t@CÉoÍp */
  FILE* fp_out = freopen("linelist.dat", "w", stdout);
  
  xrd.load_xml(argv[1]);
  if (!xrd){
    cerr << "Failed to load XML" << endl;
    print_usage(argv[0]);
    return 1;
  }
  
  SimulinkModel::XSD::blocks_T root_blks = xrd.xml_blocks();
  
  /* NXè`
   * state:óÔûö®
   * out  :oÍûö®
  */
  equation state(0,"green");
  equation out(0,"red"); 
  
  /*»ê¼êÌcsvoÍp*/
  SimulinkModel::XSD::blocks_T state_blks = xrd.xml_blocks();
  SimulinkModel::XSD::blocks_T out_blks = xrd.xml_blocks();
  
  /*óÔûö®EoÍûö®ÌTõ*/
  search_blocks(root_blks,&state,&out);
  search_output(root_blks,"UnitDelay",&out);
  
  /*blk_listÌgð\¦*/
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
  

  /*IÎê½ubNÌpeinfoFîñðtÁ*/
  //color_set(state_blks,&state);
  //color_set(out_blks,&out);
  fclose(fp_out);
  /*xmlðoÍ*/
  //print_xml(state_blks);
  
  /*Ft¯c[pÉcsvt@CðoÍ*/
  print_csv(state_blks,"result_state.csv");
  print_csv(out_blks,"result_out.csv");
}

void print_usage(char *progname)
{
  cerr << "Usage: " << progname << " <input-xml>" << endl;
}

/*xmlt@CÉoÍ·épÌÖ*/
void print_xml(SimulinkModel::XSD::blocks_T &blks)
{
  xml_schema::namespace_infomap map;
  map["SM"].name = "http://example.com/SimulinkModel"; // namespace is "SM"
  map["SM"].schema = "SimulinkModel.xsd"; // SimulinkModel XML Schema
  ::std::ofstream os ("result.xml");
  blocks (os,blks,map);
}
/*csv`®ÉµÄKvîñðoÍ*/
void print_csv(SimulinkModel::XSD::blocks_T &blks,const char *filename)
{
	ofstream ofs(filename,ios::app);
	SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
	SimulinkModel::XSD::blocks_T::block_iterator bi;
	for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
		if(bi->blocktype() == "SubSystem"){
			SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
			SimulinkModel::XSD::block_T::blocks_iterator bsi;
			for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++){
				ofs.close();
				print_csv(*bsi,filename);
			}
		}else{
			ofs << bi->name() << "," << "," << bi->peinfo() << endl;
		}
	}
}
/*sumÆunitdelayÌgÝí¹ðõµÄ»±©çóÔÍoÍûö®ðT·ÖðÄÑo·*/
void search_blocks(SimulinkModel::XSD::blocks_T &blks,equation *state,equation *out)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  for( bi = blk_seq.begin(); bi != blk_seq.end(); bi++){
    if( bi->blocktype() == "SubSystem" ){
	  cout << "ok" << endl;
      SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
      SimulinkModel::XSD::block_T::blocks_iterator bsi;
      for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++)
		search_blocks(*bsi,state,out);
    }
    else {		/*ÏªubNÌTõ*/
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
					/*óÔûö®Íunitdelay©çTõ*/
					before_block(blks,bi->name(),state);
					/*oÍûö®ÍsumÜÅTõ*/
					//after_block(blks,bi2->name(),out);
	             }
	           }
	         }
	       }
       }else if(bi->blocktype() == "Integrator"){
	         cout << bi->name() << endl;
        }
     /*ÏªubNÌTõ±±ÜÅ*/
     }
  }
}

/*ubNkèÖ*/
/*óÔûö®ðõ·é½ßÉgp*/
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
				/*SubsystemàÌInportubNÉBµ½êÌ*/
				if(con_seq.empty()){
					
				}
				/*±±ÜÅ*/
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

/*ubNHèÖ*/
/*»Ýgp³êÄ¢È¢*/
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
/*oÍûö®ðõ·é½ßÉgp*/
/*outputðõµÄfollow_block_from_lastðÄÑo·*/
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
						cout << "okokokokokokokok" << endl;
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

/*fÌÅã©çwè³ê½ubNÜÅßéÖ*/
void follow_block_from_last(SimulinkModel::XSD::blocks_T &blks,equation *out,string target_blk,string exblk)
{
	SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
	SimulinkModel::XSD::blocks_T::block_iterator bi;
	for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
		if( bi->blocktype() == "SubSystem" ){
			cout << "ok" << endl;
			SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
			SimulinkModel::XSD::block_T::blocks_iterator bsi;
			for(bsi = blks_seq.begin();bsi != blks_seq.end();bsi++){
				search_output(*bsi,"UnitDelay",out);
			}
		}
		else if(bi->name() == target_blk){
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

/*ubN¼©çubN^CvðÔ·Ö*/

string rtnNameToType(SimulinkModel::XSD::blocks_T &blks,string name)
{
	SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
	SimulinkModel::XSD::blocks_T::block_iterator bi;
	for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
		if(bi->blocktype() == "SubSystem"){
			SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
			SimulinkModel::XSD::block_T::blocks_iterator bsi;
			for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++){
				std::string tmp2 = rtnNameToType(*bsi,name);
				if(tmp2 != "0")
					return tmp2;
			} 
		}else{
			std::string tmp(bi->name());
			if(tmp == name){
				std::string rtnType(bi->blocktype());
				return rtnType;
			}
		}
		if(bi == blk_seq.end()){
			return "0";
		}
	}
}
/*øÌXMLÌpeinfoÉFt¯pÌîñðtÁ·éÖ*/
/*SubSystemàÌpeinfoîñð«·¦çêÈ¢½ßêUÛ¯*/
void color_set(SimulinkModel::XSD::blocks_T &blks,equation *set)
{
	std::vector<std::string>::iterator blk_list_i;
	SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
	SimulinkModel::XSD::blocks_T::block_iterator bi;
	for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
		cout << bi->name() << endl;
		if(bi->blocktype() == "SubSystem"){
			SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
			SimulinkModel::XSD::block_T::blocks_iterator bsi;
			for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++){
				// ±Ì[vÍêxµ©síêÈ¢<sm:blocks>
				color_set(*bsi,set);
			}
		}else{
			std::string tmp(bi->name());
			if(set->find_l(tmp) == 1){
				cout << "peinfo " << bi->peinfo() << set->get_colorval() << endl;
				bi->peinfo(set->get_colorval());
				//bi->peinfo() = set->get_colorval();
			}else{
				cout << "false" << tmp <<  endl;
			}
		}
	}
	/*ÏX_XVÌ½ß*/
	blks.block(blk_seq);

}
