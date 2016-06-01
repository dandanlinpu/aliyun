#include <iostream>
#include <stdio.h>
int main()
{
   int x = 0;
   __sync_bool_compare_and_swap(&x,0,10);
   printf("%d\n",x);
   return 0;
}
