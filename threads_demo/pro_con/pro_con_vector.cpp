#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <vector>
#include <list>
using namespace std;
template<typename T>
class wbuf{
 private:
 vector<T>m_vector;
 pthread_mutex_t m_mutex;
 int size;
 int in;
 int out;
 sem_t full;
 sem_t empty;
 
 public:
 wbuf(int _n):size(_n){
   m_vector.resize(size);
   in=out=0;
   sem_init(&full,0,0);
   sem_init(&empty,0,size);
 }
 T remove(){
   sem_wait(&full);
   pthread_mutex_lock(&m_mutex);
   int item=m_vector[out];
   out=(out+1)%size;
   pthread_mutex_unlock(&m_mutex);
   sem_post(&empty);
   return item;
 }
 void add(T item){
   sem_wait(&empty);
   pthread_mutex_lock(&m_mutex);
   m_vector[in]=item;
   in=(in+1)%size;
   pthread_mutex_unlock(&m_mutex); 
   sem_post(&full);
 }
};

//线程函数不好作为成员函数，因此作为全局变量吧
wbuf<int>Q(3);
void* consumer(void * arg){
  int i = *((int *)(&arg));
  cout<<"consumer-"<<i<<"-wait  "<<endl;
  cout<<"remove:"<<Q.remove();
  cout<<" after-"<<i<<"-consume"<<endl;
}

void* producer(void *arg){
  cout<<"producer...";
  int item = *((int *)(&arg));
  Q.add(item);
  cout<<"  after-"<<item<<"-producer.."<<endl;
}

int main(){
 pthread_t tid[2];
 int i;
 //先生产者，10个缓冲区却只有3个
 for(i=0;i<10;i++){
   pthread_create(&tid[0],NULL,producer,(void *)i);
 }
 for(i=0;i<10;i++){
   pthread_create(&tid[0],NULL,consumer,(void *)i);
 }
 pthread_exit(NULL);
 return 0;
}
