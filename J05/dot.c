#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100000

// your code here
struct thread{
  pthread_t id;
  int index;
  int sum;
  int v[SIZE];
  int u[SIZE];
};

void *dot( void* i){
  struct thread* threadArr = (struct thread*) i;
  int* index = &threadArr->index;
  int dotproduct = 0;
  int *v = threadArr->v;
  int *u = threadArr->u;
  int start = SIZE/4 * *index;
  int end = SIZE/4 * (*index + 1);
  for (int i = start; i < end; i++) {
    dotproduct += u[i] * v[i];
  }

  threadArr->sum = dotproduct;
  
  return NULL;
}

int main(int argc, char *argv[]) {
  srand(time(0));

  int v[SIZE];
  int u[SIZE];
  int dotproduct = 0;
   
  for (int i = 0; i < SIZE; i++) {
    v[i] = rand() % 1000 - 500;
    u[i] = rand() % 1000 - 500;
    dotproduct += u[i] * v[i];
  }
  printf("Ground truth dot product: %d\n", dotproduct);

  // TODO: Implement your thread solution here
  
  int thread_dotproduct = 0;
  
  printf("Test with 4 threads\n");

  struct thread threads[4];
  
  for( int i = 0; i < 4; i++){
    threads[i].index = i;
    memcpy(threads[i].v, v, sizeof(v));
    memcpy(threads[i].u, u, sizeof(u));
    pthread_create(&threads[i].id, NULL, dot, &threads[i]);
  }

  for( int i = 0; i < 4; i++){
    pthread_join(threads[i].id, NULL);
    thread_dotproduct += threads[i].sum;
  }
  
  printf("Answer with threads: %d\n", thread_dotproduct);

  return 0;
}


