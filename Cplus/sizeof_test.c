#include <stdio.h>
void size(int b[4][5]){
printf("b pointer:%d  b[0] pointer:%d\n",sizeof(b),sizeof(b[0]));
}
int main(){
int *pa;
printf("a pointer on this computer:%d byte\n",sizeof(pa));
char a[3]={1,2,3};
printf("a+++::: %d %d %d %d %d\n",a,&a+1,a+1,&a[1]+1);
int (*pa3)[3];
printf("pa[3]: %d\n",sizeof(pa3));

char b[2][3];
printf("b pointer:%d  b[0] pointer:%d\n",sizeof(b),sizeof(b[0]));
printf("%d %d %d %d %d %d %d",b,&b+1,b+1,&b[0]+1,b[0]);
//printf('bb:: %d',b);
char c[2][2]={'a','b','c','d'};
printf("cccc:%c \n",*(char *)(&c[0]+1));
 

}
