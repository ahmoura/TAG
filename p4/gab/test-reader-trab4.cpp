#include <bits/stdc++.h>

using namespace std;

int main(){

  string line;
  string deputy_id, deputy_name,deputy_state,political_party,refund_description,company_name,company_id,refund_date,refund_value;
  int i=1;
  ifstream txtFile;
  txtFile.open("dirty_deputies_v2-withoutAnyCols");

  // Passa pelas linhas que tem informacoes acerca dos professores
  while(!txtFile.eof() && (i-1) <= 100000){

    getline(txtFile, line);// Pega a linha do loop.

    if (i == 1){ // teste para ele pular a primeira linha
      cout << "1st line ==> "+line << endl;
    } else {
      
      istringstream iss(line); // variavel para poder salvar os elementos.

      //iss >> cod >> hab >> tmp[0] >> tmp[1] >> tmp[2] >> tmp[3] >> tmp[4]; // pegando da variavel iss e salvando nas variaveis correspondete
      /*iss >> deputy_id
          >> deputy_name 
          >> deputy_state 
          >> political_party 
          >> refund_description 
          >> company_name 
          >> company_id 
          >> refund_date
          >> refund_value;*/

      getline(getline(getline(getline(getline(getline(getline(getline(getline(iss, deputy_id, ','), deputy_name, ','), deputy_state, ','), political_party, ','), refund_description,','), company_name, ','), company_id, ','), refund_date, ','), refund_value, ',');
      
      // TESTE DEBUGGER
      cout << "| deputy_id: "           << deputy_id
           << "| deputy_name: "         << deputy_name
           << "| deputy_state: "        << deputy_state
           << "| political_party: "     << political_party
           << "| refund_description: "  << refund_description
           << "| company_name: "        << company_name
           << "| company_id: "          << company_id
           << "| refund_date: "         << refund_date
           << "| refund_value: "        << refund_value << "\n\n ### ANOTHER REGISTER: #" <<endl;
    }    

    i++;    
  }
  return 0;
}