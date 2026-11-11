%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex(void);
    void yyerror(const char* s);
%}

%token ID NL

%%

stmt: ID NL     { printf("Valid\n"); exit(0); };

%%

void yyerror(const char* s) {
    printf("Invalid!!!\n");
    exit(0);
}

int main() {
    printf("Enter an identifier: ");
    yyparse();
    return 0;
}