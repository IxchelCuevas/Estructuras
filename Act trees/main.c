#include <stdio.h>

#define MAX_ORIGINAL 10   // Figura 1: 10 elementos (indices 0..9)
#define MAX_FULL     15   // Arbol lleno a la misma altura (niveles 0..3)

#define LEFT(i)   (2*(i) + 1)   // left child index
#define RIGHT(i)  (2*(i) + 2)   // right child index
#define PARENT(i) (((i) - 1) / 2)

static void print_array(const char *a, int n) {
    for (int i = 0; i < n; ++i) {
        char v = a[i] ? a[i] : '.';
        printf("[%2d] %c\n", i, v);
    }
}

/* (a) Build the tree from Figure 1 using arrays
*/
void build_figure1(char nodes[MAX_ORIGINAL]) {
    for (int i = 0; i < MAX_ORIGINAL; ++i) nodes[i] = 0;  // empty

    nodes[0] = 'G';
    nodes[1] = 'D'; nodes[2] = 'I';
    nodes[3] = 'B'; nodes[4] = 'F'; nodes[5] = 'H'; nodes[6] = 'J';
    nodes[7] = 'A'; nodes[8] = 'C'; nodes[9] = 'E';
}

/* (b) Add the necessary nodes to make it a FULL binary tree.
*/
void make_full_from_figure1(const char fig1[MAX_ORIGINAL], char full[MAX_FULL]) {
    for (int i = 0; i < MAX_FULL; ++i) full[i] = 0;      // empty
    // copy the original 10 nodes
    for (int i = 0; i < MAX_ORIGINAL; ++i) full[i] = fig1[i];

    // add the missing nodes to become a full binary tree (depth 3)
    full[10] = 'K';                 // RIGHT child of F (idx 4)
    full[11] = 'L'; full[12] = 'M'; // children of H (idx 5)
    full[13] = 'N'; full[14] = 'O'; // children of J (idx 6)
}

int main(void) {
    // (a) Represent the given tree
    char fig1[MAX_ORIGINAL];
    build_figure1(fig1);
    puts("Figure 1 (array):");
    print_array(fig1, MAX_ORIGINAL);

    // (b) Make it a full binary tree
    char full[MAX_FULL];
    make_full_from_figure1(fig1, full);
    puts("\nFull binary tree (array):");
    print_array(full, MAX_FULL);

    return 0;
}
