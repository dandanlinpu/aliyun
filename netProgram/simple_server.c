#include  <unistd.h>
#include  <sys/types.h>       /* basic system data types */
#include  <sys/socket.h>      /* basic socket definitions */
#include  <sys/epoll.h>
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
   if(cflags==-1){
   	perror("fcntl_1 error");
	exit(-1);
   }
   cflags=cflags|O_NONBLOCK;
   if(fcntl(fd,F_SETFL,cflags)){
   	perror("fcntl_2 error");
	exit(-1);
   };
}
void epoll_process(){



}
int main(){
  printf("epoll test main..\n");
  int listenfd,connfd;

  //socket bind listen
  listenfd=open_listenfd(10000);
  set_fd_noblock(listenfd);
 
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
 	    int  n_read=0;
            int  n=0;
	    int  bufsize=10;
            char r_buf[bufsize];
 	    while( bufsize-n>0 && (n_read=read(events[i].data.fd,r_buf+n, bufsize-n)) > 0){
	    	n+=n_read;
	    } 
            
	    if(n_read==-1){
		if(errno==EAGAIN){
		   printf("has read all data \n");
		}else{
		   perror("read error");
		   exit(-1);
		}
	    }
            printf("read %d bytes data:%s \n",n,r_buf);
            
	    //epoll_ctl MOD:when receive data,use this fd to write data.
            struct epoll_event ev;
            ev.data.fd=events[i].data.fd;
            ev.events=EPOLLOUT|EPOLLET;
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
	    int n_write=0;
            int n=0;
            while( bufsize-n>0 && (n_write=write(events[i].data.fd,w_buf+n,bufsize-n))>0 ){
            	n+=n_write;
            }
            if(n_write==-1){
		if(errno==EAGAIN){
 		   printf("has write all data \n");
		}else{
		   perror("write error");
		   exit(-1);
		}
	    }
	    printf("write %d bytes data:%s \n",n,w_buf);
 	}
   
     }//for 
 }  //while
  return 0;
}
