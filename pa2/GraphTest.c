//-----------------------------------------------------------------------------
// Jason Waseq
// jwaseq
// pa2
// GraphTest.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
   int i, s, max, min, d, n=35;
   List  C = newList(); 
   List  P = newList(); 
   List  E = newList(); 
   Graph G = NULL;

   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   printGraph(stdout, G);

   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }
   int order = getOrder(G);
   int size = getSize(G);
   int source = getSource(G);
   int parent = getParent(G, 6);

   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");
   printf("Total Vertices: %d", order);
   printf("\n");
   printf("Total Edges: %d", size);
   printf("\n");
   printf("Current Source: %d", source);
   printf("\n");
   printf("Parent of 6: %d", parent);
   List L = newList();
   getPath(L, G, 30);
   printf("\n");
   printf("Path from 35-30: ");
   printList(stdout, L);

   printf("\n");
   printf("After makeNull on Graph G: ");
   makeNull(G);
   printGraph(stdout, G);

   Graph H = newGraph(5);   
   addArc(H, 1, 3);
   addArc(H, 2, 4);
   printf("\nAdd Arc on Graph H: \n");
   printGraph(stdout, H);

   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeList(&L);
   freeGraph(&G);
   freeGraph(&H);

   return(0);
}

/*
Output:
1: 2 8
2: 1 3 9
3: 2 4 10
4: 3 5 11
5: 4 6 12
6: 5 7 13
7: 6 14
8: 1 9 15
9: 2 8 10 16 31
10: 3 9 11 17
11: 4 10 12 18
12: 5 11 13 19
13: 6 12 14 17 20
14: 7 13 21 33
15: 8 16 22
16: 9 15 17 23
17: 10 13 16 18 24
18: 11 17 19 25
19: 12 18 20 26
20: 13 19 21 27
21: 14 20 28
22: 15 23 29
23: 16 22 24 30
24: 17 23 25 31
25: 18 24 26 32
26: 19 25 27 33
27: 20 26 28 34
28: 21 27 35
29: 22 30
30: 23 29 31
31: 9 24 30 32
32: 25 31 33
33: 14 26 32 34
34: 27 33 35
35: 28 34

Radius = 5
Central vertices: 13 17 18 24 25 31 32 33
Diameter = 8
Peripheral vertices: 1 28
Total Vertices: 35
Total Edges: 61
Current Source: 35
Parent of 6: 7
Path from 35-30: 35 34 33 32 31 30
After makeNull on Graph G:
Add Arc on Graph H:
1: 3
2: 4
3:
4:
5:
*/
