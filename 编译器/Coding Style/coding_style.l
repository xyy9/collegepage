%{
#include<stdio.h>
unsigned int tabCount=0,i=0,w=0;
%}
word    [^{}\n\t]+
left_b  \{
right_b \}
eol     \n
tab     \t
%%
{left_b}    {
            if(w == 1){
                for(i = 0;i<tabCount;i++){
                    printf("\t");
                }
            }
            tabCount++;
            printf("%c",'{');
            w = 0;
            }
{right_b}   {
            tabCount--;
            if(w == 1){
                for(i = 0;i<tabCount;i++){
                    printf("\t");
                }
            }
            printf("%c",'}');
            w = 0;
            }
{eol}       {printf("\n");
            w = 1;
            }
{word}      {
            if(w == 1){
                for(i = 0;i<tabCount;i++){
                    printf("\t");
                }
            }
            for(i = 0;i<yyleng;i++){
                printf("%c",yytext[i]);
            }
            w = 0;
            }
{tab}       {continue;}
%%
int main(int argc, char *argv[]) {
        yylex();
        return(0);
}

