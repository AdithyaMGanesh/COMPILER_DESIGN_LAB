#include<stdio.h>
#include<string.h>

int main()
{
 FILE *fp,*opt;
 char op,fir[10],sec[10],res[10];
 char opr[10];
 fp=fopen("three.txt","r");
 opt=fopen("assembly.txt","w");
 if(!fp)
 {
 printf("error reading");
 }
 if(!opt)
 {
 printf("error writing");
 }
 while(!feof(fp))
 {
  fscanf(fp," %c %s %s %s\n",&op,fir,sec,res);
  printf("%c %s %s %s\n",op,fir,sec,res);
  switch(op)
  {
   case '+': strcpy(opr,"ADD");
              break;
   case '-': strcpy(opr,"SUB");
              break;
   case '*': strcpy(opr,"MUL");
              break;
   case '/': strcpy(opr,"DIV");
              break;
  }
  if(strlen(fir)==2)
  {
    if(fir[1]=='1') fprintf(opt,"MOV AX,BX\n");
        else if(fir[1]=='2') fprintf(opt,"MOV BX,AX\n");
          else  if(fir[1]=='3') fprintf(opt,"MOV CX,DH\n");
               else if(fir[1]=='4') fprintf(opt,"MOV DX,DL\n");
  }
  else fprintf(opt,"MOV AX,%s\n",fir); 
  if(strlen(sec)==2)
  {
    if(sec[1]=='1') fprintf(opt,"%s AX,BX\n",opr);
        else if(sec[1]=='2') fprintf(opt,"%s AX,CX\n",opr);
          else  if(sec[1]=='3') fprintf(opt,"%s AX,DX\n",opr);

  }
  else fprintf(opt,"%s AX,%s\n",opr,sec); 
   if(strlen(res)==2)
  {
    if(res[1]=='1') fprintf(opt,"MOV BX,AX\n");
        else if(res[1]=='2') fprintf(opt,"MOV CX,AX\n");
          else  if(res[1]=='3') fprintf(opt,"MOV DX,AX\n");

  }
 }

}
