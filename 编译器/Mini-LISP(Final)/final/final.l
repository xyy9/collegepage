%{
#include "y.tab.h"
void yyerror(const char *);
%}
%%
"print-num"                 { return(printnum); }
"print-bool"                { return(printbool); }
"mod"                       { return(mod); }
"and"                       { return(and); }
"or"                        { return(or); }
"not"                       { return(not); }
"#t"                        { yylval.ival = 1;return(boolval); }
"#f"                        { yylval.ival = 0;return(boolval); }
"if"                        { return(IF); }
"define"                    { return(DEFINE); }
[\n\t\r ]+                  { ; }
"("|")"|"+"|"-"|"*"|"/"|">"|"<"|"="     { return(yytext[0]);}
0|[1-9][0-9]*|-[1-9][0-9]*  { yylval.ival = atoi(yytext);return(number); }
[a-z]([a-z]|[0-9]|'-')*     { yylval.sval = strdup(yytext);return(id);}
.                           { yyerror("syntax error");}
%%