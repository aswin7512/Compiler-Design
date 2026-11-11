#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR 20
#define MAX_LEN 32

typedef struct {
    char lhs[MAX_LEN];
    char op1[MAX_LEN];
    char op[2];
    char op2[MAX_LEN];
    int is_binary; // 1 if "op1 op op2", 0 if simple assignment "op1"
} Expression;

typedef struct {
    char var[MAX_LEN];
    int val;
} Constant;

Constant const_table[MAX_EXPR];
int const_count = 0;

// Check if a string represents an integer
int is_number(const char *str) {
    if (!str || *str == '\0') return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '-') return 0;
    }
    return 1;
}

// Find constant value of a variable if it exists
int get_constant(const char *var, int *val) {
    for (int i = 0; i < const_count; i++) {
        if (strcmp(const_table[i].var, var) == 0) {
            *val = const_table[i].val;
            return 1;
        }
    }
    return 0;
}

// Add or update a variable's constant value
void set_constant(const char *var, int val) {
    for (int i = 0; i < const_count; i++) {
        if (strcmp(const_table[i].var, var) == 0) {
            const_table[i].val = val;
            return;
        }
    }
    strcpy(const_table[const_count].var, var);
    const_table[const_count].val = val;
    const_count++;
}

// Remove variable from constant table if it gets reassigned to a non-constant
void invalidate_constant(const char *var) {
    for (int i = 0; i < const_count; i++) {
        if (strcmp(const_table[i].var, var) == 0) {
            for (int j = i; j < const_count - 1; j++) {
                const_table[j] = const_table[j + 1];
            }
            const_count--;
            return;
        }
    }
}

int main() {
    int n;
    Expression exprs[MAX_EXPR];
    char line[100];

    printf("Enter no. of Expressions: ");
    if (scanf("%d", &n) != 1) return 1;
    getchar(); // clear newline

    for (int i = 0; i < n; i++) {
        fgets(line, sizeof(line), stdin);
        
        // Parse assignment: LHS = OP1 OP OP2 or LHS = OP1
        char lhs[MAX_LEN], eq[2], op1[MAX_LEN], op[2], op2[MAX_LEN];
        int count = sscanf(line, "%s %s %s %s %s", lhs, eq, op1, op, op2);

        strcpy(exprs[i].lhs, lhs);
        strcpy(exprs[i].op1, op1);
        
        if (count == 5) {
            exprs[i].is_binary = 1;
            strcpy(exprs[i].op, op);
            strcpy(exprs[i].op2, op2);
        } else {
            exprs[i].is_binary = 0;
            exprs[i].op[0] = '\0';
            exprs[i].op2[0] = '\0';
        }
    }

    printf("\nOptimized Expressions:\n");

    for (int i = 0; i < n; i++) {
        int val1, val2;
        int op1_is_const = is_number(exprs[i].op1) || get_constant(exprs[i].op1, &val1);
        int op2_is_const = 0;

        if (is_number(exprs[i].op1)) val1 = atoi(exprs[i].op1);

        // Propagate constants into operands
        if (get_constant(exprs[i].op1, &val1)) {
            sprintf(exprs[i].op1, "%d", val1);
        }

        if (exprs[i].is_binary) {
            op2_is_const = is_number(exprs[i].op2) || get_constant(exprs[i].op2, &val2);
            if (is_number(exprs[i].op2)) val2 = atoi(exprs[i].op2);

            if (get_constant(exprs[i].op2, &val2)) {
                sprintf(exprs[i].op2, "%d", val2);
            }
        }

        // Constant Folding: If operands are constant, compute result directly
        if (op1_is_const && (!exprs[i].is_binary || op2_is_const)) {
            int result = val1;
            if (exprs[i].is_binary) {
                switch (exprs[i].op[0]) {
                    case '+': result = val1 + val2; break;
                    case '-': result = val1 - val2; break;
                    case '*': result = val1 * val2; break;
                    case '/': if (val2 != 0) result = val1 / val2; break;
                }
            }
            set_constant(exprs[i].lhs, result);
            printf("%s = %d\n", exprs[i].lhs, result);
        } else {
            invalidate_constant(exprs[i].lhs);
            if (exprs[i].is_binary) {
                printf("%s = %s %s %s\n", exprs[i].lhs, exprs[i].op1, exprs[i].op, exprs[i].op2);
            } else {
                printf("%s = %s\n", exprs[i].lhs, exprs[i].op1);
            }
        }
    }

    return 0;
}