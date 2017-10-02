/*
UnB - Universidade de Brasilia

Projeto 1
TAG - Teoria e Aplicacao de Grafos
Professor: Dibio

Aluno: Antonio Henrique de Moura Rodrigues
Matricula: 15 / 0118236

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
  int position;         // Numero do vertice (Equivalente a matricula)
  string name;          // Nome do aluno
  vector<int> edge;     // Lista de arestas conectadas a ele
} vertex;

typedef struct graph{ // Estrutura de grafo
  vector<vertex> adj; // Conjunto de elos (adj refere-se a adjacencia)
} graph;

vector<graph> cliques;
int printg(graph);

// Funcao de interseccao de elementos dos vetores de int;
graph intersectv(graph a, graph b){

  graph c;
  unsigned int i, j;

  for(i = 0; i < a.adj.size(); i++){
    for(j = 0; j < b.adj.size(); j++){
      if (a.adj[i].position == b.adj[j].position) c.adj.push_back(a.adj[i]); // todos valores iguais nos dois vetores sao adicionados
    }
  }

  return c;
}

// Funcao de uniao dos elementos do vetor int
graph unionv(graph a, graph b){

  graph c;
  bool flag;
  unsigned int i, j, size;

  for(i = 0; i < a.adj.size(); i++){ //Adiciona todo mundo de a em c
    c.adj.push_back(a.adj[i]);
  }

  size = c.adj.size();

  for(i = 0; i < b.adj.size(); i++){
    flag = false;
    for(j = 0; j < size; j++){
      if (b.adj[i].position == c.adj[j].position){ //Remove de c os elementos de d
        flag = true;
      }
    }
    if (flag == false) {
      c.adj.push_back(b.adj[i]); // Adiciona caso nao esteja no vetor
    }
  }

  return c;
}

// Funcao que encontra o complementar de a em relacao a b
graph complementv(graph a, graph b){

  graph c, d, e;
  bool flag;
  unsigned int i, j;


  for(i = 0; i < a.adj.size(); i++){
      c.adj.push_back(a.adj[i]);
  }

  d = intersectv (a, b); //Encontra os elementos da interseccao entre a e b

  for(i = 0; i < c.adj.size(); i++){
    flag = false;
    for(j = 0; j < d.adj.size(); j++){
      if (c.adj[i].position == d.adj[j].position){ //Remove elementos da interseccao
        flag = true;
      }
    }
    if (flag == false) {
      e.adj.push_back(c.adj[i]); //Adiciona caso nao esteja no vetor
    }
  }

  return e;

}


// Funcao para achar vizinhaca de um vertice v
graph neighborhoods (graph g, vertex v) {
  graph neighborhoods;
  unsigned int i;

  for (i = 0; i < v.edge.size(); i++) {
    neighborhoods.adj.push_back(g.adj[v.edge[i]-1]); // Procura os vertices ligados a v
  }
  return neighborhoods;
}

/*
void kahn(graph g){

    graph aux_g = g, out_g;
    int size_g = g.digraph.size();
    int i, j, k, visited = 0;

    while (aux_g.digraph.size() != 0){ //Usando aux_g de fila
                        cout << "TESTE 1";
        for (i = 0; i < aux_g.digraph.size(); i++){ // Procurando vertices com 0 chegadas
             cout << "TESTE 2";
            if (aux_g.digraph[i].nofrequirements == 0){ // Se tiver achado um vertice sem pre requisitos
            cout << "TESTE 3";
                out_g.digraph.push_back(aux_g.digraph[i]); // Copia para o grafo de saida
                k = 0;
                for(j = 0; j < aux_g.digraph.size(); j++){ // Vai procurar em todos os outros vertices se esse tem essa materia como requisito
            cout << "TESTE 4";
                    while (k <= aux_g.digraph[j].requirements.size()){ // Verifica a quantidade de pre requisitos que cada materia tem
            cout << "TESTE 5";
                       if (aux_g.digraph[j].requirements.size() != 0)
                       if (aux_g.digraph[i].number == aux_g.digraph[j].requirements[k]){ // Caso ache materia que tem ela de pre requisito
                            cout << "TESTE 6";
                            aux_g.digraph[j].requirements.erase(aux_g.digraph[j].requirements.begin()+ k); // Apaga o pre requisito
                            aux_g.digraph[j].nofrequirements--; // Tira um pre requisito da lista
                            k == aux_g.digraph[j].requirements.size(); // Ignora os proximos requisitos
                        }
                        k++;
                    }
                }
                aux_g.digraph.erase(aux_g.digraph.begin()+i);
            }
        }
    }

    printg(out_g);

}
*/

int main () {

  // Grafos da funcao bronker (Bron-Kerbosch)
  graph g;
  graph R;

  graph X;
  unsigned int i;


  loadfile(g);

  bronker(g, R, g, X);

  cout << "Clique Maximo:" << endl;
  for (i = 0; i < cliques[49].adj.size(); i++) {
    if (i != 0) {
      cout << " - ";
    }
    cout << cliques[49].adj[i].name;
  }

  cout << endl << endl << "Clique Maximal:" << endl;
  for (i = 0; i < cliques[51].adj.size(); i++) {
    if (i != 0) {
      cout << " - ";
    }
    cout << cliques[51].adj[i].name;
  }
  cout << endl;

  csort(g);
  cout << endl << "Grafo ordenado por numero de amigos:" << endl << endl;
  printg(g);

  return 0;
}
