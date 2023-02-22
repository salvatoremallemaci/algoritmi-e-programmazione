#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"

#define MAX 30

typedef struct edge{
int v;
int w;
int wt;
}Edge;

typedef struct graph *GRAPH;

GRAPH GRAPH_init(int V);
void GRAPHfree(GRAPH G);
void GRAPH_insertE(GRAPH G,int id1, int id2, int wt);
void GRAPH_printVERTEX(GRAPH G);
void GRAPH_setTab(GRAPH G, ST tab);
void GRAPH_sottografo_completo(GRAPH G, char **vertex);
void GRAPH_generate_Ladj(GRAPH G);
void GRAPH_print_Ladj(GRAPH G);


#endif // GRAPH_H
