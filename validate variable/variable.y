%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token IDENTIFIER NL

%%

stmt:
    IDENTIFIER NL { printf("Valid Variable\n"); exit(0); }
    ;

%%

void yyerror(const char *s) {
    printf("Invalid Variable\n");
    exit(0);
}

int main(void) {
    printf("Enter a variable name: ");
    yyparse();
    return 0;
}