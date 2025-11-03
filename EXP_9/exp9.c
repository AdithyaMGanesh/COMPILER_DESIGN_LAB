#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

# define MAX_STATES 26
# define MAX_SYM 10
int n,count,t;
int trans[MAX_STATES][MAX_SYM+1][MAX_STATES];
char symbols[MAX_SYM];

void find_closure(int state,int closure[],int n)
{
 if(closure[state]) return;
 closure[state]=1;
    for(int i=0;i<n;i++)
    {
     if(trans[state][0][i]){ find_closure(i,closure,n);}
    }

}
void print_closure()
{
   printf(" eps closure\n");
   printf(" state  | closure\n");
   printf("-------------------\n");
   for(int i=0;i<n;i++)
   {
    int closure[MAX_STATES]={0};
    find_closure(i,closure,n);
    printf("%c | { ",'A'+i);
    int first=1;
    for(int j=0;j<n;j++)
    {
     if(closure[j])
     {
      if(!first) printf(",");
      printf("%c ",'A'+j);
      first=0;
     }
    }
    printf("} \n");
   }
}

int sym_to_index(char c)
{
   for(int i=1;i<=count;i++)
   {
     if(symbols[i-1]==c) return i;
   }
   return -1;
}

int main()
{
 printf("Enter num of states:");
 scanf("%d",&n);
 printf("Enter num of inp symbols: ");
 scanf("%d",&count);
 printf("Enter inp symbols: ");
 scanf("%s",symbols);
 for(int i=0;i<MAX_STATES;i++)
 {
   for(int j=0;j<=MAX_SYM;j++)
    {
      for(int k=0;k<MAX_STATES;k++)
      {
       trans[i][j][k]=0;    
      }
    } 
 }
 printf("Enter num of transitions: ");
 scanf("%d",&t);
  printf("Enter as state + sym -> state: \n");
 for(int i=0;i<t;i++)
 {
  char from,sym,to;
  scanf(" %c + %c -> %c",&from,&sym,&to);
  int from_index=from-'A';
  int to_index=to-'A';
  int sym_index= (sym=='e')? 0:sym_to_index(sym);
   if (sym_index == -1 && sym != 'e') {
            printf("Invalid symbol '%c'. Try again.\n", sym);
            i--;
            continue;
        }

  trans[from_index][sym_index][to_index]=1;
  if(sym=='e')
  {
   printf("recorded eps transition from  %c -> %c\n",from,to);
  }
  else
     printf("recorded eps transition from  %c + %c -> %c\n",from,sym,to);
 }
 print_closure();
 return 0;
}
