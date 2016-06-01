#include  <unistd.h>
#include  <sys/types.h>       /* basic system data types */
#include  <sys/socket.h>      /* basic socket definitions */
#include  <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include  <arpa/inet.h>       /* inet(3) functions */

#include  <fcntl.h>

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int open_listenfd(int port){
  int listenfd;
  //socket 
  listenfd=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in servaddr;
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  servaddr.sin_port=htons(port);
  //bind
  bind(listenfd,(struct sockaddr *) &servaddr,sizeof(servaddr));
  //listen
  listen(listenfd,3);
  return listenfd;
}
void print_sockinfo(struct sockaddr_in *cliaddr){
   if(cliaddr==NULL) return;
   char addrstr[INET_ADDRSTRLEN];
   inet_ntop(AF_INET,&(cliaddr->sin_addr),addrstr,sizeof(addrstr));
   printf("ip:%s port:%d\n",addrstr,ntohs(cliaddr->sin_port));
}
void set_fd_noblock(int fd){
   int cflags=fcntl(fd,F_GETFL,0);
   fcntl(fd,F_SETFL,cflags|O_NONBLOCK);
}

int main(){
  int listenfd,connfd;
  struct sockaddr_in clientaddr;
  int clientlen=sizeof(clientaddr);

  listenfd=open_listenfd(10000);
// accept
  //set_fd_noblock(listenfd);
  connfd= accept(listenfd,(struct sockaddr *)&clientaddr,&clientlen);
  printf("connfd: %d \n",connfd);
  print_sockinfo(&clientaddr);
  char rbuf[10];
  int n=read(connfd,rbuf,10);  
  printf("read %d bytes: %s\n",n,rbuf);

  return 0;
}
