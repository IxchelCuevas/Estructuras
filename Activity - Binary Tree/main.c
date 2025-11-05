#include <stdio.h>
#include <stdbool.h>

#define CAPACITY 256

// ---- almacenamiento del heap (max-heap) ----
static int heap[CAPACITY];
static int heapSize = 0;

#define LEFT(i)   (2*(i) + 1)
#define RIGHT(i)  (2*(i) + 2)
#define PARENT(i) (((i) - 1) / 2)

static void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

// ---- impresiones básicas ----
static void showHeap(void) {
    printf("heapSize=%d : [", heapSize);
    for (int i = 0; i < heapSize; ++i) {
        if (i) printf(" ");
        printf("%d", heap[i]);
    }
    printf("]\n");
}

// ---- pretty printer (árbol de lado con líneas y corchetes) ----
static void _printIndent(int depth, int branch[]) {
    for (int i = 0; i < depth; ++i)
        printf("%s", branch[i] ? "|   " : "    ");
}

static void _printPretty(const int *A, int n, int idx, int depth, int isLeft, int branch[]) {
    if (idx >= n) return;

    int li = LEFT(idx), ri = RIGHT(idx);
    int hasL = (li < n);

    // Primero subárbol derecho (queda pendiente el izquierdo)
    branch[depth] = hasL ? 1 : 0;
    _printPretty(A, n, ri, depth + 1, 0, branch);
    branch[depth] = 0;

    // Nodo actual
    _printIndent(depth, branch);
    if (depth > 0) printf("%s", isLeft ? "\\-- " : "/-- ");
    printf("[%-3d]\n", A[idx]);

    // Subárbol izquierdo
    _printPretty(A, n, li, depth + 1, 1, branch);
}

static void printHeapPretty(const int *A, int n) {
    if (n <= 0) { puts("(arbol vacio)"); return; }
    int branch[64] = {0}; // suficiente para heaps grandes
    _printPretty(A, n, 0, 0, 0, branch);
}

//núcleo del heap
static void reHeapUp(int i) {
    while (i > 0) {
        int p = PARENT(i);
        if (heap[p] >= heap[i]) break;
        swap(&heap[p], &heap[i]);
        i = p;
    }
}

static void reHeapDown(int i) {
    for (;;) {
        int l = LEFT(i), r = RIGHT(i), largest = i;
        if (l < heapSize && heap[l] > heap[largest]) largest = l;
        if (r < heapSize && heap[r] > heap[largest]) largest = r;
        if (largest == i) break;
        swap(&heap[i], &heap[largest]);
        i = largest;
    }
}

static void insert(int item) {
    if (heapSize >= CAPACITY) {
        puts("heap lleno");
        return;
    }
    heap[heapSize] = item;
    reHeapUp(heapSize);
    heapSize++;
}

static bool removeMax(int *out) {
    if (heapSize == 0) return false;
    *out = heap[0];
    heapSize--;
    if (heapSize > 0) {
        heap[0] = heap[heapSize];
        reHeapDown(0);
    }
    return true;
}

//demo
int main(void) {
    int n, k;

    printf("Indique la cantidad de nodos n: ");
    if (scanf("%d", &n) != 1 || n < 0 || n > CAPACITY) return 0;

    printf("valores:\n");
    for (int i = 0; i < n; ++i) {
        int x; scanf("%d", &x);
        insert(x);
        showHeap();
        printHeapPretty(heap, heapSize);
        puts("-----------------------------");
    }

    printf("indique el número de veces a eliminar el máximo del heap K: ");
    if (scanf("%d", &k) != 1) return 0;
    if (k < 0) k = 0;
    if (k > heapSize) k = heapSize;

    for (int t = 1; t <= k; ++t) {
        int mx;
        if (removeMax(&mx)) {
            printf("remove #%d -> max=%d\n", t, mx);
            showHeap();
            printHeapPretty(heap, heapSize);
            puts("-----------------------------");
        } else {
            puts("heap vacio");
        }
    }

    puts("Final:");
    showHeap();
    printHeapPretty(heap, heapSize);

    return 0;
}
