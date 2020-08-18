//final project for compiler class.

//The language features are included in "Compiler Final Project" and "MiniLisp".

//Use the following command to compile:
./final.sh

//To run with test data:
./final < 01_1.lsp 

//final.sh:
bison -d -o y.tab.c final.y
gcc -c -g -I.. y.tab.c
flex -o lex.yy.c final.l
gcc -c -g -I.. lex.yy.c
gcc -o final y.tab.o lex.yy.o -ll