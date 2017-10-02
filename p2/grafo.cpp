/*
UnB - Universidade de Brasilia

Projeto 2
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

typedef struct vertex{  // Estrutura de elo
  int number;           // Numero do vertice (Equivalente a matricula)
  string name;          // Nome do aluno
  int credits;          // creditos de cada materia
  int difficulty;       // ou weight: peso da materia
  int nofrequirements;  // numeros de requirements
  vector<int> requirements;     // Lista de arestas conectadas a ele
} vertex;

typedef struct graph{ // Estrutura de grafo
  vector<vertex> digraph; // Conjunto de elos (digrafo pq tem direcao)
} graph;

int loadfile (graph &g){

  unsigned int i;
  ifstream myfile("materias_cic.txt"); // nome do arquivo
  string line; // auxiliador para pegar linhas do arquivo
  string aux; // auxiliador para converter os valores das linhas do arquivo
  vertex aux_vertex;

  if(myfile.is_open()){ // Se abrir o arquivo, exercuta
    while(getline(myfile, line)){ //Enquanto for lido linha faz


      //------------------------------------NUMERO
      i = 0;
      while (line[i] != '|') { // Le valores do line ate o pipe
        aux.push_back(line[i]); // Adiciona no auxiliar para futura conversao
        i++;
      }

      aux_vertex.number = atoi(aux.c_str()); // Converte auxiliar para int
      aux.clear(); // Limpa vetor para reaproveitamento
      //------------------------------------NOME
      i += 1; // Pula o pipe
      while (line[i] != '|') { // Le valores do line ate o pipe
        aux.push_back(line[i]); // Adiciona no auxiliar para futura conversao
        i++;
      }

      aux_vertex.name = aux.c_str(); // Converte auxiliar para int
      aux.clear(); // Limpa vetor para reaproveitamento
      //------------------------------------CREDITOS
      i += 1; // Pula o pipe
      while (line[i] != '|') { // Le valores do line ate o pipe
        aux.push_back(line[i]); // Adiciona no auxiliar para futura conversao
        i++;
      }

      aux_vertex.credits = atoi(aux.c_str()); // Converte auxiliar para int
      aux.clear(); // Limpa vetor para reaproveitamento
      //------------------------------------PESO
      i += 1; // Pula o pipe
      while (line[i] != '|') { // Le valores do line ate o pipe
        aux.push_back(line[i]); // Adiciona no auxiliar para futura conversao
        i++;
      }
      aux_vertex.difficulty = atoi(aux.c_str()); // Converte auxiliar para int
      aux.clear(); // Limpa vetor para reaproveitamento
      //------------------------------------PRE REQUISITOS
      i += 1; // Pula o pipe
	  aux_vertex.nofrequirements = 0;
      while(i < line.size()) { // Le ate o final da linha
        while (line[i] != ' ') { // Le os numeros entre espacos
          aux.push_back(line[i]); // Adiciona ao vetor auxiliar
          i++;
        }
        aux_vertex.requirements.push_back(atoi(aux.c_str())); // Joga valor convertido no vetor de arestas
        aux.clear(); // Limpa vetor para reutilizacao
        i++; // Verifica se era espaco ou pipe
        aux_vertex.nofrequirements++;
      }

      g.digraph.push_back(aux_vertex); // Adiciona o vertice auxiliar no vetor do grafo
      aux_vertex.requirements.clear(); // Limpa dados do vetor de arestas do vertice auxiliar
    }
    myfile.close(); // Fecha o arquivo apos finalizacao da leitura
  }

  else cout << "Unable to open file"; // RETURN -1;

  return 0;
}

int printg (int mode, graph g){

  unsigned int i;


  if (mode == 0){
    for (i = 0; i < g.digraph.size(); i++){ //Imprime uma caixa com os valores de cada vertice do grafo
      cout << "==================================================================" << endl;
      cout << "                                                                 |";
      cout << "\r| Number: " << g.digraph[i].number << " Name: " << g.digraph[i].name << endl;
      cout << "                                                                 |";
      cout << "\r| Credits: " <<  g.digraph[i].credits << " Difficulty: " << g.digraph[i].difficulty << endl;
      cout << "                                                                 |";
      cout << "\r| Number of pre requirements: " << g.digraph[i].nofrequirements << " " << g.digraph[i].requirements.size() << endl;
      cout << "==================================================================" << endl;
      cout << endl;
    }
  } else {
    cout << "\n\t\t ### Ordenacao Topologica  ###\n Inicio";
    for (i = 0; i < g.digraph.size(); i++){ //Imprime uma caixa com os valores de cada vertice do grafo
       cout << " -> " << g.digraph[i].number;
    }
    cout << " -> Fim \n\n\n";
  }
  return 0;
}

void csort(graph &g){

  int i, j, graph_size = g.digraph.size();
  int bigger;
  vertex aux;

  for(i = 0;i < graph_size; i++){ //Procura sempre o maior e joga no inicio
    bigger = i;
    for (j = i; j < graph_size;j++){
      if (g.digraph[j].requirements.size() < g.digraph[bigger].requirements.size()) bigger = j;
    }
    aux = g.digraph[i];
    g.digraph[i] = g.digraph[bigger];
    g.digraph[bigger] = aux;
  }
}

void kahn(graph g){

    graph copy_g = g, aux_g, out_g;
    int size_g;
    unsigned i, j, k, visited = 0;

    for (i = 0; i < copy_g.digraph.size(); i++){
        if (copy_g.digraph[i].nofrequirements == 0){
            aux_g.digraph.push_back(copy_g.digraph[i]);
            copy_g.digraph.erase(copy_g.digraph.begin()+i);
            i--;
        }
    }
    size_g = aux_g.digraph.size();
    while (size_g != 0){
        out_g.digraph.push_back(aux_g.digraph[0]);
        visited++;
        for(j = 0; j < copy_g.digraph.size(); j++){
            for (k = 0; k < copy_g.digraph[j].requirements.size(); k++){
                if (aux_g.digraph[0].number == copy_g.digraph[j].requirements[k]){
                    copy_g.digraph[j].requirements.erase(copy_g.digraph[j].requirements.begin()+k);
                    copy_g.digraph[j].nofrequirements--;
                    if (copy_g.digraph[j].nofrequirements == 0) {
                            aux_g.digraph.push_back(copy_g.digraph[j]);
                            size_g++;
                    }
                }
            }
        }
        aux_g.digraph.erase(aux_g.digraph.begin());
        size_g--;

    }

    if (visited != g.digraph.size()) cout << "\n Error!";
    printg(1, out_g);

}

int main () {

  graph g;


  loadfile(g);
  csort(g);
  //printg(g);
  kahn(g);


  return 0;
}
