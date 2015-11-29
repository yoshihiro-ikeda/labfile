#include "SimulinkModel.hxx"
#include "SimulinkModel_ns.h"
#include "SimulinkXML.h"
using namespace std;
void print_usage(char*);
void search_blocks(SimulinkModel::XSD::blocks_T &blks);
void before_block(SimulinkModel::XSD::blocks_T &blks,string target_blks);
