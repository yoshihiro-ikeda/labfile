#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include <xsd/cxx/xml/string.hxx>
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
  print_blocks(root_blks);
  fclose(fp_out);
}
void print_usage(char *progname)
{
  cerr << "Usage: " << progname << " <input-xml>" << endl;
}
void print_blocks(SimulinkModel::XSD::blocks_T &blks)
{
  SimulinkModel::XSD::blocks_T::block_sequence blk_seq = blks.block();
  SimulinkModel::XSD::blocks_T::block_iterator bi;
  for( bi = blk_seq.begin(); bi != blk_seq.end(); bi++){
    if( bi->blocktype() == "SubSystem" ){
      SimulinkModel::XSD::block_T::blocks_sequence blks_seq = bi->blocks();
      SimulinkModel::XSD::block_T::blocks_iterator bsi;
      for(bsi = blks_seq.begin(); bsi != blks_seq.end(); bsi++)
	print_blocks(*bsi);
    }
    else {
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
		              cout << bi->peinfo() << endl;
	             }
	           }
	         }
	       }
       }else if(bi->blocktype() == "Integrator"){
	         cout << bi->name() << endl;
        }
     }
  }
}