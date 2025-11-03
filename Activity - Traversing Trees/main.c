
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* new_node(int x) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) exit(1);
    n->data = x;
    n->left = n->right = NULL;
    return n;
}

/* Preorden: visita -> izquierda -> derecha */
void preorder(Node* r) {
    if (!r) return;
    printf("%d ", r->data);
    preorder(r->left);
    preorder(r->right);
}

/* Inorden: izquierda -> visita -> derecha */
void inorder(Node* r) {
    if (!r) return;
    inorder(r->left);
    printf("%d ", r->data);
    inorder(r->right);
}

/* Postorden: izquierda -> derecha -> visita */
void postorder(Node* r) {
    if (!r) return;
    postorder(r->left);
    postorder(r->right);
    printf("%d ", r->data);
}

/* Liberar memoria en postorden */
void destroy(Node* r) {
    if (!r) return;
    destroy(r->left);
    destroy(r->right);
    free(r);
}

int main(void) {
    // Árbol binario de ejemplo (7 nodos):
    Node* root = new_node(8);
    root->left = new_node(4);
    root->right = new_node(12);
    root->left->left = new_node(2);
    root->left->right = new_node(6);
    root->right->left = new_node(10);
    root->right->right = new_node(14);

    printf("Preorden: ");  preorder(root);  putchar('\n');
    printf("Inorden: ");  inorder(root);   putchar('\n');
    printf("Postorden: ");  postorder(root); putchar('\n');

    destroy(root);
    return 0;
}
