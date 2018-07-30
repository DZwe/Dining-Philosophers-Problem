/* Dining Philosopher's Problem */
/* Authors: Zwe Phone Shein, George Loriya */
/* Operating Systems Final Project */

#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

#define N 5
#define THINKING 0
#define STARVING 1
#define EAT 2
#define LEFT (ph_num+4)%N
#define RIGHT (ph_num+1)%N

sem_t mutex;
sem_t S[N];
int state[N];
int phil_num[N]={0,1,2,3,4};

void eat(int ph_num)
{
  if (state[ph_num] == STARVING && state[LEFT] != EAT && state[RIGHT] != EAT)
  {
      state[ph_num] = EAT;
      sleep(2);
      printf("Philosopher %d takes fork %d and %d\n",ph_num+1,LEFT+1,ph_num+1);
      printf("Philosopher %d is Eating\n",ph_num+1);
      sem_post(&S[ph_num]);
  }
}

void take_fork(int ph_num)
{
    sem_wait(&mutex);
    state[ph_num] = STARVING;
    printf("Philosopher %d is Starving\n",ph_num+1);
    eat(ph_num);
    sem_post(&mutex);
    sem_wait(&S[ph_num]);
    sleep(1);
}


void put_fork(int ph_num)
{
    sem_wait(&mutex);
    state[ph_num] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n",ph_num+1,LEFT+1,ph_num+1);
    printf("Philosopher %d is thinking\n",ph_num+1);
    eat(LEFT);
    eat(RIGHT);
    sem_post(&mutex);
}

void *philospher(void *num)
{
    while(1)
    {
        int *i = num;
        sleep(1);
        take_fork(*i);
        sleep(0);
        put_fork(*i);
    }
}

int main()
{
    int i;
    pthread_t thread_id[N];
    sem_init(&mutex,0,1);
    for(i=0;i<N;i++)
        sem_init(&S[i],0,0);
    for(i=0;i<N;i++)
    {
        pthread_create(&thread_id[i],NULL,philospher,&phil_num[i]);
        printf("Philosopher %d is thinking\n",i+1);
    }
    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL);
}
