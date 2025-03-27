#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include<stdbool.h>

#include "List.h"

#define UNDEF -1
#define NIL 0

typedef struct GraphObj* Graph;

Graph newGraph(int n);
void freeGraph(Graph* pG);
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); 
int getDiscover(Graph G, int u); 
int getFinish(Graph G, int u); 
void addArc(Graph G, int u, int v); 
void addEdge(Graph G, int u, int v); 
void DFS(Graph G, List S); 
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);

#endif

