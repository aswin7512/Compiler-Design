%{
    #include <stdio.h>
    int yylex();
    void yyerror(const char* s);
%}
%token NUMBER NL
%left '+' '-'
%left '*' '/'

%%

stmt: expr NL   { printf("Result: %d\n", $1); };

expr:   expr '+' token      { $$ = $1 + $3; }|
        expr '-' token      { $$ = $1 - $3; }|
        token;

token:  token '*' factor    { $$ = $1 * $3; }|
        token '/' factor    { $$ = $1 / $3; }|
        factor;

factor: '(' expr ')'        { $$ = $2; }|
        NUMBER              { $$ = $1; };

%%


void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}


int main() {
    printf("Enter Expressioon: ");
    yyparse();
    return 0;
}


/*
S -> E
E -> E+T | E-T | T
T -> T*F | T/F | F
F -> (E) | NUMBER

*/