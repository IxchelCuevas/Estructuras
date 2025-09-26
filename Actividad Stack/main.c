#include <stdio.h>

#define MAX 1000

int isEmpty(int top) { 
    return top == -1; 
}

int isFull(int top, int cap) { 
    return top == cap - 1; 
}

int match(char a, char c) {
    return (a == '(' && c == ')') || 
           (a == '[' && c == ']') || 
           (a == '{' && c == '}');
}

int main(void) {
    static char s[MAX];
    
    while (fgets(s, sizeof(s), stdin)) {
        static char stc[MAX];   // pila de caracteres
        static int  sti[MAX];   // pila de índices
        int top = -1;
        int error = 0;

        for (int i = 0; s[i] && s[i] != '\n'; ++i) {
            char c = s[i];
            
            if (c == '(' || c == '[' || c == '{') {
                if (isFull(top, MAX)) { 
                    printf("ERROR %d\n", i); 
                    error = 1; 
                    break;
                }
                stc[++top] = c;
                sti[top] = i;
            } 
            else if (c == ')' || c == ']' || c == '}') {
                if (isEmpty(top)) { 
                    printf("ERROR %d\n", i); 
                    error = 1; 
                    break;
                }
                if (!match(stc[top], c)) { 
                    printf("ERROR %d\n", i); 
                    error = 1; 
                    break;
                }
                --top;
            }
    
        }

        if (!error) {
            if (isEmpty(top)) {
                printf("OK\n");
            } else {
                printf("ERROR %d\n", sti[0]); // primer abridor sin cerrar
            }
        }
    }
    return 0;
}
