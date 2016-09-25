#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
int main(){
   char buf[]="a,  b  c  | d";
   char delim[]=", |";
   
   char *token=strtok(buf,delim);
   while(token){
      cout<<token<<strlen(token)<<endl;
      token=strtok(NULL,delim);
   }
   return 0;
}
