%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
int valid = 1;
%}

%token NUMBER ID
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

/* Grammar accepts one or more expressions separated by newlines */
input:
      /* empty */
    | input line
    ;

line:
      '\n'
    | expr '\n' {
        if (valid) {
            printf("Valid arithmetic expression\n\n");
        }
        valid = 1;
      }
    | error '\n' {
        yyerrok;
        valid = 1;
      }
    ;

expr:
      expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '(' expr ')'
    | NUMBER
    | ID
    ;

%%

void yyerror(const char *s) {
    valid = 0;
    printf("Invalid arithmetic expression\n\n");
}

int main(void) {
    printf("Enter arithmetic expressions (Press Ctrl+D to exit):\n");
    yyparse();
    return 0;
}