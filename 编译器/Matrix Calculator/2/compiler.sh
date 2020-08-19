bison -d -o y.tab.c B3B.y
gcc -c -g -I.. y.tab.c
flex -o lex.yy.c B3B.l
gcc -c -g -I.. lex.yy.c
gcc -o B3B y.tab.o lex.yy.o -ll
