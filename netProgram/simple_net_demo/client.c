#include "common.h"
int main(){
    int clientfd;
    clientfd=open_clientfd(10000);
    int wirten=write(clientfd,"hello server~",4);
    printf("client write %d words\n",wirten);
  return 0;
}
