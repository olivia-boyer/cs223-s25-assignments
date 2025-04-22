#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "write_ppm.h"

struct thread_data {
  int starti;
  int endi;
  int width;
  int height;
  struct ppm_pixel color;
  struct ppm_pixel* image;
};

void *start(void* userdata) {
  struct thread_data* data = (struct thread_data*) userdata;
  printf("Thread is coloring rows %d to %d with color %d %d %d\n", data->starti,
      data->endi, data->color.blue, data->color.green, data->color.red);
  int startidx = data->starti * 1024;
  int endidx = data->endi * 1024;
  
      for (int i = startidx; i < endidx; i ++) {
    data->image[i].red = data->color.red;
    data->image[i].green = data->color.green;
    data->image[i].blue = data->color.blue;
  }
  

  return 0;
}

int main(int argc, char** argv) {

  if (argc != 2)
  {
    printf("usage: %s <num>\n", argv[0]);
    exit(0);
  }
  int N = strtol(argv[1], NULL, 10);

  int size = 1024;
  struct ppm_pixel* image = malloc(sizeof(struct ppm_pixel) * size * size);
  struct ppm_pixel* colors = malloc(sizeof(struct ppm_pixel) * N);
  pthread_t* threads = malloc(sizeof(pthread_t) * N);
  struct thread_data* data = malloc(sizeof(struct thread_data) * N);
  int row = 1024/N;

  for (int i = 0; i < N; i++) {
    data[i].starti = i * row;
    data[i].endi = (i + 1) * row;
    data[i].width = 1024;
    data[i].height = 1024;
    data[i].color.red = rand() % 256;
    data[i].color.blue = rand() % 256;
    data[i].color.green = rand() % 256;
    data[i].image = image;
    pthread_create(&threads[i], NULL, start, &data[i]);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  write_ppm("stripes.ppm", image, size, size);
  free(image);
  free(colors);
  free(threads);
  free(data);
}
