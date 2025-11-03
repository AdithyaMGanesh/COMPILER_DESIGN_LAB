#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_STATES 100
#define MAX_SYMBOL 26

int num_symbols,num;
int transitions[MAX_STATES][MAX_SYMBOL];
int marked[MAX_STATES][MAX_STATES];
char symbols[MAX_SYMBOL];
int is_final[MAX_STATES];
int final_states[MAX_STATES];
int new_state_map[MAX_STATES];

void input_dfa()
{
 printf("Enter no of states: ");
 scanf("%d",&num);
 printf("Enter no of inp sym: ");
 scanf("%d",&num_symbols);
 printf("Enter inp symbols: ");
 scanf("%s",symbols);
 printf("Enter the transitions:\N");
 for(int i=0;i<num;i++)
 {
  printf("State %d :",i);
   for(int j=0;j<num_symbols;j++)
    {
     scanf("%d",&transitions[i][j]);
     if(transitions[i][j]>0)
        transitions[i][j]--;
     else
      transitions[i][j]=-1;
    }
 }
 int num_finals;
 printf("Enter no of final states: ");
 scanf("%d",&num_finals);
 printf("Enter the final states separated by space: ");
 for(int i=0;i<num_finals;i++)
 {
  int f;
  scanf("%d",&f);
  final_states[i]=f;
  is_final[f]=1;
}
}

void mark_table()
{
 for(int i=0;i<num;i++)
 {
   for(int j=0;j<num;j++)
    {
     marked[i][j]=0;}}
  for(int i=0;i<num;i++)
 {
   for(int j=0;j<i;j++)
    {
     if(is_final[i]!=is_final[j])
     marked[i][j]=1;}}  
}

void minimize_dfa()
{
 int changed;
 do{
  changed=0;
 for(int i=0;i<num;i++)
   {
   for(int j=0;j<i;j++)
    {
       if(!marked[i][j])
       {
           for(int k=0;k<num_symbols;k++)
           {
            int p=transitions[i][k];
            int q=transitions[j][k];
            if(p==-1 || q==-1) continue;
            if(p==q) continue;
            if(p>q)
            {
             int temp=p;
             p=q;
             q=temp; 
            }
            if(marked[q][p])
            {
             marked[i][j]=1;
             changed=1;
             break;
            }
            
           }
       }
 }
}
}while(changed);
}

void build_new_states()
{
for(int i=0;i<num;i++)
 { new_state_map[i]=-1;}
 int new_count=0;
 for(int i=0;i<num;i++)
 { if(new_state_map[i]==-1)
     {
      new_state_map[i]=new_count;
        for(int j=i+1;j<num;j++)
        {
         int a=i>j?i:j;
         int b=i>j?j:i;
         if(!marked[a][b])
         {
                new_state_map[j]=new_count;
         }
        }
             new_count++;

     }
 }
   printf("Minimized dfa states \n :");
   printf("state mapping\n :");
    for(int i=0;i<num;i++)
    {
    printf("%d -> %c\n",i,'A'+new_state_map[i]);
    }
  printf("Minimized transitions \n :");
  for(int s=0;s<num_symbols;s++)
    {
    printf("%c\t",symbols[s]);
    }
    printf("\n");
  int printed[new_count];
  memset(printed,0,sizeof(printed));
  for(int i=0;i<num;i++)
  {
   int ni=new_state_map[i];
   if(printed[ni]) continue;
   printed[ni]=1;
   printf("%c\t",'A'+new_state_map[i]);
     for(int s=0;s<num_symbols;s++)
     {
      int t=transitions[i][s];
      if(t==-1)
       printf("0\t");
      else
          printf("%c\t",'A'+new_state_map[t]);
     }
     printf("\n");
  }

}

int main()
{
  input_dfa();
  mark_table();
  minimize_dfa();
  build_new_states();
 return 0;
}
