# pl0-compiler
A pl/0 to C compiler written in C


TBD list:
1. lexer that parses tokens
2. parser that parses the order of the tokens
3. code generator that'll generate result c code 

More macro:
1. How to print line number and offset in line?
2. print_error - improve to enable string formatting
3. struct token? That has line no, offset in line, 
4. read_char function that reads a char, increments row if new row detected, increments row index when reading each char - basically just handling the offsetting of things alongside reading the char for functionality.

Also TBD for styling:
1. Divide to files for each component and write makefile, create a binary out of multiple files