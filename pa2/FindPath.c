//-----------------------------------------------------------------------------
// Jason Waseq
// jwaseq
// pa2
// FindPath.c
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char * argv[]){

   
   FILE *in, *out;

   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

    int n = 0;
    fscanf(in, "%d", &n);
    Graph g = newGraph(n);

    int uVertex = 0;
    int vVertex = 0;
    fscanf(in, "%d %d\n", &uVertex, &vVertex);
    while(uVertex != 0 || vVertex != 0){
        addEdge(g, uVertex, vVertex);
        fscanf(in, "%d %d\n", &uVertex, &vVertex);
    }

    printGraph(out, g);
    fflush(out);

    int source = 0;
    int end = 0;
    fscanf(in, "%d %d\n", &source, &end);
    while(source != 0 || end != 0){
        if (source != end){
            BFS(g, source);
            int distance = getDist(g, end);
            if(distance != INF){
                fprintf(out, "\nThe distance from %d to %d is %d\n", source, end, distance);
            }else{
                fprintf(out, "\nThe distance from %d to %d is infinity\n", source, end);
            }
            List path = newList();
            getPath(path, g, end);
            if(distance != INF){
                fprintf(out, "A shortest %d-%d path is: ", source, end);
                printList(out, path);
                fprintf(out,"\n");
            }else{
                fprintf(out, "No %d-%d path exists\n", source, end);
            }
            freeList(&path);
            fscanf(in, "%d %d\n", &source, &end);
        }else{
            fprintf(out, "\nThe distance from %d to %d is 0\n", source, end);
            fprintf(out, "A shortest %d-%d path is: %d\n", source, end, source);
            fscanf(in, "%d %d\n", &source, &end);
        }
    }

   fclose(in);
   fclose(out);
   freeGraph(&g);

   return(0);
}

