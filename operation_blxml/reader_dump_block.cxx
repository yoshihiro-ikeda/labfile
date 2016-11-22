#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include <xsd/cxx/xml/string.hxx>
#include "SimulinkModel.hxx"
#include "SimulinkModel_ns.h"
#include "SimulinkXML.h"
using namespace std;
void print_usage(char*);
void print_blocks(SimulinkModel::XSD::blocks_T &blks);
int main(int argc, char *argv[])
{
  Simulink::XML::Reader xrd;
  if(argc < 2){
    print_usage(argv[0]);
    return 0;
  }
  xrd.load_xml(argv[1]);
  if (!xrd){
    cerr << "Failed to load XML" << endl;
    print_usage(argv[0]);
    return 1;
  }
  SimulinkModel::XSD::blocks_T root_blks = xrd.xml_blocks();
  print_blocks(root_blks);
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
      cout << bi->name() << ",,0"<< endl;
    }
  }
}
