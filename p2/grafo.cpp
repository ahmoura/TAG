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
      while(i < line.size()) { // Le ate o final da linha
        while (line[i] != ' ') { // Le os numeros entre espacos
          aux.push_back(line[i]); // Adiciona ao vetor auxiliar
          i++;
        }
        aux_vertex.requirements.push_back(atoi(aux.c_str())); // Joga valor convertido no vetor de arestas
        aux.clear(); // Limpa vetor para reutilizacao
        i++; // Verifica se era espaco ou pipe
      }

      g.digraph.push_back(aux_vertex); // Adiciona o vertice auxiliar no vetor do grafo
      aux_vertex.requirements.clear(); // Limpa dados do vetor de arestas do vertice auxiliar
    }
    myfile.close(); // Fecha o arquivo apos finalizacao da leitura
  }

  else cout << "Unable to open file"; // RETURN -1;

  return 0;
}

int printg (graph g){

  unsigned int i;

  for (i = 0; i < g.digraph.size(); i++){ //Imprime uma caixa com os valores de cada vertice do grafo
    cout << "==================================================================" << endl;
    cout << "                                                                 |";
    cout << "\r| Number: " << g.digraph[i].number << " Name: " << g.digraph[i].name << endl;
    cout << "                                                                 |";
    cout << "\r| Credits: " <<  g.digraph[i].credits << " Difficulty: " << g.digraph[i].difficulty << endl;
    cout << "                                                                 |";
    cout << "\r| Number of pre requirements: " << g.digraph[i].requirements.size() << endl;
    cout << "==================================================================" << endl;
    cout << endl;
  }

  return 0;
}

int main () {

  graph g;


  loadfile(g);
  printg(g);

  return 0;
}
