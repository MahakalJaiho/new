#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack to store the intermediate infix expressions
typedef struct {
    char* arr[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, char* value) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->arr[++(s->top)] = value;
}

char* pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return NULL;
    }
    return s->arr[(s->top)--];
}

// Function to check if the character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Function to convert prefix to infix
void prefixToInfix(char* prefix) {
    Stack s;
    initStack(&s);

    int length = strlen(prefix);

    // Traverse the prefix expression from right to left
    for (int i = length - 1; i >= 0; i--) {
        // If the character is an operand (i.e., a letter or digit)
        if (isalnum(prefix[i])) {
            // Convert character to string and push to stack
            char* operand = (char*)malloc(2 * sizeof(char));
            operand[0] = prefix[i];
            operand[1] = '\0';
            push(&s, operand);
        } 
        // If the character is an operator
        else if (isOperator(prefix[i])) {
            // Pop two operands from the stack
            char* operand1 = pop(&s);
            char* operand2 = pop(&s);

            // Create a new string for the infix expression
            char* infix = (char*)malloc(strlen(operand1) + strlen(operand2) + 4); // extra space for operator and parentheses
            sprintf(infix, "(%s %c %s)", operand1, prefix[i], operand2);

            // Push the resulting infix expression back to the stack
            push(&s, infix);

            // Free the temporary strings
            free(operand1);
            free(operand2);
        }
    }

    // The final result will be the only element left in the stack
    printf("Infix Expression: %s\n", pop(&s));
}

int main() {
    char prefix[MAX];

    // Input prefix expression
    printf("Enter a prefix expression: ");
    scanf("%s", prefix);

    // Convert prefix to infix
    prefixToInfix(prefix);

    return 0;
}