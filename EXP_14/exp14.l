%{
#include "exp14.tab.h"
#include<stdlib.h>
%}

%%
[\t]+  ;
\n  return'\n';
[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)? {
  yylval.dval=atof(yytext);
  return NUMBER;
}
"+" return'+';
"-" return'-';
"*" return'*';
"/" return'/';
"^" return'^';
"(" return'(';
")" return')';
. return yytext[0];
%%

int yywrap()
{
return 1;
}
