#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include <xsd/cxx/xml/string.hxx>
#include <vector>
#include <algorithm>
#include "xmlreader.hxx"

std::vector <std::string> blk_list;
int first_flag = 0;

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
  search_blocks(root_blks);
  std::vector<std::string>::iterator blk_list_ii;
  for(blk_list_ii = blk_list.begin();blk_list_ii != blk_list.end();blk_list_ii++){
	  cout << *blk_list_ii << endl;
  }
  fclose(fp_out);
  
  /*選ばれたブロックのpeinfo色情報を付加*/
  color_set(root_blks);
  /*xmlを出力*/
  print_xml(root_blks);
  /*色付けツール用にcsvファイルを出力*/
  print_csv(root_blks);
}
void print_usage(char *progname)
{
  cerr << "Usage: " << progname << " <input-xml>" << endl;
}

void print_xml(SimulinkModel::XSD::blocks_T &blks)
{
  xml_schema::namespace_infomap map;
  map["SM"].name = "http://example.com/SimulinkModel"; // namespace is "SM"
  map["SM"].schema = "SimulinkModel.xsd"; // SimulinkModel XML Schema
  ::std::ofstream os ("result.xml");
  blocks (os,blks,map);
}

void print_csv(SimulinkModel::XSD::blocks_T &blks)
{
	ofstream ofs("result.csv");
	std::vector<std::string>::iterator blk_list_i;
	SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
	SimulinkModel::XSD::blocks_T::block_iterator bi;
	for(blk_list_i = blk_list.begin();blk_list_i != blk_list.end();blk_list_i++){
		for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
			std::string tmp(bi->name());
			if(tmp == *blk_list_i){
				ofs << bi->name() << "," << "," << bi->peinfo() << endl;
				break;
			}
		}
	}
}

void search_blocks(SimulinkModel::XSD::blocks_T &blks)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  for( bi = blk_seq.begin(); bi != blk_seq.end(); bi++){
    if( bi->blocktype() == "SubSystem" ){
      SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
      SimulinkModel::XSD::block_T::blocks_iterator bsi;
      for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++)
	search_blocks(*bsi);
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
		            //cout << (bool)bi->peinfo() << endl;
					before_block(blks,bi->name());
		            if(!(bool)bi->peinfo()){
						bi->peinfo() = "green";
					}
						//cout << bi->peinfo() << endl;
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
void before_block(SimulinkModel::XSD::blocks_T &blks,string target_blk)
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
					if(first_flag == 0){
						blk_list.push_back(tmp);
						before_block(blks,tmp);
						first_flag = 1;
					}else{
						std::vector<std::string>::iterator blk_list_i = find(blk_list.begin(),blk_list.end(),tmp);
						if(blk_list_i == blk_list.end()){
							blk_list.push_back(tmp);
							before_block(blks,tmp);
						}
					}
				}
			}
			break;
		}
	} 
}

void color_set(SimulinkModel::XSD::blocks_T &blks)
{
	std::vector<std::string>::iterator blk_list_i;
	SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
	SimulinkModel::XSD::blocks_T::block_iterator bi;
	for(blk_list_i = blk_list.begin();blk_list_i != blk_list.end();blk_list_i++){
		for(bi = blk_seq.begin();bi != blk_seq.end();bi++){
			std::string tmp(bi->name());
			if(tmp == *blk_list_i){
				if(!(bool)bi->peinfo()){
					bi->peinfo() = "red";
				}else{
					bi->peinfo() = "red";
				}
				break;
			}
		}
	}
	/*変更点更新のため*/
	blks.block(blk_seq);
}
