#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
using namespace std;
int main(){
  int fd = open("index.html",O_RDONLY);
  if(fd<0){
    cout<<__FILE__<<__LINE__<<strerror(errno)<<endl;
  }
  cout<<"here"<<endl;

}
