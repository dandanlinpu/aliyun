#include "http_server.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void form_response_header(int fd,int content_len,char *content_type){
   int maxline=1024;
   char buf[maxline];
   memset(buf,0,maxline);
   sprintf(buf,"HTTP/1.1 200 OK\n");
   sprintf(buf,"%sServer: EPOLL_HTTP_SERVER\n",buf);
   sprintf(buf,"%sContent-Length: %d\n",buf,content_len);
   sprintf(buf,"%sContent-Type: %s\n\n",buf,content_type);
   printf("form_response_header: %s",buf);
   int n_write_header=rio_writen(fd,buf,strlen(buf));
   printf("n_write_header %d bytes data\n",n_write_header);
}

void show_index(int fd,const char *filename){
   int file_fd=open(filename,O_RDONLY,0);
   if(file_fd==-1){
      perror("open error");
      exit(-1);
   }
   //获取文件大小
   struct stat fstat;
   if(stat(filename,&fstat)<0){
      perror("stat error");
      exit(-1);
   }
   int filesize=fstat.st_size;
   printf("filesize: %d \n",filesize);
   //内存映射文件
   char *mem_ptr=(char *)mmap(0,filesize,PROT_READ,MAP_PRIVATE,file_fd,0);
   if(mem_ptr==(char *)-1){
      perror("mmap error");
      exit(-1);
   }
   printf("mem_ptr %p \n",mem_ptr);
  
   //rio写入socket
   char content_type[100];
   memset(content_type,0,sizeof(content_type));
   if(strcmp(filename,"index.html")==0){
	strcpy(content_type,"text/html");
   }else if(strcmp(filename,"bootstrap.min.js")==0){
	strcpy(content_type,"application/javascript");
   }else if(strcmp(filename,"jquery.min.js")==0){
	strcpy(content_type,"application/javascript");
   }else if(strcmp(filename,"bootstrap.min.css")==0){
	strcpy(content_type,"text/css");
   }
   printf("content_type %s\n",content_type);
	
   form_response_header(fd,filesize,content_type);
   int n_write_body=rio_writen(fd,mem_ptr,filesize);
   
   printf("n_write_body %d bytes data\n",n_write_body);
}
void process_http_request(char *buf, int len){
   printf("process_http_request: %s\n",buf);
   char delim[]=" ";
   char *token=strtok(buf,delim);
   token=strtok(NULL,delim);
   printf("get uri:%s\n",token);

}
void get_reponse(){

}
/*
int main(){
   char file_str[20]=".";
   strcat(file_str,"/index.html");
   printf("file_str : %s \n",file_str);   
   show_index(1,file_str);
   //process_http_request(NULL,1); 
   return 0;
}
*/
