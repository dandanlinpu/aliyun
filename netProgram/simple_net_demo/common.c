#include "common.h"

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
  if(bind(listenfd,(struct sockaddr *) &servaddr,sizeof(servaddr))==-1){
     perror("bind error");
     exit(-1);
  };
  //listen
  if(listen(listenfd,30)==-1){
     perror("listen error");
     exit(-1);
  };
  printf("open listenfd %d\n",listenfd);
  return listenfd;
}


int open_clientfd(int port){
  int clientfd;
  struct sockaddr_in servaddr;
//socket
  clientfd=socket(AF_INET,SOCK_STREAM,0);
//serveraddr  
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  inet_pton(AF_INET,"127.0,0,1",&servaddr.sin_addr);
  servaddr.sin_port=htons(port);
//connect
  if(connect(clientfd,(struct sockaddr *) &servaddr ,sizeof(servaddr))==-1 )
     printf("connect error"); 
  printf("clientfd %d\n",clientfd);
  return clientfd;
}



void print_sockinfo(struct sockaddr_in *client_addr){
   if(client_addr==NULL) return;
   char addrstr[INET_ADDRSTRLEN]; //16
   int port;

   inet_ntop(AF_INET,&(client_addr->sin_addr),addrstr,sizeof(addrstr));
   port=ntohs(client_addr->sin_port);
   printf("remote ip:%s port:%d\n",addrstr,port);
}

void set_fd_noblock(int fd){
   int cflags=fcntl(fd,F_GETFL,0);
   fcntl(fd,F_SETFL,cflags|O_NONBLOCK);
}
