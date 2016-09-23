#include <sys/epoll.h>
#include "sock_common.h"
#include "rio.h"
void epoll_process(int listenfd){
  //epoll_create 
  int epfd=epoll_create1(0);
  if(epfd==-1){
     perror("epoll_create error");
     exit(-1);
  }
  //epoll_ctl: ADD listenfd
  struct epoll_event event;
  event.data.fd=listenfd;
  event.events=EPOLLIN|EPOLLET;
  if( epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&event)==-1){
     perror("epoll_ctl add  listenfd error");
     exit(-1);
  }
  
  //epoll_wait
  while(true){
     int maxevents=100;
     struct epoll_event events[maxevents];
     int n_events=epoll_wait(epfd,events,maxevents,-1);
     for(int i=0;i<n_events;i++){
        if(events[i].data.fd==listenfd){
            printf("process listenfd %d \n",listenfd);
 	    //accept
	    struct sockaddr_in clientaddr;
            socklen_t clientlen=sizeof(clientaddr);
            int connfd;
	    while(  (connfd=accept(listenfd,(struct sockaddr *)&clientaddr,&clientlen))>0  ){
		//handle client
  	    	printf("connfd: %d\n",connfd);
	    	print_sockinfo(&clientaddr);
	    	//epoll_ctl: ADD connfd
	    	struct epoll_event ev;
	    	ev.data.fd=connfd;
  	    	ev.events=EPOLLIN|EPOLLET;
            	if(epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev)==-1){
     		   perror("epoll_ctli add connfd  error");
                   exit(-1);
 		};
                set_fd_noblock(connfd);
	    };	
    	    if(connfd==-1){
		if(errno==EAGAIN){
		   printf("has process all SYN request \n");
		}else{
 	   	   perror("accept error");
		   exit(-1);
		}
	    }
	    
	}else if(events[i].events & EPOLLIN){
            printf("process EPOLLIN, fd:%d \n",events[i].data.fd);
	    int  bufsize=8192;
            char r_buf[bufsize];
            memset(r_buf,0,bufsize);
            int n_read=rio_readn(events[i].data.fd,r_buf,bufsize); //client直接在nc上输入ctrl+d 服务器收到FIN：w
            printf("read %d bytes data:%s \n",n_read,r_buf);
            
	    //epoll_ctl MOD:when receive data,use this fd to write data.
            struct epoll_event ev;
            ev.data.fd=events[i].data.fd;
            ev.events=EPOLLOUT|EPOLLET;
            printf("change fd %d to EPOLLOUT\n",events[i].data.fd);
            if(epoll_ctl(epfd,EPOLL_CTL_MOD,events[i].data.fd,&ev)==-1){
                perror("epoll_ctl mod  error");
     		exit(-1);
	    }; 
	}else if(events[i].events & EPOLLOUT){
            printf("process EPOLLOUT, fd:%d\n",events[i].data.fd);
            int bufsize=120;
            char w_buf[bufsize];
            for(int _i=0;_i<bufsize;_i++){
              	w_buf[_i]=_i+'1'; 
 		if(_i==(bufsize-1))   w_buf[bufsize-1]='\0';
            }
            int n_write=rio_writen(events[i].data.fd,w_buf,bufsize);
	    printf("write %d bytes data:%s \n",n_write,w_buf);
            //简单的服务器：[接受client连接->接收client数据->发送数据-> ]断开连接,close将会从epoll监听的描述符中去除，并发送fin
            close(events[i].data.fd);
 	}
   
     }//for 
  }  //while
}
int main(){
  printf("epoll test main..\n");
  
  //socket bind listen
  int  listenfd=open_listenfd(10000);
  set_fd_noblock(listenfd);
  epoll_process(listenfd);
  return 0;
}
