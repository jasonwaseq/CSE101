//-----------------------------------------------------------------------------
// Name: Jason Waseq
// CRUZID: jwaseq
// Assignment Name: pa1
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

typedef struct NodeObj* Node;

typedef struct NodeObj {
    int data;
    Node next;
    Node prev;
} NodeObj;

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

Node newNode(int data) {
    Node N = (Node)calloc(1, sizeof(NodeObj));
	assert(N != NULL);
	N->prev = NULL;
	N->data = data;
	N->next = NULL;
	return(N);
    
}

void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

List newList(){
    List L;
    L = calloc(1, sizeof(ListObj));
    assert(L != NULL);
    L->front = L->back = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}

void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      clear(*pL); 
      free(*pL);
      *pL = NULL;
      pL = NULL;
   }
}
int length(List L){
    if( L==NULL ){
        printf("List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->length);
} 
int index(List L){
    if( L==NULL ){
        printf("List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if ( L->cursor == NULL ){
        return -1;
    }else{
        return L->index;
    }
}
int front(List L){
    if( L==NULL ){
        printf("List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->front->data);
} 
int back(List L){
    if( L==NULL ){
        printf("List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->back->data);
}
int get(List L){
    if( L==NULL ){
        printf("List Error: calling get()) on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->cursor->data);
}
bool equals(List A, List B){
    if( A==NULL || B==NULL ){
        printf("List Error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    bool eq;
    Node N, M;
    eq = ( A->length == B->length );
    N = A->front;
    M = B->front;
    while( eq && N!=NULL ){
        eq = ( N->data==M->data );
        N = N->next;
        M = M->next;
    }
    return eq;
} 
void clear(List L){
    if(L!=NULL) { 
      while( L->length!=0 ) { 
         deleteFront(L); 
      }
    }
}
void set(List L, int x){
    Node N = L->cursor;
	if (N != NULL) {
		if (length(L) > 0 && index(L) >= 0) {
			L->cursor->data = x;
            L->index = index(L);
		}
	}
} 
void moveFront(List L){
    if(L->length > 0){
        L->index = 0;
        L->cursor = L->front;
    }
}
void moveBack(List L){
    if(L->length > 0){
        L->index = L->length - 1;
        L->cursor = L->back;
    }
}
void movePrev(List L){
    if(L->cursor != NULL){
        if(L->cursor != L->front){
            L->index -= 1;
            L->cursor = L->cursor->prev;
        }else if (L->cursor == L->front){
            L->cursor = NULL;
            L->index = -1;
        }
    }
}
void moveNext(List L){
    if(L->cursor != NULL){
        if(L->cursor != L->back){
            L->index += 1;
            L->cursor = L->cursor->next;
        }else if (L->cursor == L->back){
            L->cursor = NULL;
            L->index = -1;
        }
    }
}
void prepend(List L, int x){
    Node n = newNode(x);
    if(L->length > 0){
        n->next = L->front;
        L->front->prev = n;
        L->front = n;
        if(L->index != -1){
            L->index += 1;
        }
    }else{
        L->front = L->back = n;
    }
    L->length += 1;
}
void append(List L, int x){
    Node n = newNode(x);
    if(L->length > 0){
        n->prev = L->back;
        L->back->next = n;
        L->back = n;
        
    }else{
        L->back = L->front = n;
    }
    
    L->length += 1;
}
void insertBefore(List L, int x){
    if(length(L)>0 && index(L)>=0){
        if(L->cursor == L->front){
            prepend(L, x);
        }else{
            Node n = newNode(x);
            Node cursor_prev = L->cursor->prev;
            n->next = L->cursor;
            n->prev = cursor_prev;
            L->cursor->prev = n;
            cursor_prev->next = n;
            L->length += 1;
            L->index += 1;
        }
    }
} 
void insertAfter(List L, int x){
    if(length(L)>0 && index(L)>=0){
        if(L->cursor == L->back){
            append(L, x);
        }else{
            Node n = newNode(x);
            Node cursor_next = L->cursor->next;
            n->prev = L->cursor;
            n->next = cursor_next;
            L->cursor->next = n;
            cursor_next->prev = n;
            L->length += 1;
        }
    }
}
void deleteFront(List L) { 
	Node N = L->front;
	if (N != NULL) {
		if (L->length == 1) {
			freeNode(&N);
			L->front = L->back = L->cursor = NULL;
            L->index = -1;
		}
		else {
			L->front = N->next;
			freeNode(&N);
            L->index -= 1;
		}
	}
	L->length--;
	return;
}
void deleteBack(List L){
    Node N = L->back;
	if (N != NULL) {
		if (L->length == 1) {
			freeNode(&N);
			L->back = L->front = L->cursor = NULL;
            L->index = -1;
		}
		else {
            if(L->cursor == L->back){
                L->index = -1;
            }
			L->back = N->prev;
			freeNode(&N);
            L->back->next = NULL;
		}
	}
	L->length--;
	return;
}
void delete(List L){
	if (length(L) == 1) {
		freeNode(&L->cursor);
		L->front = NULL;
		L->back = NULL;
		L->length--;
        L->index = -1;
		return;
	}
	if (index(L) == 0) {
		L->front = L->cursor->next;
		freeNode(&L->cursor);
		L->length--;
        L->index = -1;
		return;
	}
	if (index(L) == (length(L)-1)) {
		L->back = L->cursor->prev;
		freeNode(&L->cursor);
        L->back->next = NULL;
		L->length--;
        L->index = -1;
		return;
	}
	L->cursor->prev->next = L->cursor->next;
	L->cursor->next->prev = L->cursor->prev;
	freeNode(&L->cursor);
	L->length--;
    L->index = -1;
	return;
}
void printList(FILE* out, List L){
    Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   for(N = L->front; N != NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
}
List copyList(List L){
    Node origin = L->cursor;
    int ori_index = L->index;
    List L1 = newList();
    for(moveFront(L); index(L) >= 0; moveNext(L)){
        append(L1, get(L));
    }

    L->cursor = origin;
    L->index = ori_index;

    return L1;

}
