#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


char input[100],output[100];
int err,i,k,errtype;

void E();
void F();
void T();
void EPrime();
void TPrime();

void E()
{
T();
EPrime();
}

void EPrime()
{
if(input[i]=='+' || input[i]=='-')
{
 output[k++]=input[i++];
 T();
 EPrime();
}
}

void T()
{
F();
TPrime();
}

void TPrime()
{
if(input[i]=='*' || input[i]=='/')
{
output[k++]=input[i++];
F();
TPrime();
}
}

void F()
{
if(isalnum(input[i]))
{
output[k++]=input[i++];
}
else if(input[i]=='(')
{
i++;
E();
if(input[i]==')')
{
i++;
}else{
err=1;
errtype=1;
}
}
else
{
err=1;
errtype=2;
}
}

void main()
{
err=0;
errtype=0;
i=0,k=0;
printf("Enter inp : ");
scanf("%s",input);
E();
if(strlen(input)==i && err==0)
{
output[k]='\0';
printf("Accepeted %s\n",input);
}
else {
if(strlen(input)!=i)
{
printf("Unknown token at %d\n",i+1);
}
else if(errtype==1)
printf("missing )\n ");
else if(errtype=2)
printf("invalid token at %d\n",i+1);
printf("Rejeceted %s",input);
}
}



