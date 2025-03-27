// Jason Waseq
// jwaseq
// pa4
// List.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

// Private Node type
typedef struct NodeObj* Node;

typedef struct NodeObj {
    void* data;
    Node next;
    Node prev;
} NodeObj;

// Private ListObj type
typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

// newNode()
// Constructor for the Node type
Node newNode(void* data) {
    Node N = (Node)malloc(sizeof(NodeObj));
    if (N == NULL) {
        fprintf(stderr, "Memory allocation error in newNode\n");
        exit(EXIT_FAILURE);
    }
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return N;
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Constructor for the List type
List newList(void) {
    List L = (List)malloc(sizeof(ListObj));
    if (L == NULL) {
        fprintf(stderr, "Memory allocation error in newList\n");
        exit(EXIT_FAILURE);
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return L;
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->cursor == NULL) ? -1 : L->index;
}

// front()
// Returns front element of L. Pre: length()>0
void* front(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        fprintf(stderr, "List Error: calling front() on empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

// back()
// Returns back element of L. Pre: length()>0
void* back(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
     if (length(L) <= 0) {
        fprintf(stderr, "List Error: calling back() on empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
void* get(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        fprintf(stderr, "List Error: calling get() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fprintf(stderr, "List Error: calling get() with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node current = L->front;
    while (current != NULL) {
        Node temp = current;
        current = current->next;
        freeNode(&temp);
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
}

// set()
// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, void* x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        fprintf(stderr, "List Error: calling set() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fprintf(stderr, "List Error: calling set() with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front of L;
// if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        if (L->cursor == L->front) {
            L->cursor = NULL;
            L->index = -1;
        } else {
            L->cursor = L->cursor->prev;
            L->index--;
        }
    }
}

// moveNext()
// If cursor is defined and not at back, move cursor one step toward the back of L;
// if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing
void moveNext(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        if (L->cursor == L->back) {
            L->cursor = NULL;
            L->index = -1;
        } else {
            L->cursor = L->cursor->next;
            L->index++;
        }
    }
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, void* x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->length == 0) {
        L->front = L->back = N;
    } else {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
        if (L->cursor != NULL) {
            L->index++;
        }
    }
    L->length++;
}

// append()
// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, void* x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->length == 0) {
        L->front = L->back = N;
    } else {
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }
    L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, void* x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0 || L->index < 0) {
        fprintf(stderr, "List Error: calling insertBefore() on empty List or undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == L->front) {
        prepend(L, x);
    } else {
        Node N = newNode(x);
        N->next = L->cursor;
        N->prev = L->cursor->prev;
        L->cursor->prev->next = N;
        L->cursor->prev = N;
        L->length++;
        L->index++;
    }
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, void* x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0 || L->index < 0) {
        fprintf(stderr, "List Error: calling insertAfter() on empty List or undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == L->back) {
        append(L, x);
    } else {
        Node N = newNode(x);
        N->next = L->cursor->next;
        N->prev = L->cursor;
        L->cursor->next->prev = N;
        L->cursor->next = N;
        L->length++;
    }
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
     if (L->length <= 0) {
        fprintf(stderr, "List Error: calling deleteFront() on empty List\n");
        exit(EXIT_FAILURE);
    }
    Node N = L->front;
    if (L->length == 1) {
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
    } else {
        L->front = N->next;
        L->front->prev = NULL;
        if (L->cursor != NULL) {
            L->index--;
        }
        if (L->cursor == N) {
            L->cursor = NULL;
            L->index = -1;
        }
    }
    freeNode(&N);
    L->length--;
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
     if (L->length <= 0) {
        fprintf(stderr, "List Error: calling deleteBack() on empty List\n");
        exit(EXIT_FAILURE);
    }
    Node N = L->back;
    if (L->length == 1) {
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
    } else {
        L->back = N->prev;
        L->back->next = NULL;
        if (L->cursor == N) {
            L->cursor = NULL;
            L->index = -1;
        }
    }
    freeNode(&N);
    L->length--;
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0 || L->index < 0) {
        fprintf(stderr, "List Error: calling delete() on empty List or undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    Node N = L->cursor;
    if (N == L->front) {
        deleteFront(L);
    } else if (N == L->back) {
        deleteBack(L);
    } else {
        N->prev->next = N->next;
        N->next->prev = N->prev;
        L->cursor = NULL;
        L->index = -1;
        freeNode(&N);
        L->length--;
    }
}

