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
	ifstream myfile("dirty_deputies_v2.csv");
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
	struct media_refund {string refund; double value; int total;} mr[30];
	unsigned int mrcount = 0, flag = 0, k = 7;
	double media, pc;
	
	/*Limpando vetor que armazenara os ressarcimentos*/
	for (i = 0; i < 30; i++){
		mr[i].refund = "NONE";
		mr[i].value = 0;
		mr[i].total = 0;
	}
	
	/* Separa e conta quantas requisicoes e valor total acumulado*/
	for(i = 0; i < deputados.size(); i ++){
		for (j = 0; j < mrcount; j++){ /*Procura se o motivo ja exite*/
			if (deputados[i].refund_description == mr[j].refund){
				flag = j;
			}
		}
		if (flag != 0){ /*Caso motivo exista, adiciona nova requisicao e acrescenta o valor*/
			mr[flag].value = mr[flag].value + atof(deputados[i].refund_value.c_str());
			mr[flag].total = mr[flag].total + 1;
			flag = 0;
		}
		else{ /*Caso nao exista, cria o campo no vetor e se adiciona*/
			mr[mrcount].refund = deputados[i].refund_description;
			mr[mrcount].value = atof(deputados[i].refund_value.c_str());
			mr[mrcount].total = mr[j].total + 1;
			mrcount++;
		}
	}	
	
	/*Printa quantidade total de requisicoes*/
	cout << "\t ## REQUISICOES DE RESSARCIMENTO ##" << endl;
	for (j = 1; j < mrcount; j++){
		cout << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "                                                  |";
		cout << "\r| Id: " << j << " Motivo: " << mr[j].refund << endl;
		cout << "                                                  |";
		cout << "\r| Valor total: R$ " << mr[j].value << endl;
		cout << "                                                  |";
		cout << "\r| Quantidade requisitada: " << mr[j].total << endl;
		cout << "---------------------------------------------------" << endl;
	}
	
	cout << "<Pressione enter para continuar>" << endl;
	getchar();
	cout << endl;
	/*Permite ao usuario escolher qual motivo de ressarcimento ele deseja observar*/
	cout << "\t ## PESQUISANDO POR ANOMALIAS ##" << endl;
	cout << "Digite um id de um motivo: ";
	cin >> k;
	cout << "Motivo escolhido: " << mr[k].refund << endl;
	cout << "Valor total gasto: " << mr[k].value << endl;
	cout << "Quantidade requisitada: " << mr[k].total << endl;
	
	/*Permite ao usuario escolher quantos porcento ele considera anomalia para o algoritmo fazer a busca*/
	media = (mr[k].value / mr[k].total);
	cout << "Gastos em media por requisicao: " << media << endl;
	cout << "Digite o numero (em porcento) para parametro de verificacao de anomalia: ";
	cin >> pc;
	media = (mr[k].value / mr[k].total) * (pc/100);
	
	getchar();
	cout << endl;
	cout << "\t ## REQUISICOES COM VALOR DE " << pc << "% ACIMA DA MEDIA ###" << endl;
	cout << "<Pressione enter para continuar>" << endl;
	for(i = 0; i < deputados.size(); i ++){
		if (deputados[i].refund_description == mr[k].refund){
			if (atof(deputados[i].refund_value.c_str()) > media){
				cout << "-------------------------------------------------------------------------------" << endl;
				cout << "                                                                              |";
				cout << "\r Name: "               << deputados[i].name               << endl;
				cout << "                                                                              |";
				cout << "\r State: "              << deputados[i].state              << endl;
				cout << "                                                                              |";
				cout << "\r Party: "              << deputados[i].party              << endl;
				cout << "                                                                              |";
				cout << "\r company_name: "       << deputados[i].company_name       << endl;
				cout << "                                                                              |";
				cout << "\r refund_date: "        << deputados[i].refund_date        << endl;
				cout << "                                                                              |";
				cout << "\r refund_value: "       << deputados[i].refund_value       << endl;
				cout << "-------------------------------------------------------------------------------" << endl;

				
			}
		}

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