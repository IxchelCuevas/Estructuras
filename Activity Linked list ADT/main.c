#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static Node *head = NULL;

static Node* createNode(int x){
    Node *n = (Node*)malloc(sizeof(Node));
    if(!n) return NULL;
    n->data = x;
    n->next = NULL;
    return n;
}

void displayNodes(void){
    if(!head){ puts("[empty]"); return; }
    for(Node *cur=head; cur; cur=cur->next) printf("%d ", cur->data);
    putchar('\n');
}

bool insertBegin(int x){
    Node *n = createNode(x);
    if(!n) return false;
    n->next = head;
    head = n;
    return true;
}

bool insertEnd(int x){
    Node *n = createNode(x);
    if(!n) return false;

    if(!head){ head = n; return true; }
    Node *cur = head;
    while(cur->next) cur = cur->next;
    cur->next = n;
    return true;
}

bool insertAt(size_t pos, int x){
    if(pos == 0) return insertBegin(x);

    Node *prev = head;
    for(size_t i=0; i<pos-1 && prev; ++i) prev = prev->next;
    if(!prev) return false;                 

    Node *n = createNode(x);
    if(!n) return false;
    n->next = prev->next;                   
    prev->next = n;
    return true;
}

bool deleteBegin(int *out){
    if(!head) return false;
    Node *del = head;
    if(out) *out = del->data;
    head = del->next;
    free(del);
    return true;
}

bool deleteEnd(int *out){
    if(!head) return false;

    if(!head->next){                         
        if(out) *out = head->data;
        free(head);
        head = NULL;
        return true;
    }
    Node *prev = head;
    while(prev->next->next) prev = prev->next; 
    Node *del = prev->next;
    if(out) *out = del->data;
    prev->next = NULL;
    free(del);
    return true;
}

bool deleteAt(size_t pos, int *out){
    if(pos == 0) return deleteBegin(out);

    Node *prev = head;
    for(size_t i=0; i<pos-1 && prev; ++i) prev = prev->next;
    if(!prev || !prev->next) return false;   
    Node *del = prev->next;
    if(out) *out = del->data;
    prev->next = del->next;
    free(del);
    return true;
}

int main(void){
    int op;
    do{
        printf("\nMENU\n"
               "1) Display\n"
               "2) Insert begin\n"
               "3) Insert end\n"
               "4) Insert at position\n"
               "5) Delete begin\n"
               "6) Delete end\n"
               "7) Delete at position\n"
               "0) Exit\n> ");
        if (scanf("%d",&op)!=1) break;

        if(op==1){
            displayNodes();

        }else if(op==2){
            int x; printf("value: "); if (scanf("%d",&x)!=1) break;
            puts(insertBegin(x) ? "ok" : "alloc fail");
            displayNodes();

        }else if(op==3){
            int x; printf("value: "); if (scanf("%d",&x)!=1) break;
            puts(insertEnd(x) ? "ok" : "alloc fail");
            displayNodes();

        }else if(op==4){
            long p; int x;
            printf("pos (0..len): "); if (scanf("%ld",&p)!=1) break;
            printf("value: "); if (scanf("%d",&x)!=1) break;
            puts((p>=0 && insertAt((size_t)p,x)) ? "ok" : "range/alloc fail");
            displayNodes();

        }else if(op==5){
            int y; puts(deleteBegin(&y) ? (printf("deleted %d\n",y), "ok") : "empty");
            displayNodes();

        }else if(op==6){
            int y; puts(deleteEnd(&y) ? (printf("deleted %d\n",y), "ok") : "empty");
            displayNodes();

        }else if(op==7){
            long p; int y;
            printf("pos (0..len-1): "); if (scanf("%ld",&p)!=1) break;
            puts((p>=0 && deleteAt((size_t)p,&y)) ? (printf("deleted %d\n",y), "ok")
                                                   : "empty/range");
            displayNodes();

        }else if(op!=0){
            puts("invalid");
        }
    }while(op!=0);

    while(head) deleteBegin(NULL);
    return 0;
}
