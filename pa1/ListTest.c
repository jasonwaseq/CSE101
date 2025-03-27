//-----------------------------------------------------------------------------
// Name: Jason Waseq
// CRUZID: jwaseq
// Assignment Name: pa1
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = NULL;
   int i;

   for(i=1; i<=21; i++){
      append(A,i);
      prepend(B,i);
   }
   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");
   C = copyList(A);
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,C)?"true":"false");
   printf("%s\n", equals(C,A)?"true":"false");
   moveFront(A);
   for(i=0; i<6; i++) moveNext(A); 
   insertBefore(A, -1);           
   for(i=0; i<7; i++) moveNext(A); 
   insertAfter(A, -2);
   for(i=0; i<4; i++) movePrev(A); 
   printf("Front %d\n", front(A));
   printf("Back %d\n", back(A));
   printList(stdout,A);
   printf("\nDelete Front\n");
   deleteFront(A);
   printList(stdout,A);
   printf("\n");
   printf("\nDelete Back\n");
   deleteBack(A);
   printList(stdout,A);
   printf("\n");
   printf("\nFront %d\n", front(A));
   printf("Back %d\n", back(A));
   printList(stdout,A);
   moveFront(A); 
   for(i=0; i<11; i++) moveNext(A); 
   printf("\nRun Set\n");
   set(A, 300);
   printList(stdout,A);
   printf("\n");
   printf("\nDelete\n");
   moveFront(A);
   for(i=0; i<18; i++) moveNext(A);
   delete(A);
   printList(stdout,A);
   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);

   return(0);
}

/*
Output:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
false
false
true
Front 1
Back 21
1 2 3 4 5 6 -1 7 8 9 10 11 12 13 14 -2 15 16 17 18 19 20 21
Delete Front
2 3 4 5 6 -1 7 8 9 10 11 12 13 14 -2 15 16 17 18 19 20 21

Delete Back
2 3 4 5 6 -1 7 8 9 10 11 12 13 14 -2 15 16 17 18 19 20

Front 2
Back 20
2 3 4 5 6 -1 7 8 9 10 11 12 13 14 -2 15 16 17 18 19 20
Run Set
2 3 4 5 6 -1 7 8 9 10 11 300 13 14 -2 15 16 17 18 19 20

Delete
2 3 4 5 6 -1 7 8 9 10 11 300 13 14 -2 15 16 17 19 20
20
0
*/
