#include <stdio.h>

int main(){
int num=0x0102;  
char *c=&num; //c指向起始地址-低地址
if(*c == 2) //2为低字节-地址和字节高低一致表明为 小端，不一致为大端
   printf("Little");
else  printf("big");

return 0;
  
}
