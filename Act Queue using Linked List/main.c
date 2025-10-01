#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *front = NULL;  /* cabeza: de aquí sale (dequeue) */
Node *rear  = NULL;  /* cola: aquí se inserta (enqueue)   */

void showQueueList(void) {
    Node *aux = front;                      /* usar aux para recorrer */
    if (!aux) { puts("[empty]"); return; }
    while (aux != NULL) {
        printf("%d ", aux->data);
        aux = aux->next;
    }
    putchar('\n');
}

void enqueue(int x) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { puts("alloc failed"); return; }
    n->data = x;
    n->next = NULL;

    if (front == NULL) {                    
        front = rear = n;
    } else {                                
        rear->next = n;
        rear = n;
    }
}

int dequeue(void) {
    if (front == NULL) {                    
        puts("queue empty");
        return 0;                           
    }
    Node *aux = front;
    int d = front->data;
    front = front->next;                    /* avanzar front */
    if (front == NULL) rear = NULL;         /* si quedó vacía, rear=NULL */
    free(aux);                              /* liberar nodo */
    return d;
}

int main(void) {
    int op;
    do {
        printf("\n1) enqueue  2) dequeue  3) show  0) exit\n> ");
        if (scanf("%d", &op) != 1) return 0;

        if (op == 1) {
            int x; printf("value: ");
            if (scanf("%d", &x) != 1) return 0;
            enqueue(x);
        } else if (op == 2) {
            int y = dequeue();
            if (front != NULL || rear != NULL) printf("dequeued: %d\n", y);
        } else if (op == 3) {
            showQueueList();
        } else if (op != 0) {
            puts("invalid");
        }
    } while (op != 0);

    return 0;
}
