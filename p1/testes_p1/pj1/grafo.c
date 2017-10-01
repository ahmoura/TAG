#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int load_file(graph* g){
  char fname[]="amigos_tag20172.txt";
  FILE *fp;
  int i, aux;

  fp = fopen(fname, "r");
  if(fp == NULL) printf("Erro, nao foi possivel abrir o arquivo\n");
  else
  while((fscanf(fp,"%d", &i))!=EOF){
    printf("%d \n", i);
    do{
      fscanf(fp,"%d", &aux);
      printf("%d", aux);
    } while (aux != -1);
    printf("/n");
  }

fclose(fp);

  return 0;
}
