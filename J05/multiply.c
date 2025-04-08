#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100

// your code here
struct thread{
  pthread_t id;
  int index;
  int vector[SIZE];
  int M[SIZE * SIZE];
  int u[SIZE];
};

void *threadMultiply( void* i){
  struct thread* threadArr = (struct thread*) i;
  int* index = &threadArr->index;
  int start = SIZE/4 * *index;
  int end = SIZE/4 * (*index + 1);
  int *M = threadArr->M;
  int *u = threadArr->u;
  int *vector = threadArr->vector;

  for (int i = 0; i < SIZE; i++) {
    vector[i] = 0;
  }

  for (int i = start; i < end; i++) {
    for (int j = 0; j < SIZE; j++) {
      vector[i] += M[i*SIZE + j] * u[j];
    }
  }

  return NULL;
}

int main(int argc, char *argv[]) {
  srand(time(0));

  int M[SIZE*SIZE];
  int u[SIZE];
  int result[SIZE];
  int result_threads[SIZE];
   
  for (int i = 0; i < SIZE; i++) {
    u[i] = rand() % 10 - 5;
    result[i] = 0;
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      int value = rand() % 10 - 5;
      M[i*SIZE + j] = value;
      result[i] += value * u[j];
    }
  }

  // TODO: Implement your thread solution here
  printf("Test with 4 threads\n");

  struct thread threads[4];
  
  for( int i = 0; i < 4; i++){
    threads[i].index = i;
    memcpy(threads[i].M, M, sizeof(M));
    memcpy(threads[i].u, u, sizeof(u));
    pthread_create(&threads[i].id, NULL, threadMultiply, &threads[i]);
  }

  for( int i =0; i < 4; i++){
    pthread_join(threads[i].id, NULL);
    for( int z = SIZE/4 * i; z < SIZE/4 * (i+1); z++){
      result_threads[z] = threads[i].vector[z];
    }
  }

  int error = 0;
  for (int i = 0; i < SIZE; i++) {
    error += abs(result[i] - result_threads[i]);
  }
  printf("Error between ground truth and multithreaded version: %d\n", error);

  return 0;
}
