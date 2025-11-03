#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int n=0,m=0;
int count;
char prod[10][10];
char f[10],first[10];
void add_to_set(char c);
void find_first(char c);
void find_follow(char c);
void main()
{
char c;
printf("enter production numbers: ");
scanf("%d",&count);
int i;
for(i=0;i<count;i++)
{
scanf("%s",prod[i]);
}
char done_first[count];
int ptr_first=-1;
for(int k=0;k<count;k++)
{
c=prod[k][0];
int exist=0;
for(i=0;i<=ptr_first;i++)
{
if(c==done_first[i])
{
exist=1;
break;
}
}
if(exist) continue;
n=0;
find_first(c);
ptr_first++;
done_first[ptr_first]=c;
printf("First(%c) : { ",c);
for(i=0;i<n;i++)
{
printf("%c%s",first[i],(i==n-1)?" ":", ");
}
printf("} \n");
}
printf("\n");
char done_follow[count];
int ptr_follow=-1;
for(int k=0;k<count;k++)
{
c=prod[k][0];
int exist=0;
for(i=0;i<=ptr_follow;i++)
{
if(c==done_follow[i])
{
exist=1;
break;
}
}
if(exist) continue;
m=0;
find_follow(c);
ptr_follow++;
done_follow[ptr_follow]=c;
printf("Follow(%c) : { ",c);
for(i=0;i<m;i++)
{
printf("%c%s",f[i],(i==m-1)?" ":", ");
}
printf("} \n");
}
}

void add_to_set(char c)
{
int i;
for(i=0;i<m;i++)
{
if(c==f[i])
{
return;
}
}
f[m++]=c;
}

void find_first(char c)
{
int j;
if(!isupper(c))
{
first[n++]=c;
return;
}
for(j=0;j<count;j++)
{
if(prod[j][0]==c)
{
if(prod[j][0]==prod[j][3])
{
continue;
}
if(prod[j][3]=='#')
{
first[n++]='#';
}
else if(!isupper(prod[j][3]))
{
first[n++]=prod[j][3];
}
else
find_first(prod[j][3]);
}
}
}

void find_follow(char c)
{
    int i, j;
    if(prod[0][0] == c)
        add_to_set('$');

    for(i = 0; i < count; i++)
    {
        for(j = 3; j < strlen(prod[i]); j++)
        {
            if(prod[i][j] == c)
            {
                // If something comes after c
                if(prod[i][j+1] != '\0')
                {
                    n = 0;
                    find_first(prod[i][j+1]);
                    int eps = 0;
                    for(int k = 0; k < n; k++)
                    {
                        if(first[k] != '#')
                            add_to_set(first[k]);
                        else
                            eps = 1;
                    }
                    // If epsilon is found, add follow of LHS also
                    if(eps)
                        find_follow(prod[i][0]);
                }
                // If c is at the end
                else if(prod[i][j+1] == '\0' && prod[i][0] != c)
                {
                    find_follow(prod[i][0]);
                }
            }
        }
    }
}

