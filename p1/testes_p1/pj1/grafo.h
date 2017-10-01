typedef struct node node;
struct node{
  int vertex;
  int edge;
  node* next;
};

typedef struct graph graph;
struct graph{
  node* adj_list[49];
  int degree[49];
};

int load_file(graph* g);
//int sort_by_degree();
//int print_by_degree();
