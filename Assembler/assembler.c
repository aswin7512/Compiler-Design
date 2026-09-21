#include <stdio.h>
#include <string.h>

int main() {
    char str[50];
    char res, arg1, op, arg2;

    printf("Enter the three address code:\n");
    if (scanf("%s", str) != 1) {
        return 1;
    }

    // Parse the input pattern: "res=arg1<op>arg2" (e.g., "s=a+b")
    if (sscanf(str, "%c=%c%c%c", &res, &arg1, &op, &arg2) == 4) {
        printf("\n");
        printf("MOV R0,%c\n", arg1);

        switch (op) {
            case '+':
                printf("ADD R0,%c\n", arg2);
                break;
            case '-':
                printf("SUB R0,%c\n", arg2);
                break;
            case '*':
                printf("MUL R0,%c\n", arg2);
                break;
            case '/':
                printf("DIV R0,%c\n", arg2);
                break;
            default:
                printf("; Unknown operator\n");
                return 1;
        }

        printf("MOV %c,R0\n", res);
    } else {
        printf("Invalid three address code format.\n");
    }

    return 0;
}