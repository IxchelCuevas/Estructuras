/* main.c */
#include <stdio.h>

int main(void) {
    int opcion;

    do {
        printf("\n==== Menu de estructuras de datos ====\n");
        printf("1. Arrays\n");
        printf("2. Listas ligadas\n");
        printf("3. Pilas (Stacks)\n");
        printf("4. Colas (Queues)\n");
        printf("5. Arboles binarios / BST\n");
        printf("6. Heaps / Colas de prioridad\n");
        printf("7. Grafos (Graphs)\n");
        printf("8. Tries (Arboles de prefijos)\n");
        printf("9. Tablas hash (Hash tables)\n");
        printf("0. Salir\n");
        printf("Elige una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            // Si hay error de entrada, salimos
            printf("Entrada no valida.\n");
            return 1;
        }

        printf("\n");

        switch (opcion) {
        case 1:
            printf("Elegiste: Arrays\n");
            printf("Link: https://drive.google.com/file/d/1i6UKD3OikOFvk7AgiSaUVfABMfpj-SmU/view?usp=drivesdk \n");
            break;
        case 2:
            printf("Elegiste: Listas ligadas\n");
            printf("Link: https://drive.google.com/file/d/1YED1mVKzRSxmhBo_NMG99BGuprSmUCWt/view?usp=drivesdk \n");
            break;
        case 3:
            printf("Elegiste: Pilas (Stacks)\n");
            printf("Link: https://drive.google.com/file/d/1qw0yR8ehH8TIp3AALFoLMP2biUim94NB/view?usp=drivesdk \n");
            break;
        case 4:
            printf("Elegiste: Colas (Queues)\n");
            printf("Link: https://drive.google.com/file/d/1HrD9dsNTiL82PKQG73vG01xThDyf4TA_/view?usp=drivesdkl\n");
            break;
        case 5:
            printf("Elegiste: Arboles binarios / BST\n");
            printf("Link: https://drive.google.com/file/d/1I2XDXldaX0AsswyWoyicGl1UhoOcYqdr/view\n");
            break;
        case 6:
            printf("Elegiste: Heaps / Colas de prioridad\n");
            printf("Link: https://drive.google.com/file/d/1PIPk0zbugAdzc3H0JsuU4X6cLU7zxlyR/view\n");
            break;
        case 7:
            printf("Elegiste: Grafos (Graphs)\n");
            printf("Link: https://drive.google.com/file/d/1Mj8p0ecXyR-map9CeUnwY-IoUfQWkBXr/view\n");
            break;
        case 8:
            printf("Elegiste: Tries (Arboles de prefijos)\n");
            printf("Link: https://drive.google.com/file/d/1iUCwKOKvuZ5j-3fNmwONaDW2sada5CaD/view?usp=drivesdk \n");
            break;
        case 9:
            printf("Elegiste: Tablas hash (Hash tables)\n");
            printf("Link: https://drive.google.com/file/d/17vch7w5Ukh_pRkRK1oW4uoKAm_3jwSKl/view?usp=drivesdk \n");
            break;
        case 0:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opcion no valida.\n");
            break;
        }

    } while (opcion != 0);

    return 0;
}
