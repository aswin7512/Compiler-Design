#include <stdio.h>

int main() {
    char res, arg1, op, arg2;
    printf("Enter Three Address code: ");
    scanf("%s = %s %s %s", &res, &arg1, &op, &arg2);

    switch (op) {
        case '+':   printf("MOV R0,%c\n", arg1);
                    printf("ADD R0,%c\n", arg2);
                    printf("MOV %c,R0\n", res);
                    break;
        
        case '-':   printf("MOV R0,%c\n", arg1);
                    printf("SUB R0,%c\n", arg2);
                    printf("MOV %c,R0\n", res);
                    break;

        case '*':   printf("MOV R0,%c\n", arg1);
                    printf("MUL R0,%c\n", arg2);
                    printf("MOV %c,R0\n", res);
                    break;

        case '/':   printf("MOV R0,%c\n", arg1);
                    printf("DIV R0,%c\n", arg2);
                    printf("MOV %c,R0\n", res);
                    break;
        
        default:    printf("; Invalid Operator!!!\n");
                    return 1;
    }
    return 0;
}