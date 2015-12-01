#include "SimulinkModel.hxx"
#include "SimulinkModel_ns.h"
#include "SimulinkXML.h"
using namespace std;
void print_usage(char*);
void print_xml(SimulinkModel::XSD::blocks_T &blks);
void print_csv(SimulinkModel::XSD::blocks_T &blks);
void search_blocks(SimulinkModel::XSD::blocks_T &blks);
void before_block(SimulinkModel::XSD::blocks_T &blks,string target_blks);
void color_set(SimulinkModel::XSD::blocks_T &blks);
