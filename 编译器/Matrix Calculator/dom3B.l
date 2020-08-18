%{
#include "y.tab.h"
void yyerror(const char *);
int col = 0;
%}
%%
\n      { return(yytext[0]);}
[0-9]+	{ col+=yyleng;yylval.ival = atoi(yytext);return(INUMBER); }
"+"     { col++;yylval.ival = col;return(ADD);}
"-"     { col++;yylval.ival = col;return(SUB);}
"*"     { col++;yylval.ival = col;return(MUL);}
"^T"    { col+=2;return(TRAN);}
"("     { col++;return(OPEN);}
")"     { col++;return(CLOSE);}
"["     { col++;return(LEFT);}
","     { col++;return(C);}
"]"     { col++;return(RIGHT);}
" "     { col++;}
[ \t]+  { col+=yyleng;}
.       { yyerror("Syntax Error");}
%%

