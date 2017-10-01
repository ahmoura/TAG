#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

Grafo *cria_grafo (int n_ver, int g_max, int ponderado){
  Grafo *gf = (Grafo*) malloc(sizeof (Grafo))
  if (gr != 0){
    int i;
    gr->n_ver = n_ver;
    gr->g_max = g_max;
    gr->ponderado = (ponderado != 0)?1:0;
    gr->grau = (int*) calloc (n_ver, sizeof(int));
    gr->arestas = (int**) malloc(n_ver*sizeof(int*));
    for (i = 0; i < n_ver; i++){
      gr->arestas[i] = (int*) malloc (g_max)
    }
  }
}
