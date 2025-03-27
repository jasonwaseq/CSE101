//-----------------------------------------------------------------------------
// Jason Waseq
// jwaseq
// pa2
// Graph.c
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Graph.h"

typedef struct GraphObj{
    List* adjacencyList;
    char** color;
    int** parent;
    int** distance;
    int order;
    int size;
    int source;
    
} GraphObj;

Graph newGraph(int n){
    Graph g = (Graph)calloc(1, sizeof(GraphObj));
    assert(g != NULL);
    g->adjacencyList = (List*)calloc(n + 1, sizeof(List));

    g->color = calloc(n + 1, sizeof(char*));
    g->parent = calloc(n + 1, sizeof(int*));
    g->distance = calloc(n + 1, sizeof(int*));

    for(int i = 0; i <= n; i++){
        g->adjacencyList[i] = newList();
        g->color[i] = calloc(1, sizeof(char));
        g->parent[i] = calloc(1, sizeof(int));
        g->distance[i] = calloc(1, sizeof(int));
        *(g->color[i]) = 'w';
        *(g->parent[i]) = NIL;
        *(g->distance[i]) = INF;
    }
    g->order = n;
    g->size = 0;
    g->source = NIL;
    return g;
}

void freeGraph(Graph* pG){
    if(pG!=NULL && *pG!=NULL) { 
        for(int i = 0; i <= (*pG)->order; i++){
            freeList(&((*pG)->adjacencyList[i]));
            free((*pG)->color[i]);
            free((*pG)->parent[i]);
            free((*pG)->distance[i]);
        }
      free(((*pG)->color));
      free(((*pG)->parent));
      free(((*pG)->distance));
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
int getSource(Graph G){
    return G->source;
}

int getParent(Graph G, int u){
    if(u >= 1 && u <= getOrder(G)){
        if(G->source == NIL){
            return NIL;
        }else{
            return *(G->parent[u]);
        }
        
    }else{
        return NIL;
    }
}

int getDist(Graph G, int u){
    return *(G->distance[u]);
}

void getPath(List L, Graph G, int u){
    int x = u;
    int y = NIL;
    if (u >= 1 && u <= getOrder(G)) {
        if (u == getSource(G)) {
            append(L, u);
            return;
        }
        if (getParent(G, x) == NIL) {
            append(L, NIL);
            return;
        }
        while (x != getSource(G)) {
            y = getParent(G, x);
            if (y == NIL) {
                break;
            }
            prepend(L, x);
            x = y;
        }
        if (y != NIL) {
            prepend(L, getSource(G));
        }
    }
}

void makeNull(Graph G){
    for(int i = 0; i <= G->order; i++){
        clear(G->adjacencyList[i]);
        *(G->color[i]) = 'w';
        *(G->distance[i]) = INF;
        *(G->parent[i]) = NIL;
    }
    G->order = 0;
    G->source = NIL;

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

    G->size++;
}
void BFS(Graph G, int s){
    G->source = s;
    for(int x = 0; x <= G->order; x++){
        *(G->color[x]) = 'w';
        *(G->distance[x]) = INF;
        *(G->parent[x]) = NIL;
        
    }
    
    *(G->color[s]) = 'g';
    *(G->distance[s]) = 0;
    *(G->parent[s]) = NIL;
   
    List queue = newList();
    append(queue, s);
    while(length(queue) > 0){
        moveFront(queue);
        int x = front(queue);
        deleteFront(queue);

        for(moveFront(G->adjacencyList[x]); index(G->adjacencyList[x]) >= 0; moveNext(G->adjacencyList[x])){
            int y = get(G->adjacencyList[x]);
            if(*(G->color[y]) == 'w'){  
                *(G->color[y]) = 'g';   
                *(G->distance[y]) = *(G->distance[x]) + 1;
                *(G->parent[y]) = x;
                append(queue, y);

            }
        }
        *(G->color[x]) = 'b';     
    }
    freeList(&queue);
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

