#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char s[50],post[50],stack[50],queue[50];
int top=-1,front=-1,j=0;

int precedence(char c)
{
 if (c=='+' || c=='-') return 1;
 else if( c=='*' || c=='/') return 2;
 else if( c=='^') return 3;
 else 
   return 0;
}

void postfix()
{
 int i =0,j=0;
 top=-1;
 while(s[i])
 {
  if(s[i]=='(') stack[++top]=s[i];
  else if(isalnum(s[i])) post[j++]=s[i];
  else if(precedence(s[i])>0)
  {
   while(top!=-1 && stack[top]!='(' && ((precedence(stack[top])>precedence(s[i])) || (precedence(stack[top])==precedence(s[i]) && s[i]!='^')))
   {
    post[j++]=stack[top--];
   }
   stack[++top]=s[i];
  }
  else if(s[i]==')')
  {
  while(top!=-1 && stack[top]!='(')      post[j++]=stack[top--];
  while(top!=-1 && stack[top]=='(')      top--;
  }
  i++;
 }
 while(top!=-1) post[j++]=stack[top--];
 post[j]='\0';
}

int temp(char c)
{
 return (c>='1' && c <='9');
}

void quadop(char c)
{
if(temp(c)) printf("t%c",c);
else printf("%c",c);
}

void tripleop(char c)
{
if(temp(c)) printf("%c",c);
else printf("%c",c);
}

int main()
{
 int j=0,top=-1,front=-1;
 printf("enter exp: ");
 scanf("%s",s);
 postfix();
 int i=0;
 char ind='1';
 printf("infix : %s \n postfix : %s",s,post);
 char q[50][50];
 char t[50][50];
 int qcount=0;
 int tcount=0;
 while(post[i]!='\0')
 {
  if(precedence(post[i])>0)
  {
   if(front<1)
   {
   printf("not enough characters ");
break;   }
   char a = queue[front--];
   char b = queue[front--];
   sprintf(q[qcount++],"%c\t%c\t%c\t%c",post[i],a,b,ind);
   sprintf(t[tcount++],"%c\t%c\t%c\t%c",ind,post[i],a,b);
   queue[++front]=ind;
   ind++;
  }
  else
   queue[++front]=post[i];
  i++;
 }
 printf("QUADRUPLE\n");
 printf("op\top1\top2\tres\n");
 for(int k=0;k<qcount;k++)
  {
   char op,o1,o2,res;
   sscanf(q[k],"%c\t%c\t%c\t%c",&op,&o1,&o2,&res);
   printf("%c\t",op);
   quadop(o1);
   printf("\t");
   quadop(o2);
   printf("\tt%c\n",res);
  }
 printf("TRIPLE\n");
 printf("ind\top\top1\top2\n");
 for(int k=0;k<tcount;k++)
  {
   char ind,op,o1,o2;
   sscanf(t[k],"%c\t%c\t%c\t%c",&ind,&op,&o1,&o2);
   printf("%c\t",ind);
   printf("%c\t",op);
   tripleop(o1);
   printf("\t");
   tripleop(o2);
   printf("\n");
  }
  return 0;
}
