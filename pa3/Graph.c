//-----------------------------------------------------------------------------
// Jason Waseq
// jwaseq
// pa3
// Graph.c
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"
#include "Graph.h"

typedef struct GraphObj{
    List* adjacencyList;
   char** color;
    int** parent;
    int** discover;
    int** finish;
    int order;
    int size;
} GraphObj;

Graph newGraph(int n){
    Graph g = (Graph)calloc(1, sizeof(GraphObj));
    assert(g != NULL);
    g->adjacencyList = (List*)calloc(n + 1, sizeof(List));
    g->color = calloc(n + 1, sizeof(char*));
    g->parent = calloc(n + 1, sizeof(int*));
    g->discover = calloc(n + 1, sizeof(int*));
    g->finish = calloc(n + 1, sizeof(int*));

    for(int i = 0; i <= n; i++){
        g->adjacencyList[i] = newList();
        g->color[i] = calloc(1, sizeof(char));
        g->parent[i] = calloc(1, sizeof(int));
        g->discover[i] = calloc(1, sizeof(int));
        g->finish[i] = calloc(1, sizeof(int));
        *(g->color[i]) = 'w';
        *(g->parent[i]) = NIL;
        *(g->discover[i]) = UNDEF;
        *(g->finish[i]) = UNDEF;
    }

    g->order = n;
    g->size = 0;
    return g;
}

void freeGraph(Graph* pG){
    if(pG!=NULL && *pG!=NULL) { 
        for(int i = 0; i <= (*pG)->order; i++){
            freeList(&((*pG)->adjacencyList[i]));
            free((*pG)->color[i]);
            free((*pG)->parent[i]);
            free((*pG)->discover[i]);
            free((*pG)->finish[i]);
        }
      free(((*pG)->color));
      free(((*pG)->parent));
      free(((*pG)->discover));
      free(((*pG)->finish));
      free((*pG)->adjacencyList);
      free(*pG);
      *pG = NULL;
      pG = NULL;
   }
}

int getOrder(Graph G){
    return G->order;
}
int getSize(Graph G){
    return G->size;
}
int getParent(Graph G, int u){
    if(u >= 1 && u <= getOrder(G)){
        return *(G->parent[u]);
        
    }else{
        return NIL;
    }
}

int getDiscover(Graph G, int u){
    if(u >= 1 && u <= getOrder(G)){
        return *(G->discover[u]);
    }else{
        return NIL;
    }
}

int getFinish(Graph G, int u){
    if(u >= 1 && u <= getOrder(G)){
        return *(G->finish[u]);
    }else{
        return NIL;
    }
}

void addEdge(Graph G, int u, int v){
    if (u == v){
        return;
    }
    
    int i, y = 0;
    if (length(G->adjacencyList[u]) > 0) {
        moveFront(G->adjacencyList[u]);
        y = get(G->adjacencyList[u]);
        if (v < y) {
            prepend(G->adjacencyList[u], v);
        }
        else {
            for (i = 1; i < length(G->adjacencyList[u]); i++) {
                moveNext(G->adjacencyList[u]);
                y = get(G->adjacencyList[u]);
                if (v < y) {
                    insertBefore(G->adjacencyList[u], v);
                    break;
                }
            }
        }
        moveBack(G->adjacencyList[u]);
        y = get(G->adjacencyList[u]);
        if (y < v) {
            append(G->adjacencyList[u], v);
        }
    }
    else {
        append(G->adjacencyList[u], v);
    }
    if (length(G->adjacencyList[v]) > 0) {
        moveFront(G->adjacencyList[v]);
        y = get(G->adjacencyList[v]);
        if (u < y) {
            prepend(G->adjacencyList[v], u);
        }
        else {
            for (i = 1; i < length(G->adjacencyList[v]); i++) {
                moveNext(G->adjacencyList[v]);
                y = get(G->adjacencyList[v]);
                if (u < y) {
                    insertBefore(G->adjacencyList[v], u);
                    break;
                }
            }
        }
        moveBack(G->adjacencyList[v]);
        y = get(G->adjacencyList[v]);
        if (y < u) {
            append(G->adjacencyList[v], u);
        }
    }
    else {
        append(G->adjacencyList[v], u);
    }
    G->size++;
}

void addArc(Graph G, int u, int v) {
    int i, y = 0;
    if (length(G->adjacencyList[u]) > 0) {
        moveFront(G->adjacencyList[u]);
        y = get(G->adjacencyList[u]);
        if (v < y) {
            prepend(G->adjacencyList[u], v);
            G->size++;
        }
        else {
            for (i = 1; i < length(G->adjacencyList[u]); i++) {
                moveNext(G->adjacencyList[u]);
                y = get(G->adjacencyList[u]);
                if (v < y) {
                    insertBefore(G->adjacencyList[u], v);
                    G->size++;
                    break;
                }
            }
        }
        moveBack(G->adjacencyList[u]);
        y = get(G->adjacencyList[u]);
        if (y < v) {
            append(G->adjacencyList[u], v);
            G->size++;
        }
    }
    else {
        append(G->adjacencyList[u], v);
        G->size++;
    }
}

void Visit(Graph G, List S, int x, int * ptime) {
    (*ptime)++;
    *(G->discover[x]) = *ptime;
    *(G->color[x]) = 'g';
    int y;
    for (moveFront(G->adjacencyList[x]); index(G->adjacencyList[x]) >= 0; moveNext(G->adjacencyList[x])) {
        y = get(G->adjacencyList[x]);
        if (*(G->color[y]) == 'w') {
            *(G->parent[y]) = x;
            Visit(G, S, y, ptime);
        }
    }
    *(G->color[x]) = 'b';
    (*ptime)++;
    *(G->finish[x]) = *ptime;
    append(S, x);

}

void DFS(Graph G, List S){
    for(int x = 0; x <= getOrder(G); x++){
        *(G->color[x]) = 'w';
        *(G->parent[x]) = NIL;
    }
    int time = 0;

    for(int x = 1; x <= getOrder(G); x++){
        int y = front(S);
        deleteFront(S);
        if (*(G->color[y]) == 'w') {
            Visit(G, S, y, &time);
        }
    }

    List S1 = newList();
    for (moveFront(S); index(S) >= 0; moveNext(S)) {
        int y = get(S);
        prepend(S1, y);
    }
    clear(S);
    for (moveFront(S1); index(S1) >= 0; moveNext(S1)) {
        int y = get(S1);
        append(S, y);
    }
    freeList(&S1);
}


Graph transpose(Graph G) {
    Graph outgraph = newGraph(getOrder(G));
    for (int x = 1; x <= getOrder(G); x++){
        for (moveFront(G->adjacencyList[x]); index(G->adjacencyList[x]) >= 0; moveNext(G->adjacencyList[x])) {
            int y = get(G->adjacencyList[x]);
            addArc(outgraph, y, x);
        }
    }
    return outgraph;
}
Graph copyGraph(Graph G){
    Graph outgraph = newGraph(getOrder(G));
    for (int x = 1; x <= getOrder(G); x++){
        for (moveFront(G->adjacencyList[x]); index(G->adjacencyList[x]) >= 0; moveNext(G->adjacencyList[x])) {
            int y = get(G->adjacencyList[x]);
            addArc(outgraph, x, y);
        }
    }
    return outgraph;
}

void printGraph(FILE* out, Graph G){
    for(int i = 1; i <= getOrder(G); i++){
        moveFront(G->adjacencyList[i]);
        fprintf(out, "%d:", i);
        while(index(G->adjacencyList[i]) >= 0){
            int neighbor = get(G->adjacencyList[i]);
            fprintf(out, " %d", neighbor);
            moveNext(G->adjacencyList[i]);
        }
        if(length(G->adjacencyList[i]) == 0){
            fprintf(out, " ");
        }
        fprintf(out, "\n");
    }
}

