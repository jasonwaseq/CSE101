//-----------------------------------------------------------------------------
// Name: Jason Waseq
// CRUZID: jwaseq
// Assignment Name: pa1
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 600

int main(int argc, char * argv[]){

   int line_count;
   FILE *in, *out;
   char line[MAX_LEN];
 
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
   line_count = 0;
   while( fgets(line, MAX_LEN, in) != NULL)  {
      line_count++;
   }
   rewind(in);
   char** lex_array = (char**) calloc (line_count, sizeof(char*));
   int ll_index = 0;
   while( fgets(line, MAX_LEN, in) != NULL) {
      lex_array[ll_index] = malloc((sizeof(line) + 1) * sizeof(char));
      strcpy(lex_array[ll_index], line);
      ll_index++;
   }

   List lex_list = newList();
   append(lex_list, 0);
   moveFront(lex_list);
   int j = 0;
   for(int i = 1; i < line_count; i++){
      moveFront(lex_list);
      j = 0;
      while(j < line_count){
         if(strcmp(lex_array[get(lex_list)], lex_array[i]) >= 0){
            insertBefore(lex_list, i);
            break;
         }else if(strcmp(lex_array[get(lex_list)], lex_array[i]) < 0){
            moveNext(lex_list);
            j++;
         }
         if(index(lex_list) < 0){
            append(lex_list, i);
            break;
         }
      }
   }


   moveFront(lex_list);
   while(index(lex_list) >= 0){
      int indices = get(lex_list);
      fprintf(out, "%s", lex_array[indices]);
      moveNext(lex_list);
   }
   freeList(&lex_list);
   for(int i = 0; i < line_count; i++){
      free(lex_array[i]);
   }
   free(lex_array);

   fclose(in);
   fclose(out);

   return(0);
}
