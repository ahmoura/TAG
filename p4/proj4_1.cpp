#include <cstdlib>
#include <bits/stdc++.h>
#include <string.h>
#include <sstream>

using namespace std;

using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;

typedef struct Deputado{
	string name;
	string state;
	string party;
	string refund_description;
	string company_name;
	string company_id;
	string refund_date;
	string refund_value;
}Deputado;

vector<Deputado> loadFile(){
	int i, j = 0;
	string delimiter = ",";
	ifstream myfile("dirty_deputies_v3.csv");
  	string line;
  	vector<string> campos;
  	string token;
  	size_t pos = 0;
  	vector<Deputado> deputados;
  	Deputado deputado;

  	if(myfile.is_open()){
  		getline(myfile,line);
  		while(myfile.eof() == false){
  			getline(myfile,line);
  			i = 0;
  			while ((pos = line.find(delimiter)) != std::string::npos) {
    			token = line.substr(0, pos);
    			line.erase(0, pos + delimiter.length());
    			switch(i){
    				case 0:
    					deputado.name = token;
						i++;
    				break;
    				case 1:
    					deputado.state = token;
						i++;
    				break;
    				case 2:
    					deputado.party = token;
						i++;
    				break;
    				case 3:
    					deputado.refund_description = token;
						i++;
    				break;
    				case 4:
    					deputado.company_name = token;
						i++;
    				break;
    				case 5:
    					deputado.company_id = token;
						i++;
    				break;
    				case 6:
    					deputado.refund_date = token;
						i++;
    				break;
    				case 7:
    					deputado.refund_value = token;
						i++;
						deputados.push_back(deputado);
						j++;
    				break;
    			}
			}
			if(i == 8){
				i = 0;
			}

			
  		}
  	}
  	return deputados;
}

void itree(vector<Deputado> deputados){
	
	unsigned int i, j;
	struct media_refund {string refund; double value; int total;} mr[100];
	unsigned int mrcount = 0, flag = 0;
	stringstream ss;
	double fl;
	
	for (i = 0; i < 100; i++){
		mr[i].refund = "NONE";
		mr[i].value = 0;
		mr[i].total = 0;
	}

	for(i = 0; i < deputados.size(); i ++){
		for (j = 0; j < mrcount; j++){
			if (deputados[i].refund_description == mr[j].refund){
			flag = j;
			}
		}
		if (flag != 0){
			ss << deputados[i].refund_value;
			fl = 0;
			ss >> fl;
			ss.clear();
			mr[flag].value = mr[flag].value + fl;
			mr[flag].total = mr[flag].total + 1;
			flag = 0;
		}
		else{
			mr[mrcount].refund = deputados[i].refund_description;
			ss << deputados[i].refund_value;
			fl = 0;
			ss >> fl;
			ss.clear();
			mr[mrcount].value = fl;
			mr[mrcount].total = mr[mrcount].total + 1;
			mrcount++;
		}
	}
	for (j = 0; j < mrcount; j++){
		cout << "REFUND: " << mr[j].refund << "   ";
		cout << "VALUE: " << mr[j].value << "   ";
		cout << "TOTAL: " << mr[j].total << endl;
	}
}

void printFile(vector<Deputado> deputados){
	unsigned int i;

	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	for(i = 0; i < deputados.size(); i ++){
		cout << "ID: "               << i              << endl;
		cout << "Name: "               << deputados[i].name               << endl;
		cout << "State: "              << deputados[i].state              << endl;
		cout << "Party: "              << deputados[i].party              << endl;
		cout << "refund_description: " << deputados[i].refund_description << endl;
		cout << "company_name: "       << deputados[i].company_name       << endl;
		cout << "company_id: "         << deputados[i].company_id         << endl;
		cout << "refund_date: "        << deputados[i].refund_date        << endl;
		cout << "refund_value: "       << deputados[i].refund_value       << endl;
		cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;	
	}
}

int main (){
	vector<Deputado> all_deputados;
	all_deputados = loadFile();
	itree(all_deputados);
	//printFile(all_deputados);
	return 0;
}