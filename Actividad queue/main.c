#include <stdio.h>

#define QUEUESIZE 5

int queue[QUEUESIZE];
int front = 0;
int rear = 0;
int numCurrentElements = 0;

void enqueue(int val){
    queue[rear] = val;           
    numCurrentElements++;        
    rear++;
    if(rear == QUEUESIZE) rear = 0;
}

int dequeue(){
    int val = queue[front];
    numCurrentElements--;
    front++;
    if(front == QUEUESIZE) front = 0;
    return val;
}

void printQueue(){
    int i;
    printf("\nQueue:");
    if(numCurrentElements == 0){
        printf(" [empty]\n");
        return;
    }

    if(rear <= front){
        for(i = front; i < QUEUESIZE; i++) printf(" %d", queue[i]);
        for(i = 0; i < rear; i++)           printf(" %d", queue[i]);
    }else{
        for(i = front; i < rear; i++)       printf(" %d", queue[i]);
    }
    printf("\n");
}

int main(void){
    int option, x;

    while(1){
        printf("\n--- MENU ---\n");
        printf("1 = Enqueue\n");
        printf("2 = Dequeue\n");
        printf("0 = Salir\n");
        printf("Elige una opcion: ");
        
        if(scanf("%d", &option) != 1) return 0;

        if(option == 1){
            if(numCurrentElements == QUEUESIZE){
                printf("Cola llena. No se puede encolar.\n");
            }else{
                printf("Ingresa un entero: ");
                if(scanf("%d", &x) == 1){
                    enqueue(x);
                }
            }
            printQueue();
        }
        else if(option == 2){
            if(numCurrentElements == 0){
                printf("Cola vacia. No se puede desencolar.\n");
            }else{
                int y = dequeue();
                printf("Elemento desencolado: %d\n", y);
            }
            printQueue();
        }
        else if(option == 0){
            printf("Saliendo...\n");
            break;
        }
        else{
            printf("Opcion invalida.\n");
        }
    }

    return 0;
}
