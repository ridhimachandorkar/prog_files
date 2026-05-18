#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define N 5
pthread_mutex_t fork[N];
sem_t room;
void *philosopher(void *arg) {
    int id=*(int *)arg;

    while (1){
        printf("Philosopher %d is thinking\n",id);
        sleep(1);
        sem_wait(&room); 
        pthread_mutex_lock(&fork[id]);
        pthread_mutex_lock(&fork[(id+1) % N]);
        printf("Philosopher %d is eating\n",id);
        sleep(1);
        pthread_mutex_unlock(&fork[id]);
        pthread_mutex_unlock(&fork[(id+1)%N]);
        sem_post(&room);
    }
    return NULL;
}
int main(){
    pthread_t ph[N];
    int id[N];
    sem_init(&room,0,N-1);
    for (int i=0;i<N;i++)
        pthread_mutex_init(&fork[i],NULL);

    for (int i=0;i < N;i++){
        id[i]=i;
        pthread_create(&ph[i],NULL,philosopher,&id[i]);
    }
    for (int i=0;i<N;i++)
        pthread_join(ph[i],NULL);
    return 0;
}