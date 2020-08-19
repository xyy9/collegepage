%{
#include "y.tab.h"
%}
%%
\n  {return(yytext[0]);}
[ \t]+	{ /* do nothing */ }
[0-9]+	{ yylval.ival = atoi(yytext);return(INUMBER); }
"add"   {return(ADD);}
"sub"   {return(SUB);}
"mul"   {return(MUL);}
"mod"   {return(MOD);}
"inc"   {return(INC);}
"dec"   {return(DEC);}
"load"  {return(LOAD);}
%%
