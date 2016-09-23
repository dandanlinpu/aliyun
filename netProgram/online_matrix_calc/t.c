
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "rio.h"
void write_http_header(int fd){

}
void form_response_header(char *buf,int maxline,int filesize){
   sprintf(buf,"HTTP/1.1 200 OK\n");
   sprintf(buf,"%sServer: EPOLL_HTTP_SERVER\n",buf);
   sprintf(buf,"%sContent-Length: %d\n",buf,filesize);
   sprintf(buf,"%sContent-Type: text/html\n\n",buf);
   printf("form_response_header: %s",buf);
}
int main(){
   int maxline=1024;
   char h_buf[maxline];
   memset(h_buf,0,maxline);
   form_response_header(h_buf,maxline,1130);
   return 0;
}
