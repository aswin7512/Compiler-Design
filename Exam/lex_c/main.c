#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

bool isKeyword(char token[]) {
    char keywords[][10] = {
        "int",  "float",    "char"
        "if",   "else",     "return"
    };
    int n = 6;

    for (int i = 0; i < n; i++) if (!strcmp(keywords[i], token)) return true;
    return false;
}

int main() {
    char filepath[200], ch;
    printf("Enter filename to read: ");
    scanf("%199s", filepath);
    
    FILE* fp = fopen(filepath, "r");

    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch)) continue;

        if (isalpha(ch) || ch == '_') {
            char token[100];

            int i = 0;
            do {
                token[i++] = ch;
                ch = fgetc(fp);
            } while (isalnum(ch) || ch == '_');
            token[i] = 0;

            if (isKeyword(token)) printf("%s: Keyword\n", token);
            else printf("%s: Identifier\n");

            if (ch!= EOF) ungetc(ch, fp);
        }

        else if (isdigit(ch)) {
            char token[100];

            int i = 0;
            do {
                token[i++] = ch;
                ch = fgetc(fp);
            } while (isdigit(ch));
            token[i] = 0;
            printf("%s: Number\n", token);

            if (ch != EOF) ungetc(ch, fp);
        }

        else if (strchr("+-*/%<>!=", ch)) printf("%c: Operator\n", ch);
        else if (strchr("()[]{}&;", ch)) printf("%c: Special Symbol\n", ch);
        else printf("%c: Unknown\n", ch);
    }

    return 0;
}