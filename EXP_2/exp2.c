#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int i,l;
char input[50],converted[50];
char stack[50],lasthandle[6],handles[][7]={")E(","E+E","E-E","E*E","E^E","E/E","i"};
int top=0;

char prec[9][9]={
   /*input     +   -   *    /  ^   i   (   )   $ */
   /* + */    '>','>','<','<','<','<','<','>', '>',
   /* - */    '>','>','<','<','<','<','<','>', '>',
   /* * */   '>','>','>','>','<','<','<','>', '>',
   /* / */   '>','>','>','>','<','<','<','>', '>',
   /* ^ */   '>','>','>','>','>','<','<','>', '>',
   /* i */   '>','>','>','>','>','e','e','>', '>',
   /* ( */   '<','<','<','<','<','<','<','>', 'e',
   /* ) */   '>','>','>','>','>','e','e','>', '>',
   /* $ */  '<','<','<','<','<','<','<','<', '>',
};

int getindex(char c)
{
switch(c)
{
case '+': return 0;
case '-': return 1;
case '*': return 2;
case '/': return 3;
case '^': return 4;
case 'i': return 5;
case '(': return 6;
case ')': return 7;
case '$': return 8;
}
return -1;
}

void shift()
{
stack[++top]=converted[i];
i++;
stack[top+1]='\0';
}

int reduce()
{
int i,len,found=0,t;
for(i=0;i<7;i++)
{
len=strlen(handles[i]);
if(stack[top]==handles[i][0])
{
found=1;
for(t=0;t<len;t++)
{
 if(stack[top-t]!=handles[i][t])
 {
 found=0;
 break;
 }
}
if(found==1)
{
 stack[top-t+1]='E';
 top=top-t+1;
 strcpy(lasthandle,handles[i]);
 stack[top+1]='\0';
 return 1;
}
}
}
return 0;
}

void dispstack()
{
int j=0;
for(j=0;j<=top;j++)
{
printf("%c",stack[j]);
}
}

void dispinput()
{
int j;
for(j=i;j<l;j++)
{
printf("%c",converted[j]);
}
}
void tokenize(char *raw)
{
 int j=0;
 int len=strlen(raw);
 int k;
 for(k=0;k<len;)
 {
  if(isalpha(raw[k]))
  {
   while(isalpha(raw[k])) k++; 
   converted[j++]='i';
  }
  else if(isdigit(raw[k]))
  {
   while(isdigit(raw[k])) k++; 
   converted[j++]='i';
  }
  else if(strchr("+-*^/()",(raw[k])))
  {
   converted[j++]=raw[k++];
  }
  else
  {
  printf("inval char %c",raw[k]);
  exit(1);
  }
 }
    converted[j++]='$';
    converted[j]='\0';
}
void main()
{
 char raw_inp[50];
 printf("enter exp : ");
 scanf("%s",raw_inp);
 tokenize(raw_inp);
 l=strlen(converted);
 strcpy(stack,"$");
 printf("stack\tinput\taction ");
 while(i<l)
 {
  shift();
  printf("\n");
  dispstack();
  printf("\t");
  dispinput();
  printf("\t");
  printf("shift");
  if(prec[getindex(stack[top])][getindex(converted[i])] == '>')
  {
   while(reduce())
   {
  printf("\n");
  dispstack();
  printf("\t");
  dispinput();
  printf("\t");
  printf("reduce : E->%s",lasthandle);
   }
  }
 }
 if(strcmp(stack,"$E$")==0){
  printf("\n");
  printf(" accepted");}
 else{
   printf("\n");
   printf("\n rejected");
 }
}






