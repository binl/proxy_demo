#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define N 1000

static unsigned int global = 0;
sem_t mutex;
//Have a thread add N to the global variable
void* threadFunc(void* vargp)
{
  int i = 0;
  sem_wait(&mutex); //Start critical code
  unsigned int locGlob = global;
  for (i = 0; i < N; i++)
    locGlob = locGlob + 1;
  global = locGlob;
  sem_post(&mutex); //End critical code
  return NULL;
}

int main()
{
  pthread_t tids[N];
  pthread_t tid;
  sem_init(&mutex,0,1); //Initialize semaphore to allow only 1 thread 
  int i = 0;
  for (i = 0; i < N; i++) //Spawn n threads
    pthread_create(tids+i,NULL,threadFunc,NULL);
  for (i = 0; i < N; i++) //Wait for all to finish
    pthread_join(tids[i], NULL);
  printf("%u\n",global);
  return 0;
}