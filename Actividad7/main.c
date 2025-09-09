#include <stdio.h>
#include <stdlib.h>

void print_spiral(int **A, int N, int M) {
    if (N <= 0 || M <= 0) { printf("\n"); return; }

    int top = 0, bottom = N - 1;
    int left = 0, right  = M - 1;
    int first = 1;

    while (top <= bottom && left <= right) {
        for (int c = left; c <= right; ++c) {
            if (!first) printf(" ");
            printf("%d", A[top][c]); first = 0;
        }
        top++;

        for (int r = top; r <= bottom; ++r) printf(" %d", A[r][right]);
        right--;

        if (top <= bottom) {
            for (int c = right; c >= left; --c) printf(" %d", A[bottom][c]);
            bottom--;
        }

        if (left <= right) {
            for (int r = bottom; r >= top; --r) printf(" %d", A[r][left]);
            left++;
        }
    }
    printf("\n");
}

int main(void) {
    int N, M;
    printf("Ingrese el numero de filas y columnas (N M): ");
    if (scanf("%d %d", &N, &M) != 2) {
        printf("Error: no se pudo leer N y M.\n");
        return 1;
    }

    int **A = (int **)malloc(N * sizeof *A);
    if (!A) return 1;

    int *block = (int *)malloc(N * M * sizeof *block);
    if (!block) { free(A); return 1; }

    for (int r = 0; r < N; ++r) A[r] = block + r * M;

    printf("Ingrese los %d elementos de la matriz (fila por fila separado con espacios):\n", N * M);
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < M; ++c) {
            scanf("%d", &A[r][c]);}

    printf("\nMatriz ingresada:\n");
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            printf("%4d", A[r][c]);
        }
        printf("\n");
    }

    printf("\nElementos en orden espiral:\n");
    print_spiral(A, N, M);

    free(block);
    free(A);
    return 0;
}
