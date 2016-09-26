#include <iostream>
#include <vector>
#include <string>
#include "http_server.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "url_encode.h"
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
vector< vector<int> > matrix_str_process(char *matrix){
   //1 2 3|4 5 6|7 8 9
   cout<<"process matrix: "<<matrix<<endl;
   vector<string> matrix_v;
   vector< vector<int> >result;
   char delim[]="|";
   char *token=strtok(matrix,delim);
   while(token){
        matrix_v.push_back(string(token));
        token=strtok(NULL,delim);
   }
   result.resize(matrix_v.size());
   for(int i=0;i<matrix_v.size();i++){
      char s[30];
      strcpy(s,matrix_v[i].data());
      char *_token=strtok(s," ");
      while(_token){
        result[i].push_back(atoi(_token));
      	_token=strtok(NULL," ");
      }
   }
   for(int i=0;i<result.size();i++){
     for(int j=0;j<result[i].size();j++){
   	cout<<"result:"<<result[i][j]<<" ";
     }
	cout<<endl;
   }
   return result;
}
void calc(int fd,char url[]){
 //  url="/calc?matrix1=%5B1+2+3%7C4+5+6%7C7+8+9%5D&matrix2=%5B7+8%7C10+11%7C55+100%5D&operation=multiply";
   string str_dec=UrlDecode(string(url));
   cout<<"url decoded.."<<str_dec<<endl;
   char str_res[100];
   strcpy(str_res,str_dec.data());
   cout<<"str_dec:"<<str_dec<<endl;
    
   char delim[]="[]";
   char *token=strtok(str_res,delim);
   char *matrix1=strtok(NULL,delim);
   token=strtok(NULL,delim);
   char *matrix2=strtok(NULL,delim);
   printf("matrix1: %s \n",matrix1);//1 2 3|3 4 5|6 7 8
   printf("matrix2: %s \n",matrix2);
   
  vector<vector<int> >matrix1_num_v =  matrix_str_process(matrix1);
  vector<vector<int> >matrix2_num_v =  matrix_str_process(matrix2);
  //矩阵运算
  cout<<"matrix calc"<<endl;
  vector<vector<int> >matrix_result(3,vector<int>(3,0));
  for(int i=0;i<matrix_result.size();i++){
     for(int j=0;j<matrix_result[0].size();j++){
        matrix_result[i][j]=i+j;
     }
  }
  //结果矩阵字符串化
  char res_buf[100];
  memset(res_buf,0,sizeof(res_buf));
  for(int i=0;i<matrix_result.size();i++){
     for(int j=0;j<matrix_result[0].size();j++){
	sprintf(res_buf,"%s %d",res_buf,matrix_result[i][j]);     
     } 
     if(i!=matrix_result.size()-1){
        sprintf(res_buf,"%s ;",res_buf);
     }
  }
  printf("res_buf %s\n",res_buf); 
  //矩阵运算结果字符串化
  form_response_header(fd,strlen(res_buf),"text/plain");
  int n_writen=rio_writen(fd,res_buf,strlen(res_buf));
  printf("matrix reslut str %d bytes data:%s\n",n_writen,res_buf);
  
  /* 
   vector<string> m1_v;
   vector< vector<int> >m1_vi;
   char delim2[]="|";
   char *token2=strtok(matrix1,delim2);
   while(token2){
        m1_v.push_back(string(token2));
        token2=strtok(NULL,delim2);
   }
   cout<<"1111"<<matrix1<<endl;
   m1_vi.resize(m1_v.size());
   for(int i=0;i<m1_v.size();i++){
      cout<<"m1_v"<<m1_v[i]<<endl;
      char s[30];
      strcpy(s,m1_v[i].data());
      char *m1_token=strtok(s," ");
      while(m1_token){
        m1_vi[i].push_back(atoi(m1_token));
      	m1_token=strtok(NULL," ");
      }
   }
   for(int i=0;i<m1_vi.size();i++){
     for(int j=0;j<m1_vi[i].size();j++){
   	cout<<"m1_vi:"<<m1_vi[i][j]<<" ";
     }
	cout<<endl;
   }
   */


}


/*
int main(){
//   char file_str[20]=".";
 //  strcat(file_str,"/index.html");
  // printf("file_str : %s \n",file_str);   
 //  show_index(1,file_str);
   //process_http_request(NULL,1); 

   calc(NULL);
   
   return 0;
}
*/
