%{
#include<stdio.h>
#include<stdlib.h>
int lc=1;
int c=0;
%}

identifier [a-zA-Z_][a-zA-Z0-9_]*
keywords (int|float|char|for|do|while|printf|return)

%%
\n           {lc++;}
"#".*        {}
{keywords}   {if(!c) printf("%s\t%d\t%s\n",yytext,lc,"KEYWORD");}
{identifier}"(" {}
"/*"           {c=1;}
"*/"           {c=0;}
"{"           {}
"}"           {}
{identifier}(\[[0-9]*\])? {if(!c) printf("%s\t%d\t%s\n",yytext,lc,"IDENTIFIER");}
\"([^"])*\"  {}
[0-9]+ {if(!c) printf("%s\t%d\t%s\n",yytext,lc,"DIGIT");}
"=" {if(!c) printf("%s\t%d\t%s\n",yytext,lc,"ASSIGN OP");}
">=" {if(!c) printf("%s\t%d\t%s\n",yytext,lc,"GE OP");}
"<=" {if(!c) printf("%s\t%d\t%s\n",yytext,lc,"LE OP");}
"==" {if(!c) printf("%s\t%d\t%s\n",yytext,lc,"EQ OP");}
">" {if(!c) printf("%s\t%d\t%s\n",yytext,lc,"GT OP");}
"<" {if(!c) printf("%s\t%d\t%s\n",yytext,lc,"LT OP");}
"+" {if(!c) printf("%s\t%d\t%s\n",yytext,lc,"ARITH +");}
"-" {if(!c) printf("%s\t%d\t%s\n",yytext,lc,"ARITH -");}
"*" {if(!c) printf("%s\t%d\t%s\n",yytext,lc,"ARITH *");}
"/" {if(!c) printf("%s\t%d\t%s\n",yytext,lc,"ARITH /");}
"%" {if(!c) printf("%s\t%d\t%s\n",yytext,lc,"ARITH %");}
[();;] {}
. {}
%%

int yywrap(void)
{
return 1;
}
int main()
{
FILE *fp = fopen("code.c","r");
if(!fp)
{
perror("failed");
}
printf("LEXEME\tLINE NO\t TOKEN");
yyin=fp;
yylex();
fclose(fp);
return 0;
}

