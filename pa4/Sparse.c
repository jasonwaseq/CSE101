// Jason Waseq
// jwaseq
// pa4
// Sparse.c

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "List.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    FILE* in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    FILE* out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    int n, a, b;
    fscanf(in, "%d %d %d", &n, &a, &b);

    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    // Read matrix A
    for (int i = 0; i < a; i++) {
        int row, col;
        double value;
        fscanf(in, "%d %d %lf", &row, &col, &value);
        changeEntry(A, row, col, value);
    }

    // Read matrix B
    for (int i = 0; i < b; i++) {
        int row, col;
        double value;
        fscanf(in, "%d %d %lf", &row, &col, &value);
        changeEntry(B, row, col, value);
    }

    // Print matrices and perform operations
    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    Matrix scalarA = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, scalarA);
    fprintf(out, "\n");

    Matrix sumAB = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, sumAB);
    fprintf(out, "\n");

    Matrix sumAA = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, sumAA);
    fprintf(out, "\n");

    Matrix diffBA = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, diffBA);
    fprintf(out, "\n");

    Matrix diffAA = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, diffAA);
    fprintf(out, "\n");

    Matrix transA = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, transA);
    fprintf(out, "\n");

    Matrix prodAB = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, prodAB);
    fprintf(out, "\n");

    Matrix prodBB = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, prodBB);
    fprintf(out, "\n");

    // Free matrices
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&scalarA);
    freeMatrix(&sumAB);
    freeMatrix(&sumAA);
    freeMatrix(&diffBA);
    freeMatrix(&diffAA);
    freeMatrix(&transA);
    freeMatrix(&prodAB);
    freeMatrix(&prodBB);

    fclose(in);
    fclose(out);

    return 0;
}

