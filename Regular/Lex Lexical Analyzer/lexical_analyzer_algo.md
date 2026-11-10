### Lexical Analyzer (Lex)

1. **Initialize:** Set `line_number = 1` and point `yyin` to the input source.
2. **Scan:** Read the character stream and match the longest token prefix against defined regex patterns.
3. **Filter:** Discard whitespace and comments (`//...` and `/*...*/`), incrementing `line_number` on every encountered `\n`.
4. **Tokenize:**
    * If a reserved keyword, emit `KEYWORD`.
    * If numeric digits, emit `INT_CONST` or `FLOAT_CONST`.
    * If enclosed in double quotes, emit `STRING_LIT`.
    * If a valid identifier pattern, emit `IDENTIFIER`.
    * If an operator or punctuation mark, emit `OPERATOR` or `DELIMITER`.
    * If unmatched, print a lexical error.
    
5. **Terminate:** Repeat steps 2–4 until End-of-File (EOF); return 0 via `yywrap()`.
