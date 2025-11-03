#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

# define MAX_STATES 100
# define MAX_SYMBOLS 26
# define MAX_DFA_STATES 256

int n, sym_count;
char symbols[MAX_STATES];
int transitions[MAX_STATES][MAX_SYMBOLS + 1][MAX_STATES];
int visited[MAX_DFA_STATES];
int dfa_transitions[MAX_DFA_STATES][MAX_SYMBOLS];
int dfa_states[MAX_DFA_STATES][MAX_STATES];
int dfa_count=0;

void find_ep_closure(int state,int closure[])
{
 if(closure[state]) return;
 closure[state]=1;
 for(int i=0;i<n;i++)
  {
   if(transitions[state][0][i])
      find_ep_closure(i,closure);
  }
}

void eps_closure_set(int state[],int closure[]){
for(int i=0;i<n;i++)
  {
   if(state[i])
      find_ep_closure(i,closure);
  }
}

int symbol_to_index(char c)
{
 for(int i=0;i<sym_count;i++)
 {
  if(symbols[i]==c) return i;
 }
return -1;
}
int are_same_Sets(int a[],int b[])
{
 for(int i=0;i<n;i++)
 {
  if(a[i]!=b[i]) return 0;
 }
 return 1;
}

int get_dfa_state_index(int state[])
{
  for(int i=0;i<dfa_count;i++)
  {
   if(are_same_Sets(state,dfa_states[i])) return i;
  }
  memcpy(dfa_states[dfa_count],state,sizeof(int)*n);
  return dfa_count++;
}

void convert_to_dfa()
{
 int start_closure[MAX_STATES]={0};
 find_ep_closure(0,start_closure);
 int queue[MAX_DFA_STATES],front=0,rear=0;
 int start_index=get_dfa_state_index(start_closure);
 queue[rear++]=start_index;
 while(front<rear)
 {
  int curr=queue[front++];
  visited[curr]=1;
  for(int s=0;s<sym_count;s++)
  {
   int move_result[MAX_STATES]={0};
    for(int i=0;i<n;i++)
    {
     if(dfa_states[curr][i])
     {
      for(int j=0;j<n;j++)
      {
       if(transitions[i][s+1][j])
         move_result[j]=1;
      }
     }
    }
    int closure[MAX_STATES]={0};
    eps_closure_set(move_result,closure);
    if(memcmp(closure,(int[MAX_STATES]){0},sizeof(closure))==0) continue;
    int next_index=get_dfa_state_index(closure);
    dfa_transitions[curr][s]=next_index;
    if(!visited[next_index])
      queue[rear++]=next_index;
  } 
 }
}
void print_dfa()
{
 printf("dfa trans table\n");
 printf("state\t");
   for(int s=0;s<sym_count;s++)
   {
    printf("%c\t",symbols[s]);
   }
 printf("\n");
     for(int i=0;i<dfa_count;i++)
     {
      if(i==0) printf("->%c\t",'A'+i);
      else if(i==dfa_count-1) printf("*%c\t",'A'+i);
      else printf("->%c\t",'A'+i);
        for(int s=0;s<sym_count;s++)
        {
         int dest=dfa_transitions[i][s];
         if(dest || memcmp(dfa_states[dest],(int[MAX_STATES]){0},sizeof(int)*n))
           printf("%c\t",'A'+dest);
         else
         printf("-\t");
        }
        printf("\n");
     }
}

int main()
{
 printf("Enter number of states: ");
 scanf("%d",&n);
 printf("Enter number of input symbols: ");
 scanf("%d",&sym_count);
 printf("Enter inp symbols : ");
 scanf("%s",symbols);
 memset(transitions,0,sizeof(transitions));
 int t;
 printf("Enter number of transitions:");
 scanf("%d",&t);
  printf("Enter transitions in the fromat state + symbol -> state:\n ");
  for(int i=0;i<t;i++)
  {
   char sym,from,arrow[3],to;
   scanf(" %c + %c %2s %c",&from,&sym,arrow,&to);
   int from_index=from-'A';
      int to_index=to-'A';
         int sym_index=(sym == 'e') ? 0 : symbol_to_index(sym)+1;
         if(sym_index==0 && sym!='e')
         {
          printf("invalid symbol");
          i--;
          continue;
         }
   transitions[from_index][sym_index][to_index]=1;
  }
  convert_to_dfa();
  print_dfa();
  return 0;
}
