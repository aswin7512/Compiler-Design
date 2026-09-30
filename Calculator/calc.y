%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER NL

%left '+' '-'
%left '*' '/'

%%

stmt:
    expr NL { printf("Result = %d\n", $1); exit(0); }
    ;

expr:
    expr '+' expr   { $$ = $1 + $3; }
  | expr '-' expr   { $$ = $1 - $3; }
  | expr '*' expr   { $$ = $1 * $3; }
  | expr '/' expr   { 
                        if ($3 == 0) {
                            printf("Division by zero error\n");
                            exit(1);
                        }
                        $$ = $1 / $3; 
                    }
  | '(' expr ')'    { $$ = $2; }
  | NUMBER          { $$ = $1; }
  ;

%%

void yyerror(const char *s) {
    printf("Invalid Expression\n");
    exit(1);
}

int main(void) {
    printf("Enter expression: ");
    yyparse();
    return 0;
}