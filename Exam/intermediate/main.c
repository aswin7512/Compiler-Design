#include <stdio.h>
#include <string.h>
#include<ctype.h>


char stack[100];
int top = -1;
int count = 1;

void push(char ch) { stack[++top] = ch; }

char pop() { return stack[top--]; }

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    return 1;
}

void infixToPostfix(char infix[], char postfix[]) {
    int j = 0;

    for (int i = 0; infix[i] != 0; i++) {
        if (isalnum(infix[i]))
            postfix[j++] = infix[i];
        
        else if (infix[i] == '(')
            push(infix[i]);
        
        else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') postfix[j++] = pop();
            pop();
        }

        else {
            while (top != -1 && precedence(infix[i]) < precedence(stack[top])) postfix[j++] = pop();
            push(infix[i]);
        }
    }

    while (top != -1) postfix[j++] = pop();
    postfix[j] = 0;
}

void generateTAC(char postfix[]) {
    char opStack[100][4];
    int opTop = -1;

    for (int i = 0; postfix[i] != 0; i++) {
        char op1[4], op2[4], result[4];

        if (isalnum(postfix[i])) sprintf(opStack[++opTop], "%c", postfix[i]);

        else {
            strcpy(op2, opStack[opTop--]);
            strcpy(op1, opStack[opTop--]);
            sprintf(result, "t%d", count++);
            if (opTop != -1) printf("%s = %s %c %s\n", result, op1, postfix[i], op2);
            else printf("%s %c %s\n", op1, postfix[i], op2);
            sprintf(opStack[++opTop], "%s", result);
        }
    }
}

int main() {
    char infix[100], postfix[100];
    printf("Enter Expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Three Address code for %s\n", infix);
    generateTAC(postfix);
    return 0;
}