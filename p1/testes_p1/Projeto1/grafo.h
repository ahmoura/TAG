typedef struct grafo Grafo:

struct grafo{
  int poderado; //Mostra se o grafo é ponderado;
  int n_ver; // numero de vertices
  int g_max; //maximo de graus do grafo
  int** arestas; // numero de arestas
  int* grau; // qtd ou grau
}

Grafo *cria_grafo (int n_ver, int g_max, int ponderado);
