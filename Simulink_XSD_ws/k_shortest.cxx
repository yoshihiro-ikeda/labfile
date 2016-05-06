//K longest path routing Algorithm

#include "BLGraph.hxx"
#include <iostream>
#include <fstream>
#include <memory>

#include <algorithm>

#include <xercesc/dom/DOM.hpp>

int main(int argc, char *argv[])
{
	char filename[64];
	int cnt = 0;
	int cost = 0;//pathのコスト計算用
	
	block_T::performance_sequence ps;
	block_T::performance_iterator pi;
	  
	cout << "start reading." << endl;
	cout << "filename is " << argv[1] << endl;
	strcpy(filename,argv[1]);
	Reader xrd(filename); //XMLファイルを読み込み
	cout << "finish reading XML." << endl;
	
	BLGraph graph(xrd); //BLGragh作成完了
	cout << "finish creating graph." << endl;
	
	vector<string> path;
	count_u = 0;
	
