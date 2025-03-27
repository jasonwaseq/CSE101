// Jason Waseq
// jwaseq
// pa4
// Matrix.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"
#include "Matrix.h"

#define EPSILON 0.0000001

// Define Entry as a pointer to EntryObj
typedef struct EntryObj* Entry;

// Define EntryObj structure
typedef struct EntryObj {
    int col;
    double val;
} EntryObj;

// Define Matrix as a pointer to MatrixObj
typedef struct MatrixObj* Matrix;

// Define MatrixObj structure
typedef struct MatrixObj {
    List* rows;
    int size;
    int nnz;
} MatrixObj;

// Helper function to compute absolute value of a double
double absDouble(double x) {
    return (x < 0) ? -x : x;
}

// Function to create a new Entry
Entry newEntry(int col, double val) {
    Entry e = (Entry)calloc(1, sizeof(EntryObj));
    assert(e != NULL);
    e->col = col;
    e->val = val;
    return e;
}

// Function to free an Entry
void freeEntry(Entry* e) {
    if (e != NULL && *e != NULL) {
        free(*e);
        *e = NULL;
    }
}

// Function to create a new Matrix
Matrix newMatrix(int n) {
    Matrix m = (Matrix)calloc(1, sizeof(MatrixObj));
    assert(m != NULL);
    m->rows = (List*)calloc(n + 1, sizeof(List));
    for (int i = 0; i <= n; i++) {
        m->rows[i] = newList();
    }
    m->size = n;
    m->nnz = 0;
    return m;
}

// Function to free a Matrix
void freeMatrix(Matrix* m) {
    if (m != NULL && *m != NULL) {
        for (int i = 0; i <= size(*m); i++) {
            for (moveFront((*m)->rows[i]); index((*m)->rows[i]) >= 0; moveNext((*m)->rows[i])) {
                Entry e = get((*m)->rows[i]);
                freeEntry(&e);
            }
            freeList(&((*m)->rows[i]));
        }
        free((*m)->rows);
        free(*m);
        *m = NULL;
    }
}

// Function to get the size of a Matrix
int size(Matrix m) {
    return m->size;
}

// Function to get the number of non-zero elements in a Matrix
int NNZ(Matrix m) {
    return m->nnz;
}

// Function to check if two Matrices are equal
int equals(Matrix a, Matrix b) {
    if (a->size != b->size || a->nnz != b->nnz) {
        return 0;
    }
    for (int i = 1; i <= size(a); i++) {
        if (length(a->rows[i]) != length(b->rows[i])) {
            return 0;
        }
        moveFront(b->rows[i]);
        for (moveFront(a->rows[i]); index(a->rows[i]) >= 0; moveNext(a->rows[i])) {
            Entry ea = get(a->rows[i]);
            Entry eb = get(b->rows[i]);
            if (ea->col != eb->col || ea->val != eb->val) {
                return 0;
            }
            moveNext(b->rows[i]);
        }
    }
    return 1;
}

// Function to reset a Matrix to the zero state
void makeZero(Matrix m) {
    for (int i = 0; i <= size(m); i++) {
        while (length(m->rows[i]) > 0) {
            Entry e = front(m->rows[i]);
            freeEntry(&e);
            deleteFront(m->rows[i]);
        }
    }
    m->nnz = 0;
}

// Function to change an entry in the Matrix
void changeEntry(Matrix m, int i, int j, double x) {
    List row = m->rows[i];
    bool found = false;

    for (moveFront(row); index(row) >= 0; moveNext(row)) {
        Entry e = get(row);
        if (e->col == j) {
            found = true;
            if (absDouble(x) > EPSILON) {
                e->val = x; // Update the value
            } else {
                delete(row); // Remove the entry if x is zero
                freeEntry(&e);
                m->nnz--;
            }
            break;
        } else if (e->col > j) {
            if (absDouble(x) > EPSILON) {
                insertBefore(row, newEntry(j, x)); // Insert new entry
                m->nnz++;
            }
            found = true;
            break;
        }
    }

    if (!found && absDouble(x) > EPSILON) {
        append(row, newEntry(j, x)); // Append new entry at the end
        m->nnz++;
    }
}

// Function to create a copy of a Matrix
Matrix copy(Matrix a) {
    Matrix b = newMatrix(a->size);
    b->nnz = NNZ(a);
    for (int i = 1; i <= size(a); i++) {
        for (moveFront(a->rows[i]); index(a->rows[i]) >= 0; moveNext(a->rows[i])) {
            Entry e = get(a->rows[i]);
            append(b->rows[i], newEntry(e->col, e->val));
        }
    }
    return b;
}

// Function to transpose a Matrix
Matrix transpose(Matrix a) {
    Matrix b = newMatrix(size(a));
    b->nnz = NNZ(a);
    for (int i = 1; i <= size(a); i++) {
        for (moveFront(a->rows[i]); index(a->rows[i]) >= 0; moveNext(a->rows[i])) {
            Entry e = get(a->rows[i]);
            append(b->rows[e->col], newEntry(i, e->val));
        }
    }
    return b;
}

// Function to multiply a Matrix by a scalar
Matrix scalarMult(double x, Matrix a) {
    Matrix m = newMatrix(size(a));
    if (x != 0) {
        m->nnz = NNZ(a);
    }
    for (int i = 1; i <= size(a); i++) {
        for (moveFront(a->rows[i]); index(a->rows[i]) >= 0; moveNext(a->rows[i])) {
            Entry e = get(a->rows[i]);
            append(m->rows[i], newEntry(e->col, e->val * x));
        }
    }
    return m;
}

// Function to compute the sum of two Matrices
Matrix sum(Matrix a, Matrix b) {
    assert(size(a) == size(b));
    Matrix copya = copy(a);
    Matrix copyb = copy(b);
    Matrix result = newMatrix(size(a));
    for (int i = 1; i <= size(a); i++) {
        int countera = 0;
        int counterb = 0;
        Entry e1 = NULL;
        Entry e2 = NULL;
        moveFront(copya->rows[i]);
        moveFront(copyb->rows[i]);
        while (countera < length(copya->rows[i]) || counterb < length(copyb->rows[i])) {
            if (countera < length(copya->rows[i]) && counterb < length(copyb->rows[i])) {
                e1 = get(copya->rows[i]);
                e2 = get(copyb->rows[i]);
                if (e1->col == e2->col) {
                    double sum = e1->val + e2->val;
                    if (absDouble(sum) > EPSILON) {
                        append(result->rows[i], newEntry(e1->col, sum));
                        result->nnz++;
                    }
                    countera++;
                    moveNext(copya->rows[i]);
                    counterb++;
                    moveNext(copyb->rows[i]);
                } else if (e1->col < e2->col) {
                    append(result->rows[i], newEntry(e1->col, e1->val));
                    countera++;
                    moveNext(copya->rows[i]);
                    result->nnz++;
                } else {
                    append(result->rows[i], newEntry(e2->col, e2->val));
                    counterb++;
                    moveNext(copyb->rows[i]);
                    result->nnz++;
                }
            } else if (countera < length(copya->rows[i])) {
                e1 = get(copya->rows[i]);
                append(result->rows[i], newEntry(e1->col, e1->val));
                countera++;
                moveNext(copya->rows[i]);
                result->nnz++;
            } else {
                e2 = get(copyb->rows[i]);
                append(result->rows[i], newEntry(e2->col, e2->val));
                counterb++;
                moveNext(copyb->rows[i]);
                result->nnz++;
           }
       }
    }
    freeMatrix(&copya);
    freeMatrix(&copyb);
    return result;
}

// Function to compute the difference of two Matrices
Matrix diff(Matrix a, Matrix b) {
    assert(size(a) == size(b));
    Matrix result = newMatrix(size(a));
    for (int i = 1; i <= size(a); i++) {
        moveFront(a->rows[i]);
        moveFront(b->rows[i]);
        while (index(a->rows[i]) >= 0 || index(b->rows[i]) >= 0) {
            Entry ea = index(a->rows[i]) >= 0 ? get(a->rows[i]) : NULL;
            Entry eb = index(b->rows[i]) >= 0 ? get(b->rows[i]) : NULL;
            if (ea && eb && ea->col == eb->col) {
                double diff = ea->val - eb->val;
                if (absDouble(diff) > EPSILON) {
                    append(result->rows[i], newEntry(ea->col, diff));
                    result->nnz++;
                }
                moveNext(a->rows[i]);
                moveNext(b->rows[i]);
            } else if (ea && (!eb || ea->col < eb->col)) {
                append(result->rows[i], newEntry(ea->col, ea->val));
                result->nnz++;
                moveNext(a->rows[i]);
            } else {
                append(result->rows[i], newEntry(eb->col, -eb->val));
                result->nnz++;
                moveNext(b->rows[i]);
            }
        }
    }
    return result;
}

// Function to compute the dot product of two Lists
double vectorDot(List p, List q) {
    double result = 0.0;
    moveFront(p);
    moveFront(q);
    while (index(p) >= 0 && index(q) >= 0) {
	Entry ep = get(p);
        Entry eq = get(q);
        if (ep->col == eq->col) {
            result += ep->val * eq->val;
            moveNext(p);
            moveNext(q);
        } else if (ep->col < eq->col) {
            moveNext(p);
        } else {
            moveNext(q);
        }
    }
    return result;
}

// Function to compute the product of two Matrices
Matrix product(Matrix a, Matrix b) {
    assert(size(a) == size(b));
    Matrix j = transpose(b);
    Matrix result = newMatrix(size(a));
   for (int i = 1; i <= size(a); i++){
	   List rowa = a->rows[i];
	   for (int k = 1; k<= size(a); k++){
		   List rowj = j->rows[k];
		   double info = vectorDot(rowa,rowj);
		   if (info !=0){
			   changeEntry(result,i,k,info);
	   }
   }
}
freeMatrix(&j);
return result;
}

// Function to print a Matrix
void printMatrix(FILE* out, Matrix m) {
    for (int i = 1; i <= size(m); i++) {
        if (length(m->rows[i]) == 0) continue;
        fprintf(out, "%d:", i);
        for (moveFront(m->rows[i]); index(m->rows[i]) >= 0; moveNext(m->rows[i])) {
            Entry e = get(m->rows[i]);
            fprintf(out, " (%d, %.1f)", e->col, e->val);
        }
        fprintf(out, "\n");
    }
}

