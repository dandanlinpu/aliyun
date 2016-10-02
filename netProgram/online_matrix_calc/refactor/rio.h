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
int rio_readn(int fd,char *buf,int n);  //读取n个字节到buf中，要么读够了n个字节，要莫tcp缓冲区被读完
int rio_writen(int fd,const char *buf,int n); //写buf的n个字节到fd中，写完为止
