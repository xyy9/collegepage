%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    void yyerror(const char *message);
    int stack[100];
    int top = -1;
    int a = 0, b = 0;
    int list = 0;
    void push(int data){
        if(top >= 100)  printf("stack is full\n");
        else{
            top++;
            stack[top] = data;
        }
    }
    int pop(){
        int data;
        if(top == -1){
            printf ("stack is empty\n");
            exit(0);
        }
        else{
            data = stack[top];
            top--;
            return data;
        }
    }
    typedef struct node *Node;
    struct node{
        int ival;
        char *sval;
        Node next;
    };
    Node first,ptr,last;
%}
%code requires {
    typedef struct{
        int ival;
        char *sval;
    }eval;
}
%union {
    int ival;
    char* sval;
    eval v;
}
%token <ival> number
%token printnum
%token printbool
%token mod
%token and
%token or
%token not
%token <sval> id
%token <ival> boolval
%token IF
%token DEFINE
%type <v> EXP
%type <ival> MEXP
%type <ival> NUM-OP
%type <ival> PLUS
%type <ival> MINUS
%type <ival> MULTIPLY
%type <ival> DIVIDE
%type <ival> MODULUS
%type <ival> LOGICAL-OP
%type <ival> GREATER
%type <ival> SMALLER
%type <ival> EQUAL
%type <ival> AND-OP
%type <ival> OR-OP
%type <ival> NOT-OP
%type <ival> IF-EXP
%type <ival> TEST-EXP
%type <ival> THEN-EXP
%type <ival> ELSE-EXP
%type <v> VARIABLE
%%
PROGRAM         : STMT                          {exit(0);}
                | STMT PROGRAM
                ;
STMT            : EXP
                | DEF-STMT
                | PRINT-STMT
                ;
PRINT-STMT      : '(' printnum EXP ')'          {printf("%d\n",$3.ival);}
                | '(' printbool EXP ')'         {printf("%s\n",$3.sval);}
                ;
EXP             : boolval                       {if($1 == 1) $$.sval = "#t";
                                                 else $$.sval = "#f";
                                                 push($1);
                                                }
                | number                        {$$.ival = $1;push($1);}
                | VARIABLE                      {$$.ival = $1.ival;}
                | NUM-OP                        {$$.ival = $1;push($1);}
                | LOGICAL-OP                    {if($1 == 1) $$.sval = "#t";
                                                 else $$.sval = "#f";
                                                 push($1);
                                                }
                //| FUN-EXP                       
                //| FUN-CALL                      
                | IF-EXP                        {$$.ival = $1;}
                ;
MEXP            : EXP                           {$$ = 1;}
                | EXP MEXP                      {$$ = $2 + 1;}
                ;
NUM-OP          : PLUS                          {int i = $1;
                                                 for(;i>1;i--){
                                                     a = pop();
                                                     b = pop();
                                                     push(a+b);
                                                 }
                                                 $$ = pop();
                                                }
                | MINUS                         {a = pop();
                                                 b = pop();
                                                 push(b-a);
                                                 $$ = pop();
                                                }
                | MULTIPLY                      {int i = $1;
                                                 for(;i>1;i--){
                                                     a = pop();
                                                     b = pop();
                                                     push(a*b);
                                                 }
                                                 $$ = pop();
                                                }
                | DIVIDE                        {a = pop();
                                                 b = pop();
                                                 push(b/a);
                                                 $$ = pop();
                                                }
                | MODULUS                       {a = pop();
                                                 b = pop();
                                                 push(b%a);
                                                 $$ = pop();
                                                }
                ;
PLUS            : '(' '+' EXP MEXP ')'          {$$ = $4 + 1;}
                ;
MINUS           : '(' '-' EXP EXP ')'           {$$ = 2;}
                ;
MULTIPLY        : '(' '*' EXP MEXP ')'          {$$ = $4 + 1;}
                ;
DIVIDE          : '(' '/' EXP EXP ')'           {$$ = 2;}
                ;
MODULUS         : '(' mod EXP EXP ')'           {$$ = 2;}
                ;
LOGICAL-OP      : GREATER                       {a = pop();
                                                 b = pop();
                                                 if(b > a) $$ = 1;
                                                 else $$ = 0;
                                                }
                | SMALLER                       {a = pop();
                                                 b = pop();
                                                 if(b < a) $$ = 1;
                                                 else $$ = 0;
                                                }
                | EQUAL                         {int i = $1;
                                                 for(;i>1;i--){
                                                     a = pop();
                                                     b = pop();
                                                     if(a == b) {
                                                         if(i==2) push(1);
                                                         else push(a);
                                                     }
                                                     else{
                                                         push(0);
                                                         break;
                                                     }
                                                     printf("a:%d,b:%d",a,b);
                                                 }
                                                 $$ = pop();
                                                }
                | AND-OP                        {int i = $1;
                                                 for(;i>1;i--){
                                                     a = pop();
                                                     b = pop();
                                                     if(a == 1 && b == 1) push(1);
                                                     else push(0);
                                                 }
                                                 $$ = pop();
                                                }
                | OR-OP                         {int i = $1;
                                                 for(;i>1;i--){
                                                     a = pop();
                                                     b = pop();
                                                     if(a == 1 || b == 1) push(1);
                                                     else push(0);
                                                 }
                                                 $$ = pop();
                                                }
                | NOT-OP                        {a = pop();
                                                 if(a == 1) $$ = 0;else $$ = 1;
                                                }
                ;
GREATER         : '(' '>' EXP EXP ')'           {$$ = 2;}
                ;
SMALLER         : '(' '<' EXP EXP ')'           {$$ = 2;}
                ;
EQUAL           : '(' '=' EXP MEXP ')'          {$$ = $4 + 1;}
                ;
AND-OP          : '(' and EXP MEXP ')'          {$$ = $4 + 1;}
                ;
OR-OP           : '(' or EXP MEXP ')'           {$$ = $4 + 1;}
                ;
NOT-OP          : '(' not EXP ')'               {$$ = 1;}
                ;
DEF-STMT        : '(' DEFINE VARIABLE EXP ')'   {Node tmp;
                                                 tmp = (Node)malloc(sizeof(Node));
                                                 tmp->ival = $4.ival;
                                                 tmp->sval = $3.sval;
                                                 if(list == 0){
                                                    ptr = tmp;
                                                    ptr->next = NULL;
                                                    first = ptr;
                                                    list = 1;
                                                 }
                                                 else{
                                                    ptr->next = tmp;
                                                    ptr = tmp;
                                                    ptr->next = NULL;
                                                 }
                                                 last = ptr;
                                                }
                ;
VARIABLE        : id                            {ptr = first;
                                                 if(list != 0){
                                                    while(ptr->next!=NULL){
                                                     if(strcmp(ptr->sval, $1) == 0){
                                                         $$.ival = ptr->ival;
                                                         break;
                                                     }
                                                     ptr = ptr->next;
                                                 }
                                                 if(strcmp(ptr->sval, $1) == 0){
                                                     $$.ival = ptr->ival;
                                                 }
                                                 ptr = last;
                                                 }
                                                 $$.sval = $1;
                                                }
                ;
/*FUN-EXP         : '(' FUN FUN_IDs FUN-BODY ')'  
                ;
FUN-IDs         : '(' id* ')'                    
                ;
FUN-BODY        : EXP
                ;
FUN-CALL        : '(' FUN-EXP PARAM* ')'         
                | '(' FUN-NAME PARAM* ')' 
                ;
PARAM           : EXP
                ;
FUN-NAME        : id
                ;*/
IF-EXP          : '(' IF TEST-EXP THEN-EXP ELSE-EXP ')'     {if($3 == 1) $$ = $4;else $$ = $5;}
                ;
TEST-EXP        : EXP                               {if($1.sval == "#t") $$ = 1;}
                ;
THEN-EXP        : EXP                               {$$ = $1.ival;}
                ;
ELSE-EXP        : EXP                               {$$ = $1.ival;}
                ;
%%
void yyerror (const char *message)
{
        printf("syntax error\n");
        //printf("Type error!\n");
        exit(0);
}
int main(int argc, char *argv[]) {
        yyparse();
        return 0;
}

