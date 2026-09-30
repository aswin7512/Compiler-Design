%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

extern int yylval;
%}

%%

[0-9]+  { yylval = atoi(yytext); return NUMBER; }
[ \t]   { /* ignore spaces */ }
\n      { return NL; }
.       { return yytext[0]; }

%%

int yywrap(void) {
    return 1;
}