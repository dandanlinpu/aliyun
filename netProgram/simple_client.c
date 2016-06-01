#include  <unistd.h>
#include  <sys/types.h>       /* basic system data types */
#include  <sys/socket.h>      /* basic socket definitions */
#include  <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include  <arpa/inet.h>       /* inet(3) functions */
#include <sys/select.h>       /* select function*/

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
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
  return clientfd;
}
int main(){
    int clientfd;
    clientfd=open_clientfd(10000);
    int wirten=write(clientfd,"hi server~",4);
    printf("client write %d words\n",wirten);
  return 0;
}
