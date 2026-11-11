digit       [0-9]
letter      [a-zA-Z_]
spec        [()\[\]{};]
id          {letter}({letter}|{digit})*
number      {digit}+

%%
"if"|"else"|"for"|"while"|"return"|"int"|"float"|"char"     {printf("%s: Keyword\n", yytext);}
{id}        { printf("%s: Identifier\n", yytext); }
{number}    { printf("%s: Number\n", yytext); }
[+\-*/%<>=] { printf("%s: Operator\n", yytext); }
[()\[\]{};] { printf("%s: Special Symbol\n", yytext); }
[ \n\t\r]   {}
.           { printf("%s: Unknown...\n", yytext); }
%%

int yywrap() {return 1;}

int main() {
    char filename[100];
    printf("Enter filename: ");
    scanf("%99s", filename);
    FILE* fp = fopen(filename, "r");
    yyin = fp;
    yylex();
    fclose(fp);
    return 0;
}