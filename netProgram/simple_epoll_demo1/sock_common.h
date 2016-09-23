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
int open_listenfd (int port);
void print_sockinfo(struct sockaddr_in *cliaddr);
void set_fd_noblock(int fd);
int open_clientfd(int port);
