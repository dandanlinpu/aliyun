#include "rio.h"
int rio_readn(int fd,char *buf,int n){  //读取n个字节到buf中，要么读够了n个字节，fd缓冲数据被读完才返回
    int nleft=n;
    int nread=0;
    while( (nread=read(fd,buf,nleft))>0 ){
        nleft-=nread;
        buf+=nread;
        printf("rio nread %d bytes this time.\n",nread);
    }  
    if(nread==0){
         printf("read EOF.FIN\n");  //ctrl+D
    }else  if(nread==-1 ){
        if(errno==EAGAIN){
	   printf("rio_readn has read all fd buf data\n");
     	}else{
           perror("rio_readn error");
        }
    }
    if(nleft==0) printf("rio_readn:application buf is used up! maybe left some data in the tcp buf.\n"); 
    printf("rio read %d bytes in all\n",n-nleft);
    return n-nleft;
}

int rio_writen(int fd,const char *buf,int n){ //写buf的n个字节到fd中，写完为止
    int nwrite=0;
    int nleft=n;
    while(nleft>0){
       	nwrite=write(fd,buf,nleft);
       	if(nwrite==-1){
	   if(errno==EAGAIN || errno==EINTR){
	   //   printf("tcp buf is full or signal interupt write, can't write data this time.\n");	
              nwrite=0;
	   }else{
              perror("rio_writen error");
              exit(-1);                    
           }
  	}
        nleft-=nwrite;
        buf+=nwrite;        
        // printf("nwrite %d bytes this time.\n",nwrite);
    }
    return n;
}
