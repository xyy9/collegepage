bison -d -o y.tab.c final.y
gcc -c -g -I.. y.tab.c
flex -o lex.yy.c final.l
gcc -c -g -I.. lex.yy.c
gcc -o final y.tab.o lex.yy.o -ll
