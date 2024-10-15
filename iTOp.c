#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100
char st[MAX];
int top = -1;

void push(char st[], char val);
char pop(char st[]);
void InfixtoPostfix(char source[], char target[]);
int getPriority(char op);

int main() {
    char infix[100], postfix[100];
    
    printf("\nEnter any infix expression: ");
    fgets(infix, sizeof(infix), stdin);

    infix[strcspn(infix, "\n")] = '\0';

    InfixtoPostfix(infix, postfix);
    printf("\nThe corresponding postfix expression is: %s\n", postfix);
    
    return 0;
}

void InfixtoPostfix(char source[], char target[]) {
    int i = 0, j = 0;
    char temp;

    while (source[i] != '\0') {
        if (source[i] == '(') {
            push(st, source[i]);
        } 
        else if (source[i] == ')') {
            while (top != -1 && st[top] != '(') {
                target[j++] = pop(st);
            }
            if (top == -1) {
                printf("\nINCORRECT EXPRESSION\n");
                exit(1);
            }
            pop(st);  
        } 
        else if (isalnum(source[i])) {  
            target[j++] = source[i];
        } 
        else if (strchr("+-*/%", source[i])) {  
            while (top != -1 && st[top] != '(' &&
                   getPriority(st[top]) >= getPriority(source[i])) {
                target[j++] = pop(st);
            }
            push(st, source[i]);
        } 
        else {
            printf("\nINCORRECT ELEMENT IN EXPRESSION\n");
            exit(1);
        }
        i++;
    }

    while (top != -1 && st[top] != '(') {
        target[j++] = pop(st);
    }
    target[j] = '\0';  
}

int getPriority(char op) {
    if (op == '/' || op == '*' || op == '%')
        return 1;
    else if (op == '+' || op == '-')
        return 0;
    else
        return -1;  
}

void push(char st[], char val) {
    if (top == MAX - 1) {
        printf("\nSTACK OVERFLOW\n");
    } else {
        st[++top] = val;
    }
}

char pop(char st[]) {
    if (top == -1) {
        printf("\nSTACK UNDERFLOW\n");
        return '\0';
    } else {
        return st[top--];
    }
}