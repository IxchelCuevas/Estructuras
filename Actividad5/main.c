#include <stdio.h>
#include <stdlib.h>

int main(){
    int rows = 3, cols = 4;
    int rows2 = 2, cols2 = 2;

    int memoria_filas = (int)(rows * (int)sizeof(int*));
    int **M = (int**)malloc(rows * sizeof(int*));
    if (!M) { fprintf(stderr, "Error: memoria insuficiente\n"); return 1; }

    int total = 0;

    printf("Memoria de filas = %d\n", (int)(rows * (int)sizeof(int*)));

    for (int i = 0; i < rows; i++) {
        M[i] = (int*)malloc(cols * sizeof(int));
        if (!M[i]) {
            fprintf(stderr, "Error: memoria insuficiente\n");
            for (int k = 0; k < i; ++k) free(M[k]);
            free(M);
            return 1;
        }
        total += (int)(cols * (int)sizeof(int));
    }

    printf("Memoria de columnas = %d\n", total);
    printf("Memoria total solicitada = %d\n\n", total + memoria_filas);

    size_t n = (size_t)rows2 * (size_t)cols2;

    for (int i = 0; i < rows2; i++) {
        M[i] = (int*)malloc(cols2 * sizeof(int));
        if (!M[i]) {
            fprintf(stderr, "Error: memoria insuficiente\n");
            for (int k = 0; k < i; ++k) free(M[k]);
            free(M);
            return 1;
        }
    }

    printf("Introduce %d enteros (por filas):\n", rows2 * cols2);
    for (int i = 0; i < rows2; i++) {
        int *p = M[i];   // puntero al inicio de la fila i
        for (int j = 0; j < cols2; j++, p++) {
            scanf("%d", p);
        }
    }

    printf("\nMatriz ingresada:\n");
    for (int i = 0; i < rows2; i++) {
        for (int *p = M[i]; p < M[i] + cols2; p++) {
            printf("%d ", *p);
        }
        printf("\n");
    }

    for (int i = 0; i < rows2; i++) free(M[i]);
    free(M);

    return 0;
}
