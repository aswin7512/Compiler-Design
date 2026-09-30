## Simple Calculator

### 1. Lex / `calc.l`

1. **Input Reading:** Scan input text character by character.
2. **Token & Value Processing:**
* If a numeric pattern `[0-9]+` is detected, convert string `yytext` to integer value via `atoi()`, assign it to `yylval`, and return token `NUMBER`.
* Skip tab and space characters (`[ \t]`).
* If a newline `\n` is encountered, return token `NL`.
* For operators (`+`, `-`, `*`, `/`, `(`, `)`), return the character directly as its ASCII token code.



### 2. Yacc / `calc.y`

1. **Precedence Setup:** Enforce operator hierarchy (`*`, `/` higher than `+`, `-`) using `%left` declarations to resolve ambiguous parsing actions.
2. **Parsing Phase:**
    * Fetch tokens iteratively via `yylex()`.
    * Construct and evaluate the expression recursively using bottom-up shift-reduce parsing rules:
    * **Addition (`expr '+' expr`):** Compute $E_1 + E_3$, assign to `$$`.
    * **Subtraction (`expr '-' expr`):** Compute $E_1 - E_3$, assign to `$$`.
    * **Multiplication (`expr '*' expr`):** Compute $E_1 \times E_3$, assign to `$$`.
    * **Division (`expr '/' expr`):** Check if divisor $E_3 == 0$. If true, print `"Division by zero error"` and terminate (`exit(1)`); otherwise, compute $E_1 / E_3$, assign to `$$`.
    * **Grouping (`'(' expr ')'`):** Pass inside expression value directly (`$$ = $2`).
    * **Leaf Node (`NUMBER`):** Pass terminal numerical value (`$$ = $1`).
3. **Output & Completion:** Upon encountering `NL` following a valid `expr`, print `"Result = <value>"` and terminate (`exit(0)`).
