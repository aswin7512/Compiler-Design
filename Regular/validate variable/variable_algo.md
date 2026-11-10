##  Validate Variable

### 1. Lex / `variable.l`

1. **Input Reading:** Read characters sequentially from the standard input stream (`stdin`).
2. **Token Recognition:**
* If the sequence matches `[a-zA-Z][a-zA-Z0-9]*` (starts with a letter, followed by zero or more alphanumeric characters), return token `IDENTIFIER`.
* If the character is a newline `\n`, return token `NL`.
* For any other unexpected character, return the literal character byte (`yytext[0]`).



### 2. Yacc / `variable.y`

1. **Initialization:** Call `yyparse()` inside `main()`.
2. **Parsing Phase:**
* Request the next token from `yylex()`.
* Match the incoming tokens against the grammar rule `stmt: IDENTIFIER NL`.


3. **Execution & Evaluation:**
* **If Match Succeeds:** Print `"Valid Variable"` and invoke `exit(0)`.
* **If Match Fails (Syntax Error / Invalid Token):** Control shifts to `yyerror()`, printing `"Invalid Variable"` before calling `exit(0)`.