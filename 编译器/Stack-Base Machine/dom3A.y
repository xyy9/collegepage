%{
#include <stdio.h>
#include <stdlib.h>
int stack[100];
int top = -1;
int a = 0, b = 0;
void push(int data){
    if(top >= 100)  printf("stack is full");
    else{
        top++;
        stack[top] = data;
    }
}
int pop(){
    int data;
    if(top == -1){
        printf ("Invalid format\n");
        exit(0);
    }
    else{
        data = stack[top];
        top--;
        return data;
    }
}
void yyerror(const char *message);
%}
%union {
int ival;
}
%token <ival> INUMBER
%token ADD
%token SUB
%token MUL
%token MOD
%token INC
%token DEC
%token LOAD
%type <ival> expr
%left '+'
%%
program : lines         {if(top != 0){
                            printf ("Invalid format\n");
                         }
                         else{
                             printf ("%d", stack[0]);
                         }
                        }
lines   : lines line    {;}
        | line          {;}
        ;
line    : expr '\n'     {;}
        ;
expr    : ADD           {a = pop();
                         b = pop();
                         push(a+b);
                        }
        | SUB           {a = pop();
                         b = pop();
                         push(a-b);
                        }
        | MUL           {a = pop();
                         b = pop();
                         push(a*b);
                        }
        | MOD           {a = pop();
                         b = pop();
                         push(a%b);
                        }
        | INC           {a = pop() + 1;
                         push(a);
                        }
        | DEC           {a = pop() - 1;
                         push(a);
                        }
        | LOAD INUMBER  {push($2);}
        ;
%%
void yyerror (const char *message)
{

}

int main(int argc, char *argv[]) {
        yyparse();
        return 0;
}
