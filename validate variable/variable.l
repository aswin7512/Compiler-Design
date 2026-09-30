%{
#include "y.tab.h"
%}

%%

[a-zA-Z][a-zA-Z0-9]*    { return IDENTIFIER; }
\n                      { return NL; }
.                       { return yytext[0]; }

%%

int yywrap(void) {
    return 1;
}