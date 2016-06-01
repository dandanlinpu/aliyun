#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

int buf[5];
int in=0;
int out=0;

void* consumer(void * arg){
  sem_wait(&full);
  pthread_mutex_lock(&mutex);   
  out=out%10;
  printf("consumer %d: %d\n",*((int *)(&arg)),buf[out++]);
  pthread_mutex_unlock(&mutex);
  sem_post(&empty);
}

void* producer(void * arg){
  sem_wait(&empty);
  pthread_mutex_lock(&mutex);  
  int data=*((int *)(& arg));
  in=in%10;
  buf[in++]=data;
  printf("producer %d: produce data: %d\n",*((int *)(&arg)),data);
  pthread_mutex_unlock(&mutex);   
  sem_post(&full);
}
int main(){
//初始化全局信号量、锁
 sem_init(&empty,0,5);
 sem_init(&full,0,0);
 pthread_t tid[2];
 int i;
 for(i=0;i<10;i++){
   pthread_create(&tid[0],NULL,producer,(void *)i);
 }
 for(i=0;i<3;i++){
   pthread_create(&tid[0],NULL,consumer,(void *)i);
 }
 pthread_exit(NULL);
 return 0;
}
