%{
#include "y.tab.c"
#include <stdio.h>
%}

DIGIT   [0-9]
LETTER  [a-zA-Z_]

%%

[ \t]+                  { /* Ignore whitespace */ }

{DIGIT}+(\.{DIGIT}+)?   { return NUMBER; }

{LETTER}({LETTER}|{DIGIT})* { return ID; }

[+\-*/()\n]             { return yytext[0]; }

.                       { 
    printf("Lexical Error: Unrecognized character '%s'\n", yytext); 
    return yytext[0]; 
}

%%

int yywrap(void) {
    return 1;
}