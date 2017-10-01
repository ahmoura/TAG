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

// Funcao para ordernar o grafo em relacao ao vertice de maior grau
void csort(graph &g){

  int i, j, adj_size = g.adj.size();
  int bigger;
  vertex aux;

  for(i = 0;i < adj_size; i++){ //Procura sempre o maior e joga no inicio
    bigger = i;
    for (j = i; j < adj_size;j++){
      if (g.adj[j].edge.size() > g.adj[bigger].edge.size()) bigger = j;
    }
    aux = g.adj[i];
    g.adj[i] = g.adj[bigger];
    g.adj[bigger] = aux;
  }
}

// Funcao para imprimir na tela os vertices
int printg (graph g){

  unsigned int i;

  for (i = 0; i < g.adj.size(); i++){ //Imprime uma caixa com os valores de cada vertice do grafo
    cout << "==================================================================" << endl;
    cout << "                                                                 |";
    cout << "\r| Nome: " << g.adj[i].name << " Elo: " << g.adj[i].position << endl;
    cout << "                                                                 |";
    cout << "\r| Numero de arestas: " <<  g.adj[i].edge.size() <<endl;
    cout << "==================================================================" << endl;
    cout << endl;
  }

  return 0;
}

// Funcao para copiar os dados do arquivo para o grafo do programa
int loadfile (graph &g){

  unsigned int i;
  ifstream myfile("amigos_tag20172.txt"); // nome do arquivo
  string line; // auxiliador para pegar linhas do arquivo
  string aux; // auxiliador para converter os valores das linhas do arquivo
  vertex aux_vertex;

  if(myfile.is_open()){ // Se abrir o arquivo, exercuta
    while(getline(myfile, line)){ //Enquanto for lido linha faz

      i = 0;
      while (line[i] != '|') { // Le valores do line ate o pipe
        aux.push_back(line[i]); // Adiciona no auxiliar para futura conversao
        i++;
      }

      aux_vertex.position = atoi(aux.c_str()); // Converte auxiliar para int
      aux.clear(); // Limpa vetor para reaproveitamento

      i += 1; // Pula o pipe
      while(line[i] != '|') { // Le ate o proximo pipe
        while (line[i] != ' ' && line[i] != '|') { // Le os numeros entre espacos
          aux.push_back(line[i]); // Adiciona ao vetor auxiliar
          i++;
        }
        aux_vertex.edge.push_back(atoi(aux.c_str())); // Joga valor convertido no vetor de arestas
        aux.clear(); // Limpa vetor para reutilizacao
        if (line[i] == ' ') i++; // Verifica se era espaco ou pipe
      }

      i += 1; // Pula o proximo pipe
      while(i < line.size()) { // Le ate o final da linha
        aux.push_back(line[i]); // Adiciona no vetor auxiliar
        i++;
      }
      aux_vertex.name = aux; // Nao necessita de conversao, apenas copia para o nome
      aux.clear(); // Limpa vetor para reutilizacao da proxima linha

      g.adj.push_back(aux_vertex); // Adiciona o vertice auxiliar no vetor do grafo
      aux_vertex.edge.clear(); // Limpa dados do vetor de arestas do vertice auxiliar
      cout << endl;
    }
    myfile.close(); // Fecha o arquivo apos finalizacao da leitura
  }

  else cout << "Unable to open file"; // RETURN -1;

  return 0;
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

// Funcao para achar os cliques do grafo, segundo algoritimo do slide e da wikipedia
void bronker(graph g, graph R, graph P, graph X) {
  unsigned int i;
  graph aux;
  graph ordenado;
  vertex pivo;
  graph complementar;

  if (P.adj.empty() && X.adj.empty()) {
    cliques.push_back(R); // Retorna o clique maximal que foi formado em R
    return;
  }

  ordenado = unionv(P, X);
  csort(ordenado);
  pivo = ordenado.adj[0];

  complementar = complementv(P, neighborhoods(g, pivo));
  for (i = 0; i < complementar.adj.size(); i++) { // Recursividade da funcao (Seguindo slide)
    aux.adj.push_back(complementar.adj[i]);

    bronker(g, unionv(R, aux), intersectv(P, neighborhoods(g, complementar.adj[i])), intersectv(X, neighborhoods(g, complementar.adj[i])));
    P = complementv(P, aux);
    X = unionv(X, aux);

    aux.adj.clear();
  }
}


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
