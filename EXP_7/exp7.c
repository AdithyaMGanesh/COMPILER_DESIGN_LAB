#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INS 100

typedef struct{
 char operator;
 char op1[10];
 char op2[10];
 char result[10];
}Instruction;

int is_same_exp(Instruction *a,Instruction *b)
{
 if(a->operator!=b->operator) return 0;
 if(a->operator == '+' || b->operator == '-')
  return ((strcmp(a->op1,b->op1)==0 && strcmp(a->op2,b->op2)==0) || (strcmp(a->op1,b->op2)==0 && strcmp(a->op2,b->op1)==0));
  else
      return (strcmp(a->op1,b->op1)==0 && strcmp(a->op2,b->op2)==0);
}

int is_redefined(Instruction instr[],int i, int j)
{
 for(int k=i+1;k<j;k++)
  {
   if(instr[k].operator == '=')
    {
     if(strcmp(instr[k].op1,instr[i].op1)==0 || strcmp(instr[k].op1,instr[i].op2)==0)
       return 1;         
    }
  }
  return 0;
}

void common_sub_elm(Instruction instr[],int n)
{
 for(int i=0;i<n;i++)
 {
  if(instr[i].operator==0) continue;
  for(int j=i+1;j<n;j++)
  {
     if(instr[j].operator==0) continue;
      if(is_same_exp(&instr[i],&instr[j]) && !is_redefined(instr,i,j))
       {
        char old_result[10];
        strcpy(old_result,instr[j].result);
             for(int k=j;k<n;k++)
             {
              if(strcmp(instr[k].op1,old_result)==0)
                strcpy(instr[k].op1,instr[i].result);
              if(strcmp(instr[k].op2,old_result)==0)
                strcpy(instr[k].op2,instr[i].result);
       }
       instr[j].operator=0;
     }
  }
 }
}
void  print_elm(Instruction instr[],int n)
{
 for(int i=0;i<n;i++)
  {
   if(instr[i].operator!=0)
     printf("%c %s %s %s\n",instr[i].operator,instr[i].op1,instr[i].op2,instr[i].result);
  }

}
int main()
{
 int n;
 Instruction instr[MAX_INS];
 printf("Enter num of instructions : ");
 scanf("%d",&n);
 for(int i=0;i<n;i++)
 {
  printf("Instruction %d : ",i+1);
  scanf(" %c %s %s %s",&instr[i].operator,instr[i].op1,instr[i].op2,instr[i].result);
 }
 common_sub_elm(instr,n);
 printf("\nAfter elimination : \n");
 print_elm(instr,n);
 return 0;
}
