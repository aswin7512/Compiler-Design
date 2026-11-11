#include <stdio.h>
#include<stdlib.h>
#include<ctype.h>


char input[100];
int i = 0;
void expression();


void skipSpaces() { while (isspace(input[i])) i++; }


void factor() {
    skipSpaces();
    if (isalpha(input[i]))
        while (isalnum(input[++i]));
    
    else if (isdigit(input[i]))
        while (isdigit(input[++i]));
    
    else if (input[i] == '(') {
        i++;
        expression();
        skipSpaces();
        if (input[i] == ')') i++;
        else {
            printf("Invalid Expression!!!\n"); 
            exit(1);
        }
    }

    else {
            printf("Invalid Expression!!!\n"); 
        exit(1);
    }
}


void term() {
    factor();
    skipSpaces();

    while (input[i] == '*' || input[i] == '/') {
        i++;
        factor();
        skipSpaces();
    }
}


void expression() {
    term();
    skipSpaces();

    while (input[i] == '+' || input[i] == '-') {
        i++;
        term();
        skipSpaces();
    }
}


int main() {
    printf("Enter your Expression: ");
    fgets(input, sizeof(input), stdin);
    
    expression();
    skipSpaces();

    if (input[i] == 0) printf("Valid Expression\n");
    else printf("Invalid Expression!!!\n");
    return 0;
}