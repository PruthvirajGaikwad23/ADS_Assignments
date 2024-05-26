#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100
char infix[MAX], prefix[MAX];

char stack[MAX];
int top = -1;

void push(char x) {
    if (top == MAX - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack[++top] = x;
}

char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

int priority(char x) {
    if (x == '(')
        return 0;
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    if (x == '^')
        return 3;
    return 0;
}

void reverse(char *exp) {
    int n = strlen(exp);
    for (int i = 0; i < n / 2; i++) {
        char temp = exp[i];
        exp[i] = exp[n - i - 1];
        exp[n - i - 1] = temp;
    }
}

void infixToPrefix(char infix[], char prefix[]) {
    reverse(infix);
    int i = 0, k = 0;
    char x;
    while (infix[i] != '\0') {
        if (isalnum(infix[i])) {
            prefix[k++] = infix[i];
        } else if (infix[i] == ')') {
            push(infix[i]);
        } else if (infix[i] == '(') {
            while ((x = pop()) != ')') {
                prefix[k++] = x;
            }
        } else {
            while (top != -1 && priority(stack[top]) > priority(infix[i])) {
                prefix[k++] = pop();
            }
            push(infix[i]);
        }
        i++;
    }
    while (top != -1) {
        prefix[k++] = pop();
    }
    prefix[k] = '\0';
    reverse(prefix);
}

int main() 
{
    printf("Enter the infix expression: ");
    scanf("%s", infix);
    infixToPrefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);
    return 0;
}
