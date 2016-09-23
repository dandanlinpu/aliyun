#include "http_server.h"
void form_response_header(char *buf,int maxline,int filesize){
   sprintf(buf,"HTTP/1.1 200 OK\n");
   sprintf(buf,"%sServer: EPOLL_HTTP_SERVER\n",buf);
   sprintf(buf,"%sContent-Length: %d\n",buf,filesize);
   sprintf(buf,"%sContent-Type: text/html\n\n",buf);
   printf("form_response_header: %s",buf);
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
   int maxline=1024;
   char h_buf[maxline];
   memset(h_buf,0,maxline);
   form_response_header(h_buf,maxline,filesize);
   int n_write_header=rio_writen(fd,h_buf,strlen(h_buf));
   printf("n_write_header %d bytes data:%s\n",n_write_header,h_buf);

   int n_write_body=rio_writen(fd,mem_ptr,filesize);
   printf("n_write_body %d bytes data:%s\n",n_write_body,mem_ptr);
}
/*
int main(){
   show_index(1,"index.html");
   return 0;
}
*/
