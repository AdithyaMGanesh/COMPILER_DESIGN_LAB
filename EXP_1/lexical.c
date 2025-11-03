#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

# define MAX 2000

char lexemes[MAX][50];
char tokens[MAX][50];
int lines[MAX];
int entrycount=0;

const char * keywords[]={"include","for","printf","scanf","while","int","char","do","const"};
int numkeywords=sizeof(keywords)/sizeof(keywords[0]);

int iskeyword(char *word){
 int i;
 for(i=0;i<numkeywords;i++)
 {
  if(strcmp(word,keywords[i])==0){
    return 1;
  }
 }
 return 0;
}

int findintable(char *word, const char*type){
 int i;
 for(i=0;i<entrycount;i++)
 {
  if(strcmp(word,lexemes[i])==0 && strcmp(type,tokens[i])==0 ){
    return lines[i];
  }
 }
 return -1;
}

void appendtotable(char * word, const char *type)
{
 if(findintable(word, type)==-1)
 {
   int newline;
   if(entrycount==0)
     newline=1;
   else
    {
     newline=lines[entrycount-1]+1;
    }
    strcpy(lexemes[entrycount],word);
    strcpy(tokens[entrycount],type);
    lines[entrycount]=newline;
    entrycount++;
 }
}

void symtable(){
 FILE *sym = fopen("symbol.txt","w");
 if(!sym)
 {
  printf("error opening sym");
  exit(1);
 }
 fprintf(sym,"LEXEME\tID\tTOKEN\n");
 for(int i=0;i<entrycount;i++)
 {
  fprintf(sym,"%-20s%-10d%5s\n",lexemes[i],lines[i],tokens[i]);
 }
 fclose(sym);
}

int main()
{
 int j=0,l=1,skipstring=0,i;
 char buffer[50],ch,ch1,operators[]="+-*/%";
 FILE *fp=fopen("input.txt","r");
 if(!fp)
 {
  printf("error opening inp");
  exit(1);
 }
 FILE *op=fopen("output.txt","w");
 if(!op)
 {
  printf("error opening output");
  exit(1);
 }
fprintf(op,"%-20s%-10s%5s\n","LEXEME","LINENO","TOKEN");

 while((ch=fgetc(fp))!=EOF)
 {
  if(ch=='"'){
   skipstring=!skipstring;
   continue;
  }
  if(skipstring) continue;
  for( i=0;i<5;i++)
  {
   if(ch==operators[i])
   {
    char temp[2]={ch,'\0'};
    appendtotable(temp,"Arith op");
    int id=findintable(temp,"Arith op");
    fprintf(op,"%-20s%-10dArithmetic op(%d)\n",temp,l,id);
    break;
   }
  }
  if(i==5)
  {
   if(isalnum(ch))
   {
    buffer[j++]=ch;
    ch1=fgetc(fp);
    if(!isalnum(ch1))
    {
     buffer[j]='\0';
     fseek(fp,-1,SEEK_CUR);
     if(strcmp(buffer,"main")==0)
     {
      j=0;
      continue;
     }
	     if(isdigit(buffer[0]))
	    {
	    appendtotable(buffer,"number");
	    int id=findintable(buffer,"number");
	    fprintf(op,"%-20s%-10dnumber(%d)\n",buffer,l,id);
	    } 
	    else if(iskeyword(buffer))
	    {
	    appendtotable(buffer,"keyword");
	    int id=findintable(buffer,"keyword");
	    fprintf(op,"%-20s%-10dkeyword(%d)\n",buffer,l,id);
	    } 
	    else
	    {
	    appendtotable(buffer,"identifier");
	    int id=findintable(buffer,"identifier");
	    fprintf(op,"%-20s%-10didentifier(%d)\n",buffer,l,id);
	    } 
	    j=0;
    }
    else
    {
     fseek(fp,-1,SEEK_CUR);
    }
   }
   else if(ch=='>')
   {
    ch1=fgetc(fp);
    if(ch1=='=')
    {
    appendtotable(">=","Relop GE");
    int id=findintable(buffer,"Relop GE");
    fprintf(op,"%-20s%-10dRelop GE(%d)\n",">=",l,id);
    }
    else{
    fseek(fp,-1,SEEK_CUR);
    appendtotable(">","Relop GT");
    int id=findintable(">","Relop GT");
    fprintf(op,"%-20s%-10dRelop GT(%d)\n",">",l,id);
    
    }
   }
   else if(ch=='<')
   {
    ch1=fgetc(fp);
    if(ch1=='=')
    {
    appendtotable("<=","Relop LE");
    int id=findintable("<=","Relop LE");
    fprintf(op,"%-20s%-10dRelop LE(%d)\n","<=",l,id);
    }
    else{
    fseek(fp,-1,SEEK_CUR);
    appendtotable("<","Relop LT");
    int id=findintable("<","Relop LT");
    fprintf(op,"%-20s%-10dRelop LT(%d)\n","<",l,id);
    }
   }
   else if(ch=='=')
   {
    ch1=fgetc(fp);
    if(ch1=='=')
    {
    appendtotable("==","Equop ");
    int id=findintable("==","Equop");
    fprintf(op,"%-20s%-10dEQ op EQ(%d)\n","==",l,id);
    }
    else{
    fseek(fp,-1,SEEK_CUR);
    appendtotable("=","assign op");
    int id=findintable("=","assign op ");
    fprintf(op,"%-20s%-10dASSIGN OP(%d)\n","=",l,id); 
    }
   }
   else 
   {
    if(ch=='\n')
    {
    l++;
    } 
    }
   }
  
  }
  fclose(fp);
  fclose(op);
   symtable();
 return 0;
 }
 

