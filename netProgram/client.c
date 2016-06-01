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
int main(){

  int clientfd;
  struct sockaddr_in servaddr;
//socket
  clientfd=socket(AF_INET,SOCK_STREAM,0);
//serveraddr  
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(11111);
  inet_pton(AF_INET,"127.0,0,1",&servaddr.sin_addr);
//connect
  if(connect(clientfd,(struct sockaddr *) &servaddr ,sizeof(servaddr))==-1 )
    printf("connect error");
  return 0;
}
