### Arithmetic Expression Validator (Lex & YACC)

#### Part A: Lexer (`yylex`)

1. **Filter:** Ignore spaces and tabs.
2. **Classify:**
    * Digits $\to$ return `NUMBER`.
    * Letters/alphanumerics $\to$ return `ID`.
    * Characters in `{+, -, *, /, (, ), \n}` $\to$ return their ASCII character code.
    * Any other character $\to$ flag error and return the character.



#### Part B: Parser (`yyparse`)

1. **Initialize:** Set operator precedence (`*`, `/` over `+`, `-`, all left-associative) and set `valid = 1`.
2. **Shift/Reduce:** Read tokens from `yylex()` into the LALR(1) stack:
    * Shift terminals (`NUMBER`, `ID`, operators, parentheses).
    * Reduce valid sub-expressions using $E \to E + E \mid E - E \mid E * E \mid E / E \mid (E) \mid \text{NUMBER} \mid \text{ID}$.
    * Resolve operator conflicts using the declared precedence table.


3. **Evaluate:**
    * On `\n`, if the stack successfully reduces to a single expression without parse errors, print `"Valid arithmetic expression"`.
    * If a grammar mismatch occurs, execute `yyerror()`: set `valid = 0`, print `"Invalid arithmetic expression"`, and discard tokens until the next newline (`error '\n'`).


4. **Repeat:** Reset `valid = 1` and continue parsing until EOF.