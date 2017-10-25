/*
UnB - Universidade de Brasilia

Projeto 3
TAG - Teoria e Aplicacao de Grafos
Professor: Dibio

Aluno: Antonio Henrique de Moura Rodrigues
Matricula: 15 / 0118236

Aluno: Matheus Nera Gay?
Matricula: 15 / 0124242
*/

#include <iostream>   // funcoes de entrada e saida de dados
#include <fstream>    // funcoes de manipulacao de arquivos
#include <string>     // funcoes de manipulacao de cadeia de caracteres
#include <vector>     // funcoes de vetor dinamico
#include <algorithm>  // funcoes de sort
#include <cstdlib>    // funcoes de conversao de tipos de arquivo

using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;
using namespace std;

typedef struct svertex{
  int preferences;
  string code;
} svertex;

typedef struct tvertex{
  int license;
  string code;
  vector<string> preferences;
} tvertex;

typedef struct graph{
  vector<tvertex> teacher;
  vector<svertex> school;
} graph;

int loadfile (graph &g){

  unsigned int i, j, k;
  ifstream myfile("entradaProj3TAG.txt");
  string line;
  string aux;
  tvertex aux_tvertex;
  svertex aux_svertex;


  if(myfile.is_open()){ // Se abrir o arquivo, exercuta

		//------------------------- LEITURA DOS PROFESSORES
		for (j = 0; j < 100; j++){

		getline(myfile, line);
		i = 0;

		//------------------------- LEITURA DO CODIGO
		while (line[i] != '|') { // Le valores do line ate o pipe
			aux.push_back(line[i]); // Adiciona no auxiliar para futura conversao
			i++;
		}
		aux_tvertex.code = aux;
		aux.clear();
		//------------------------- LEITURA DA LICENCA
		i += 1; // Pula o pipe
		while (line[i] != '|') { // Le valores do line ate o pipe
			aux.push_back(line[i]); // Adiciona no auxiliar para futura conversao
			i++;
		}
		aux_tvertex.license = atoi(aux.c_str()); // Joga dentro da struct o valor convertido

		//------------------------- LEITURA DAS PREFERENCIAS
		i += 1;
		while(i < line.size()) { // Le ate o final da linha
			while (line[i] != ' ') { // Le os numeros entre espacos
				aux.push_back(line[i]); // Adiciona ao vetor auxiliar
				i++;
			}
			aux_tvertex.preferences.push_back(aux); // Joga valor convertido no vetor de arestas
			aux.clear(); // Limpa vetor para reutilizacao
			i++; // Verifica se era espaco ou pipe
		}
		g.teacher.push_back(aux_tvertex); // Adiciona o vertice auxiliar no vetor do grafo
		aux_tvertex.preferences.clear(); // Limpa dados do vetor de arestas do vertice auxiliar
    }

	//------------------------- LEITURA DAS ESCOLAS
	for (j = 0; j < 50; j++){

		getline(myfile, line);
		i = 0;

		//------------------------- LEITURA DO CODIGO
		while (line[i] != '|') { // Le valores do line ate o pipe
			aux.push_back(line[i]); // Adiciona no auxiliar para futura conversao
			i++;
		}
		aux_svertex.code = aux;
		aux.clear();

		//------------------------- LEITURA DA PREFERENCIA
		i += 1; // Pula o pipe
		while (line[i] != '|') { // Le valores do line ate o pipe
			aux.push_back(line[i]); // Adiciona no auxiliar para futura conversao
			i++;
		}
		aux_svertex.preferences = atoi(aux.c_str());
		g.school.push_back(aux_svertex); // Adiciona o vertice auxiliar no vetor do grafo

	}
    myfile.close(); // Fecha o arquivo apos finalizacao da leitura
  }
  else cout << "Unable to open file"; // RETURN -1;

  return 0;
}

int printg (graph g){

  unsigned int i, j;

    cout << "\n\t\t ### PROFESSORES  ###\n";
    for (i = 0; i < g.teacher.size(); i++){ //Imprime uma caixa com os valores de cada vertice do grafo
      cout << "==========================================================================================" << endl;
      cout << "                                                                                         |";
      cout << "\r| Code: " << g.teacher[i].code << " License: " <<  g.teacher[i].license << endl;
      cout << "                                                                                         |";
      cout << "\r| Preferences: ";
      for (j = 0; j < g.teacher[i].preferences.size(); j++){
        cout << " " << g.teacher[i].preferences[j];
      }
      cout << endl;
      cout << "==========================================================================================" << endl;

    }
/*    cout << "\n\t\t ### ESCOLAS  ###\n";
    for (i = 0; i < g.school.size(); i++){ //Imprime uma caixa com os valores de cada vertice do grafo
      cout << "==========================================================================================" << endl;
      cout << "                                                                                         |";
      cout << "\r| Code: " << g.school[i].code << " Preferences: " <<  g.school[i].preferences << endl;
      cout << endl;
      cout << "==========================================================================================" << endl;

    } */
  return 0;
}


int main () {

  graph g;

  loadfile(g);
  printg(g);


  return 0;
}
