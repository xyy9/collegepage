%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *message);
%}
%code requires {
typedef struct {
        int row;
        int col;
} size_matrix;
}
%union {
int ival;
size_matrix sm;
}
%token <ival> INUMBER
%token OPEN
%token CLOSE
%token LEFT
%token C
%token RIGHT
%type <sm> expr
%type <sm> matrix
%left <ival> ADD
%left <ival> SUB
%left <ival> MUL
%right TRAN
%%
program : expr '\n'     {printf("Accepted\n");exit(0);}
        ;
expr    : expr TRAN     {$$.col = $1.row; $$.row = $1.col;}
        | expr ADD expr {if($1.row == $3.row && $1.col == $3.col){
                                $$ = $1;
                         }
                         else{
                                 printf("Semantic error on col %d\n",$2);
                                 exit(0);
                         }
                        }
        | expr SUB expr {if($1.row == $3.row && $1.col == $3.col){
                                $$ = $1;
                         }
                         else{
                                 printf("Semantic error on col %d\n",$2);
                                 exit(0);
                         }
                        }
        | expr MUL expr {if($1.col == $3.row){
                                $$.row = $1.row;
                                $$.col = $3.col;
                         }
                         else{
                                 printf("Semantic error on col %d\n",$2);
                                 exit(0);
                         }
                        }
        | OPEN expr CLOSE {$$ = $2;}
        | matrix        {$$ = $1;}
        ;
matrix  : LEFT INUMBER C INUMBER RIGHT  {$$.row = $2;$$.col = $4;}
        ;
%%
void yyerror (const char *message)
{

}
int main(int argc, char *argv[]) {
        yyparse();
        return 0;
}
