%{
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int yylex(void);
char yyerror(const char *s);
int keep_running=1;
%}

%union{
double dval;
}
%token <dval> NUMBER;
%left '+''-';
%left '*''/';
%right '^';
%right UMINUS;
%type <dval> expr;

%%
input:
   /**/
   |input line
   ;
line:
   '\n'
   | expr '\n'{
    char choice;
    printf("result : %g\n",$1);
    printf("do you want to continue: ");
    scanf("%c",&choice);
    if (choice!='y' && choice!='Y')
    {
    keep_running=0;
    exit(0);
    } };
expr:  
     NUMBER {$$=$1;}
     | expr '+' expr {$$=$1 + $3;}
     | expr '-' expr {$$=$1 - $3;}
     | expr '*' expr {$$=$1 * $3;}
     | expr '/' expr {
           if($3==0)
           {printf("div by zero\n");
           $$=0;
           }else{ $$= $1 / $3;}}
     | expr '^' expr {$$=pow($1,$3);}
     | '('expr ')'  {$$=$2;}
     |  '-' expr %prec UMINUS {$$=-$2;}
     ;
%%
char yyerror(const char *s)
{
printf("error : %s\n",s);
}
int main()
{
printf("calculator\n");
printf("enter exp : ");
while(keep_running)
{
yyparse();
}
return 0;
}
