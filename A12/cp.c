#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

#define N 10
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mux = PTHREAD_MUTEX_INITIALIZER;
int buff[N];
int in = 0, out = 0;
int numItems = 0;

int produce_item() {
  return rand() % 10;
}

void consume_item(int item) {

printf("Received item: %d\n", item);

}

void* consumer(void*) {
  int item;
  while(1) {
    sleep(1.0);
    pthread_mutex_lock(&mux);
    while(numItems == 0) {
      pthread_cond_wait(&empty, &mux);
    }
    item = buff[out];
    out = (out + 1) % N;
    numItems--;
    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mux);
    consume_item(item);
    }
  return NULL;
}

void* producer(void*) {
  int item;
  while(1) {
    item = produce_item();
    pthread_mutex_lock(&mux);
    while(numItems >= N) {
      pthread_cond_wait(&full, &mux);
    }
    buff[in] = item;
    in = (in + 1) % N;
    numItems++;
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mux);
    }
  }


int main() {
//create circular queue
//create producer thread
//create consumer thread
//sync actions
//infinite loop  

// todo

pthread_t threads[2];
pthread_create(&threads[0], NULL, producer, NULL);
pthread_create(&threads[1], NULL, consumer, NULL);

pthread_join(threads[0], NULL);
pthread_join(threads[1], NULL);
  return 0;
}

