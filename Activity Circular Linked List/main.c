#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    size_t size;
} CList;

static Node* newNode(int x){
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) return NULL;
    n->data = x;
    n->next = NULL;
    return n;
}

void init(CList *L){ L->head = L->tail = NULL; L->size = 0; }
bool isEmpty(const CList *L){ return L->size == 0; }
size_t sizeC(const CList *L){ return L->size; }

bool getHead(const CList *L, int *out){
    if (isEmpty(L)) return false;
    if (out) *out = L->head->data;
    return true;
}
bool getTail(const CList *L, int *out){
    if (isEmpty(L)) return false;
    if (out) *out = L->tail->data;
    return true;
}

bool addFront(CList *L, int x){
    Node *n = newNode(x);
    if (!n) return false;

    if (isEmpty(L)){
        L->head = L->tail = n;
        n->next = n;                 
    } else {
        n->next = L->head;
        L->head = n;
        L->tail->next = L->head;     
    }
    L->size++;
    return true;
}

bool addEnd(CList *L, int x){
    Node *n = newNode(x);
    if (!n) return false;

    if (isEmpty(L)){
        L->head = L->tail = n;
        n->next = n;
    } else {
        n->next = L->head;
        L->tail->next = n;
        L->tail = n;
    }
    L->size++;
    return true;
}

bool addAt(CList *L, size_t pos, int x){
    if (pos > L->size) return false;        
    if (pos == 0)  return addFront(L, x);
    if (pos == L->size) return addEnd(L, x);

    Node *n = newNode(x);
    if (!n) return false;

    Node *prev = L->head;
    for (size_t i = 0; i < pos - 1; ++i) prev = prev->next;
    n->next = prev->next;
    prev->next = n;
    L->size++;
    return true;
}

bool removeFront(CList *L, int *out){
    if (isEmpty(L)) return false;

    Node *del = L->head;
    if (L->size == 1){
        if (out) *out = del->data;
        L->head = L->tail = NULL;
    } else {
        if (out) *out = del->data;
        L->head = del->next;
        L->tail->next = L->head;
    }
    free(del);
    L->size--;
    return true;
}

bool removeEnd(CList *L, int *out){
    if (isEmpty(L)) return false;

    if (L->size == 1){
        int v = L->head->data;
        free(L->head);
        L->head = L->tail = NULL;
        L->size = 0;
        if (out) *out = v;
        return true;
    }

    Node *prev = L->head;
    while (prev->next != L->tail) prev = prev->next;

    int v = L->tail->data;
    prev->next = L->head;
    free(L->tail);
    L->tail = prev;
    L->size--;
    if (out) *out = v;
    return true;
}

bool removeAt(CList *L, size_t pos, int *out){
    if (pos >= L->size) return false;
    if (pos == 0) return removeFront(L, out);
    if (pos == L->size - 1) return removeEnd(L, out);

    Node *prev = L->head;
    for (size_t i = 0; i < pos - 1; ++i) prev = prev->next;

    Node *del = prev->next;
    prev->next = del->next;
    int v = del->data;
    free(del);
    L->size--;
    if (out) *out = v;
    return true;
}

int searchFirst(const CList *L, int x){
    if (isEmpty(L)) return -1;
    Node *cur = L->head;
    for (size_t i = 0; i < L->size; ++i){
        if (cur->data == x) return (int)i;
        cur = cur->next;
    }
    return -1;
}

void traverse(const CList *L, void (*visit)(int)){
    if (isEmpty(L)) return;
    Node *cur = L->head;
    for (size_t i = 0; i < L->size; ++i){
        visit(cur->data);
        cur = cur->next;
    }
}

static void printItem(int x){ printf("%d ", x); }

void display(const CList *L){
    printf("CLL(size=%zu): ", L->size);
    if (isEmpty(L)){ puts("[empty]"); return; }
    traverse(L, printItem);
    putchar('\n');
}

void clear(CList *L){
    int tmp;
    while (!isEmpty(L)) removeFront(L, &tmp);
}

int main(void){
    CList L; init(&L);

    int op;
    do {
        printf("\nMENU\n"
               " 1) Add front\n"
               " 2) Add end\n"
               " 3) Add at position\n"
               " 4) Remove front\n"
               " 5) Remove end\n"
               " 6) Remove at position\n"
               " 7) Search first\n"
               " 8) Traverse/Display\n"
               " 9) Size\n"
               "10) Is Empty\n"
               "11) Clear\n"
               "12) GetHead\n"
               "13) GetTail\n"
               " 0) Exit\n> ");
        if (scanf("%d", &op) != 1) break;

        if (op == 1){
            int x; printf("value: "); if (scanf("%d",&x)!=1) break;
            puts(addFront(&L,x) ? "ok" : "alloc fail");
        } else if (op == 2){
            int x; printf("value: "); if (scanf("%d",&x)!=1) break;
            puts(addEnd(&L,x) ? "ok" : "alloc fail");
        } else if (op == 3){
            int x; long p;
            printf("pos (0..%zu): ", sizeC(&L)); if (scanf("%ld",&p)!=1) break;
            printf("value: "); if (scanf("%d",&x)!=1) break;
            puts((p>=0 && addAt(&L,(size_t)p,x)) ? "ok" : "range/alloc fail");
        } else if (op == 4){
            int y; puts(removeFront(&L,&y) ? (printf("removed %d\n",y), "ok") : "empty");
        } else if (op == 5){
            int y; puts(removeEnd(&L,&y) ? (printf("removed %d\n",y), "ok") : "empty");
        } else if (op == 6){
            long p; int y;
            printf("pos (0..%zu): ", sizeC(&L)- (sizeC(&L)?1:0)); if (scanf("%ld",&p)!=1) break;
            puts((p>=0 && removeAt(&L,(size_t)p,&y)) ? (printf("removed %d\n",y), "ok") : "empty/range");
        } else if (op == 7){
            int x; printf("value: "); if (scanf("%d",&x)!=1) break;
            int idx = searchFirst(&L,x);
            if (idx == -1) puts("not found"); else printf("found at pos %d\n", idx);
        } else if (op == 8){
            display(&L);
        } else if (op == 9){
            printf("size = %zu\n", sizeC(&L));
        } else if (op == 10){
            printf("%s\n", isEmpty(&L) ? "empty" : "not empty");
        } else if (op == 11){
            clear(&L); puts("cleared");
        } else if (op == 12){
            int v; puts(getHead(&L,&v) ? (printf("head = %d\n",v), "ok") : "empty");
        } else if (op == 13){
            int v; puts(getTail(&L,&v) ? (printf("tail = %d\n",v), "ok") : "empty");
        } else if (op != 0){
            puts("invalid");
        }
    } while (op != 0);

    clear(&L);
    return 0;
}
