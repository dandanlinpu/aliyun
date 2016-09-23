#include "common.h"
int main(){
  printf("main..\n");
  int listenfd,connfd;
  struct sockaddr_in clientaddr;
  socklen_t clientlen;

  //socket bind listen
  listenfd=open_listenfd(10000);
  
  //set_fd_noblock(listenfd);
  //accept
  connfd= accept(listenfd,(struct sockaddr *)&clientaddr,&clientlen);
  if(connfd==-1){
    perror("accept error");
    exit(-1);
  }
  printf("connfd: %d \n",connfd);
  print_sockinfo(&clientaddr);
  //read
  char rbuf[100];
  int n=read(connfd,rbuf,100);  
  printf("read %d bytes data: %s \n",n,rbuf);
  return 0;
}
