#include <stdio.h>
#include <stdlib.h>

float totalSale(float sales[], int n);
float maxSale(float sales[], int n);

int main(void) {
    const char *fname = "sales.txt";
    FILE *fp = fopen(fname, "r");
    if (!fp) {
        fprintf(stderr, "Error: no se puede abrir %s\n", fname);
        return 1;
    }

    int tamaño = 0;
    float tmp;
    while (fscanf(fp, "%f", &tmp) == 1) {
        tamaño++;
    }

    if (tamaño == 0) {
        fprintf(stderr, "Error: %s no contiene números válidos \n", fname);
        fclose(fp);
        return 1;
    }

    float *sales = (float *)malloc(tamaño * sizeof(float));
    if (!sales) {
        fprintf(stderr, "Error: memoria insuficiente para %d elementos.\n", tamaño);
        fclose(fp);
        return 1;
    }

    rewind(fp);
    for (int i = 0; i < tamaño; i++) {
        if (fscanf(fp, "%f", &sales[i]) != 1) {
            fprintf(stderr, "Error de lectura en la línea %d.\n", i + 1);
            free(sales);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp); 

    float total = totalSale(sales, tamaño);
    float maximo = maxSale(sales, tamaño);

    printf("Elementos leídos: %d\n", tamaño);
    printf("Total de ventas: %.2f\n", total);
    printf("Venta máxima:    %.2f\n", maximo);

    free(sales);
    return 0;
}

float totalSale(float sales[], int n) {
    float s = 0.0f;
    for (int i = 0; i < n; i++) s += sales[i];
    return s;
}

float maxSale(float sales[], int n) {
    float m = sales[0];
    for (int i = 1; i < n; i++) if (sales[i] > m) m = sales[i];
    return m;
}
