#include <stdio.h>
#include <stdlib.h>


enum { A_ = 0, B_ = 1, C_ = 2, D_ = 3 };
#define N 4  /* número de vértices: A,B,C,D */

static inline char nameOf(int i) { return (char)('A' + i); }


void buildAdjMatrixUndirected(int M[N][N]) {
    /* Inicializamos toda la matriz en 0 (sin aristas). */
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            M[i][j] = 0;

    /* E = { {A,B}, {A,C}, {B,D} } → pares (no dirigidos)        */
    int edges[][2] = {
        {A_, B_},  /* A—B */
        {A_, C_},  /* A—C */
        {B_, D_}   /* B—D */
    };
    int m = sizeof(edges) / sizeof(edges[0]);

    /* Para cada arista {u,v} marcamos M[u][v] y M[v][u] = 1.     */
    for (int k = 0; k < m; ++k) {
        int u = edges[k][0], v = edges[k][1];
        M[u][v] = 1;
        M[v][u] = 1;  /* simetría por ser no dirigido */
    }
}

/* Imprime la matriz con encabezados A,B,C,D en filas/columnas. */
void printAdjMatrix(int M[N][N]) {
    /* Encabezado de columnas */
    printf("    ");
    for (int j = 0; j < N; ++j) printf("%c ", nameOf(j));
    printf("\n");

    /* Separador visual */
    printf("   ");
    for (int j = 0; j < N; ++j) printf("--");
    printf("-\n");

    /* Filas con etiqueta y valores 0/1 */
    for (int i = 0; i < N; ++i) {
        printf("%c | ", nameOf(i));
        for (int j = 0; j < N; ++j) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}


typedef struct Node {
    int v;              /* índice del vecino (0..3 == A..D) */
    struct Node *next;  /* siguiente vecino en la lista      */
} Node;

/* Crea un nodo para el vecino 'v'. */
static Node* newNode(int v) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->v = v;
    p->next = NULL;
    return p;
}

/* Inserta arista dirigida u -> v: agrega v al inicio de adj[u]. */
void addEdgeDirected(Node* adj[N], int u, int v) {
    Node *p = newNode(v);
    p->next = adj[u];
    adj[u] = p;
}

/* Construye la lista de adyacencia para el grafo dirigido. */
void buildAdjListDirected(Node* adj[N]) {
    /* Inicializamos cada lista como vacía (NULL). */
    for (int i = 0; i < N; ++i) adj[i] = NULL;

    /* Aristas dirigidas: A->B, A->C, B->D. */
    addEdgeDirected(adj, A_, B_);
    addEdgeDirected(adj, A_, C_);
    addEdgeDirected(adj, B_, D_);
}

/* Imprime, para cada vértice u, su lista de vecinos salientes. */
void printAdjList(Node* adj[N]) {
    for (int u = 0; u < N; ++u) {
        printf("%c: ", nameOf(u));
        for (Node *p = adj[u]; p != NULL; p = p->next) {
            printf("%c ", nameOf(p->v));
        }
        printf("\n");
    }
}

/* Libera toda la memoria asociada a las listas. */
void freeAdjList(Node* adj[N]) {
    for (int u = 0; u < N; ++u) {
        Node *p = adj[u];
        while (p) {
            Node *q = p->next;
            free(p);
            p = q;
        }
    }
}

/* ============================================================
   DEMO
   - Construye e imprime la matriz (no dirigido).
   - Construye e imprime la lista (dirigido).
   ============================================================ */
int main(void) {
    /* ----- Matriz de adyacencia (no dirigido) ----- */
    int M[N][N];
    buildAdjMatrixUndirected(M);
    printf("Matriz de adyacencia (no dirigido) con orden A,B,C,D:\n");
    printAdjMatrix(M);
    printf("\n");

    /* ----- Lista de adyacencia (dirigido) ----- */
    Node* adj[N];
    buildAdjListDirected(adj);
    printf("Lista de adyacencia (dirigido):\n");
    printAdjList(adj);

    /* Limpieza de memoria de las listas */
    freeAdjList(adj);
    return 0;
}
