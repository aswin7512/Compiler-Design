%{
#include <stdio.h>
#include <stdlib.h>

int line_number = 1;
%}

/* Definitions / Regular Aliases */
DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
INT_CONST   {DIGIT}+
FLOAT_CONST {DIGIT}+\.{DIGIT}+([eE][+-]?{DIGIT}+)?

%%

\n              { line_number++; }
[ \t\r]+        { /* Skip whitespace */ }

"//".*          { /* Ignore single-line comments */ }

"/*"([^*]|\*+[^*/])*\*+"/" { 
    /* Ignore multi-line comments; count internal newlines */
    for (int i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == '\n') line_number++;
    }
}

    /* Keywords - must appear BEFORE the generic identifier pattern */
"int"|"float"|"char"|"double"|"void"|"if"|"else"|"while"|"for"|"return"|"break"|"continue" {
    printf("[Line %d] KEYWORD     : %s\n", line_number, yytext);
}

    /* Literals / Constants */
{FLOAT_CONST}   { printf("[Line %d] FLOAT_CONST : %s\n", line_number, yytext); }
{INT_CONST}     { printf("[Line %d] INT_CONST   : %s\n", line_number, yytext); }
\"([^\\\"]|\\.)*\" { printf("[Line %d] STRING_LIT  : %s\n", line_number, yytext); }

    /* Identifiers */
{ID}            { printf("[Line %d] IDENTIFIER  : %s\n", line_number, yytext); }

    /* Multi-character Operators */
"=="|"!="|"<="|">="|"&&"|"||"|"++"|"--" {
    printf("[Line %d] RELOP/LOGOP : %s\n", line_number, yytext);
}

    /* Single-character Operators and Delimiters */
[+\-*/%=<>]     { printf("[Line %d] OPERATOR    : %s\n", line_number, yytext); }
[;,(){}\[\]]    { printf("[Line %d] DELIMITER   : %s\n", line_number, yytext); }

    /* Catch-all for unrecognized characters */
.               { printf("[Line %d] ERROR (Unknown Token): %s\n", line_number, yytext); }

%%

int yywrap(void) {
    return 1;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Failed to open file");
            return 1;
        }
        yyin = file;
    }
    yylex();
    return 0;
}