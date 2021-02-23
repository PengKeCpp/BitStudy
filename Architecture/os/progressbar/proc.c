#include "proc.h"

void proc(){
 int i=0;
 const int len=NUM+1;
 char bar[len];
 const char label[]="|/-\\";
 memset(bar,'\0',len);
 while(i<NUM){
  bar[i++]='#';
  printf("[%-100s][%3d%%][%c]\r",bar, i , label[i%4]);
  fflush(stdout); 
  usleep(30000);
 
 }
 printf("\n");
}
