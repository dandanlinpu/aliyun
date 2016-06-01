#include  <unistd.h>
#include  <sys/types.h>       /* basic system data types */
#include  <sys/socket.h>      /* basic socket definitions */
#include  <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include  <arpa/inet.h>       /* inet(3) functions */
#include <sys/select.h>       /* select function*/
#include <sys/poll.h>     
#include <sys/epoll.h>     

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
int main(){
printf("EOF %d\n",EOF);
printf("EINTR %d\n",EINTR);
printf("EPIPE %d\n",EPIPE );
printf("EAGAIN %d\n",EAGAIN);
printf("EPOLLHUP %d\n",EPOLLHUP);
}//main
