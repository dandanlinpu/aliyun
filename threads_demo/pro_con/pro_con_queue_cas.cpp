#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <vector>
#include <list>
using namespace std;

template<typename T>
class wqueue{
 private:
 list<T> m_queue;
 pthread_mutex_t m_mutex;
 pthread_cond_t m_condv; //use a mutex and condation variable

 public:
 T remove(){
   pthread_mutex_lock(&m_mutex);
   while(m_queue.size()==0){
	pthread_cond_wait(&m_condv,&m_mutex);   
   }
   T item = m_queue.front();
   m_queue.pop_front();
   pthread_mutex_unlock(&m_mutex);
   return item;
 }
 void add(T item){
   pthread_mutex_lock(&m_mutex);
   m_queue.push_back(item);
   pthread_cond_signal(&m_condv);
   pthread_mutex_unlock(&m_mutex); 
 }
 int size() { //不是用于等待while-cond中的，而是用于外部获取wqueue的大小
   pthread_mutex_lock(&m_mutex);
   int size = m_queue.size();
   pthread_mutex_unlock(&m_mutex);
   return size;
 }
};
//线程函数不好作为成员函数，因此作为全局变量吧
wqueue<int>Q;
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
 for(i=0;i<10;i++){
   pthread_create(&tid[0],NULL,consumer,(void *)i);
 }
 for(i=0;i<10;i++){
   pthread_create(&tid[0],NULL,producer,(void *)i);
 }
 pthread_exit(NULL);
 return 0;
}
