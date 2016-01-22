#include "SimulinkModel.hxx"
#include "SimulinkModel_ns.h"
#include "SimulinkXML.h"
using namespace std;
class equation {
	public:
		equation (int num,std::string color_name)
		{
			first_flag = num;
			color = color_name;
		}
		int get_flagval(){return first_flag;}
		void set_flagval(){first_flag = 1;}
		std::string get_colorval(){return color;}
		//std::vector<std::string>::iterator blk_list_i;
		void add_blk(string name){blk_list.push_back(name);}
		typedef std::vector<std::string>::iterator iterator;
		iterator vec_begin(){return blk_list.begin();}
		iterator vec_end(){return blk_list.end();}
		int find_l(std::string name) //あったら1なかったら0
		{
			iterator blk_list_i;
			blk_list_i = find(blk_list.begin(),blk_list.end(),name);
			if(blk_list_i == blk_list.end()){
				return 0;
			}else{
				return 1;
			}
		}

	private:
		std::vector <std::string> blk_list;
		int first_flag;
		std::string color;
};

void print_usage(char*);
void print_xml(SimulinkModel::XSD::blocks_T &blks);
void print_csv(SimulinkModel::XSD::blocks_T &blks,const char *filename);
void print_each_csv(SimulinkModel::XSD::blocks_T &blks);
void search_blocks(SimulinkModel::XSD::blocks_T &blks);
void sub_search_blocks(SimulinkModel::XSD::blocks_T &blks,SimulinkModel::XSD::blocks_T &sub_blks);
void before_block(SimulinkModel::XSD::blocks_T &blks,string target_blks,equation *state,int flag);
void sub_before_block(SimulinkModel::XSD::blocks_T &blks,SimulinkModel::XSD::blocks_T &sub_blks,string target_blk,equation *state,int flag);
void select_port_before(SimulinkModel::XSD::blocks_T &blks, SimulinkModel::XSD::blocks_T &sub_blks, string sys, string port, equation *state);
void search_output(SimulinkModel::XSD::blocks_T &blks,std::string target_blk,equation *out);
void sub_out_before_block(SimulinkModel::XSD::blocks_T &blks,SimulinkModel::XSD::blocks_T &sub_blks,string target_blk,equation *state);
void follow_block_from_last(SimulinkModel::XSD::blocks_T &blks,equation *out,string target_blk,string exblk);
void rtnsubBlocks(SimulinkModel::XSD::blocks_T &blks,string name);
void rtnupSys(SimulinkModel::XSD::blocks_T &blks,SimulinkModel::XSD::blocks_T &blks2,string name);
string rtnNameToType(SimulinkModel::XSD::blocks_T &blks,string name);
string rtnSubSys(SimulinkModel::XSD::blocks_T &blks,string blockname,string sys);
int rtnIn(SimulinkModel::XSD::blocks_T &blks,string name);
void color_set(SimulinkModel::XSD::blocks_T &blks,equation *set);
