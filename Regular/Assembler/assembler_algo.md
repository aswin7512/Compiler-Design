### Algorithm: Target Code Generator for Three-Address Code

1. **Input:** Read the three-address code string in the form `result = operand1 operator operand2` (e.g., `s=a+b`).


2. **Parse:** Extract the target variable (`res`), the first source operand (`arg1`), the operator (`op`), and the second source operand (`arg2`).
3. **Load:** Emit instruction to load the first operand into register `R0`:
$$\text{MOV R0, } arg1$$



4. **Compute:** Based on the operator `op`, emit the corresponding arithmetic instruction using `R0` and `arg2`:
* If `'+'`: Emit `ADD R0, ` $arg2$

* If `'-'`: Emit `SUB R0, ` $arg2$
* If `'*'`: Emit `MUL R0, ` $arg2$
* If `'/'`: Emit `DIV R0, ` $arg2$


5. **Store:** Emit instruction to store the evaluated result from `R0` back into the target variable:
$$\text{MOV } res\text{, R0}$$



6. **Terminate:** Exit successfully.