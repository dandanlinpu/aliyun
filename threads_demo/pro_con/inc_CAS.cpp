#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
using namespace std;
int count=0;
pthread_mutex_t m;
void* inc(void *arg){
 //  pthread_mutex_lock(&m);
     int tmp=count;
     usleep(300);//300ms
     count=tmp+1;
//  pthread_mutex_unlock(&m);
}
void* inc_CAS(void *arg){
   int *p=NULL;
   do{
    p=&count;
    usleep(300);
   }while(!__sync_bool_compare_and_swap(p,count,count+1)); 
}
int main(){
  const int N=10;
  pthread_t tid[N];
  pthread_t tid1[N];
  pthread_t tid2[N];
  for(int i=0;i<N;i++){
     pthread_create(&tid[i],NULL,inc_CAS,NULL);
  } 
  for(int i=0;i<N;i++){
  pthread_join(tid[i],NULL);
} 
  cout<<count<<endl;
}
