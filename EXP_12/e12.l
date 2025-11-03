%{
#include<stdio.h>
int cc=0,wc=0,lc=0;
extern FILE* yyin;
%}

%%
[a-zA-Z0-9]+  { cc += yyleng; wc++; }   /* count letters/numbers as chars + words */
[ \t]+        { }                       /* ignore spaces/tabs */
\n             { lc++; }                 /* increment line count */
.              { cc++; }                 /* count punctuation/symbols */
%%

int yywrap(void) { return 1; }

int main() {
    FILE *fin = fopen("in.txt", "r");
    if (!fin) {
        printf("Error opening file.\n");
        return 1;
    }

    yyin = fin;
    yylex();

    /* Add 1 if the last line has no newline */
    if (cc > 0 || wc > 0) lc++;

    printf("Words: %d\nCharacters: %d\nLines: %d\n", wc, cc, lc);

    fclose(fin);
    return 0;
}
