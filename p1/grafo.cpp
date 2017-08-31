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

typedef struct node{
  int position;
  string name;
  vector<int> vertex;
} node;

typedef struct graph{
  vector<node> adj;
} graph;

void csort(graph &g){

  int i, j, adj_size = g.adj.size();
  int bigger;
  node aux;

  for(i = 0;i < adj_size; i++){
    bigger = i;
    for (j = i; j < adj_size;j++){
      if (g.adj[j].vertex.size() > g.adj[bigger].vertex.size()) bigger = j;
    }
    aux = g.adj[i];
    g.adj[i] = g.adj[bigger];
    g.adj[bigger] = aux;

  }
}

int printg (graph g){

  unsigned int i;

  for (i = 0; i < g.adj.size(); i++){
    cout << "==================================================================" << endl;
    cout << "                                                                 |";
    cout << "\r| Nome: " << g.adj[i].name << " Elo: " << g.adj[i].position << endl;
    cout << "                                                                 |";
    cout << "\r| Numero de vertices: " <<  g.adj[i].vertex.size() <<endl;
    cout << "==================================================================" << endl;
    cout << endl;
  }

/*
  unsigned int i, j;

  for (i = 0; i < g.adj.size(); i++){
    cout << g.adj[i].position << " " <<  g.adj[i].name << " ";
    for (j = 0; j < g.adj[i].vertex.size(); j++) {
      cout << g.adj[i].vertex[j] << " ";
    }
    cout << endl;
  }
*/

  return 0;
}

/// Loadfile:
int loadfile (graph &g){

  unsigned int i;
  ifstream myfile("amigos_tag20172.txt"); // ifstream = padrão ios:in
  string line;
  string aux;
  //temporario
  node aux_edge;

  if(myfile.is_open()){
    while(getline(myfile, line)){

      //--------------------
      i = 0;
      while (line[i] != '|') {
        aux.push_back(line[i]);
        i++;
      }

      aux_edge.position = atoi(aux.c_str());
      aux.clear();

      //--------------------------
      i += 1;
      while(line[i] != '|') {
        while (line[i] != ' ' && line[i] != '|') {
          aux.push_back(line[i]);
          i++;
        }
        aux_edge.vertex.push_back(atoi(aux.c_str()));
        aux.clear();
        if (line[i] == ' ') i++;
      }

      //--------------------------
      i += 1;
      while(i < line.size()) {
        aux.push_back(line[i]);
        i++;
      }
      aux_edge.name = aux;
      aux.clear();

      //---------------------------
      g.adj.push_back(aux_edge);
      aux_edge.vertex.clear();
      cout << endl;
    }
    myfile.close();
  }

  else cout << "Unable to open file"; // RETURN -1;

  return 0;
}

int main () {

  graph g;

  loadfile(g);
  csort(g);
  printg(g);

  return 0;
}
