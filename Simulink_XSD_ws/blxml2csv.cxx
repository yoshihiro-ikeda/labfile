#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <string.h>

using namespace std;

int main(){
    ifstream file("paths.csv");
    vector< vector<string> > values;
    string str;
    int p;

    if(file.fail()){
        cerr << "failed." << endl;
        exit(0);
    }

    while(getline(file, str)){
        //コメント行は排除
        if( (p = str.find("//")) != str.npos ) continue;
        vector<string> inner;

        //コンマがあるか探し、valuesに格納
        while( (p = str.find(",")) != str.npos ){
            inner.push_back(str.substr(0, p));

            //strの中身は""のに文字を飛ばす
            str = str.substr(p+1);
        }
        inner.push_back(str);
        values.push_back(inner);
    }

    //paths.csvの中身参照完了
    
    vector<string> paths;
    
    ifstream pathfile("c_path.csv");
    while(getline(pathfile, str)){
		cout << str << endl;
		string tmp(str);
		for(int i = 0; i < values.size();i++){
			if(tmp == values[i][2]){
				paths.push_back(values[i][0]);
				cout << endl;
			}
		}
    }
    
    for(int j = 0;j < paths.size();j++){
		cout << paths[j] << endl;
	}
	
	return 0;
}
