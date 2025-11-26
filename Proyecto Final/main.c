#include <stdio.h>
#include <stdlib.h>

void abrirHTML(const char *ruta) {
    char comando[512];

#if defined(_WIN32) || defined(_WIN64)
    /* Windows */
    snprintf(comando, sizeof(comando), "start %s", ruta);
    system(comando);

#elif defined(__APPLE__)
    /* macOS */
    snprintf(comando, sizeof(comando), "open %s", ruta);
    system(comando);

#else
    /* Linux / Codespaces: aqui NO usamos xdg-open para evitar el error */
    printf("\n[INFO] Abre este archivo HTML manualmente: %s\n", ruta);
    printf("[INFO] En Codespaces puedes hacer clic en el archivo en el panel izquierdo.\n");
    /* NO llamamos system() aqui para que no truene */
#endif
}


void mostrarMenu(void) {
    printf("=== Sistema de Estructuras de Datos ===\n");
    printf("1) Array\n");
    printf("2) Pila\n");
    printf("0) Salir\n");
    printf("Elige una opcion: ");
}

int main(void) {
    int opcion;

    do {
        mostrarMenu();

        if (scanf("%d", &opcion) != 1) {
            /* Limpiar basura del buffer si el usuario escribe letras */
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            printf("Entrada invalida.\n\n");
            continue;
        }

        switch (opcion) {
        case 1:
            /* array.html debe estar en la MISMA carpeta que main.c */
            abrirHTML("array.html");
            break;
        case 2:
            /* pila.html igual en la misma carpeta */
            abrirHTML("pila.html");
            break;
        case 0:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion invalida.\n");
        }

        printf("\n");

    } while (opcion != 0);

    return 0;
}

