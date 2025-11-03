#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

# define MAX 100

typedef struct{
 char lhs[10],op1[10],op2[10],op[3];
 int valueknown;
 int value;
}Statement;

int isnumber(char *s)
{
 if(s[0]=='+' || s[0]=='-') s++;
 for(int i=0;s[i];i++) {
   if(!isdigit(s[i])) return 0;}
 return 1;
}
int main()
{
 Statement s[MAX];
 int n;
 printf("Enter number of statements:");
 scanf("%d",&n);
 getchar();
  printf("Enter statements in 3ac (a = b + c):\n");
 for(int i=0;i<n;i++)
 {
  char line[50];
  fgets(line,sizeof(line),stdin);
  char tempop[3]="=";
  char lhs[10]="",op1[10]="",op2[10]="";
  int parts = sscanf(line,"%s = %s %s %s",lhs,op1,tempop,op2);
  strcpy(s[i].lhs,lhs);
    strcpy(s[i].op1,op1);
      strcpy(s[i].op,tempop);
        strcpy(s[i].op2,(parts==4)?op2:"");
        s[i].valueknown=0;
 }
 for(int i=0;i<n;i++)
 {
   for(int j=0;j<i;j++)
   {
    if(s[j].valueknown)
    {
     char val[10];
     sprintf(val,"%d",s[j].value);
     if(strcmp(s[i].op1,s[j].lhs)==0)
       strcpy(s[i].op1,val);
     if(strcmp(s[i].op2,s[j].lhs)==0)
       strcpy(s[i].op2,val);
    }
   }
   if(isnumber(s[i].op1) && (isnumber(s[i].op2) || strlen(s[i].op2)==0))
   {
    int val1=atoi(s[i].op1);
    int val2=(strlen(s[i].op2) > 0) ?atoi(s[i].op2):0;
    int res=val1;
    if(strcmp(s[i].op,"+")==0)
       res=val1+val2;
   else if(strcmp(s[i].op,"-")==0)
       res=val1-val2;
      else if(strcmp(s[i].op,"*")==0)
       res=val1*val2;
       else if(strcmp(s[i].op,"/")==0 && val2!=0)
       res=val1/val2;
       s[i].valueknown=1;
       s[i].value=res;
       sprintf(s[i].op1,"%d",res);
       strcpy(s[i].op,"=");
       strcpy(s[i].op2,"");
       
   }
 
 }
 printf("After constant propogation:\n");
  for(int i=0;i<n;i++)
  {
   if(s[i].valueknown)
    printf("%s = %d\n",s[i].lhs,s[i].value);
   else
       printf("%s = %s %s %s\n",s[i].lhs,s[i].op1,s[i].op,s[i].op2);
  }
return 0;
}
