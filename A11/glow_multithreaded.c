/*Author: Olivia Boyer.
 *Description: utilizes multiple threads for more efficient implementation of 
 *glow filter. Takes command-line arguments to allow for various image inputs,
 *blur radius, etc.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <pthread.h>

struct threadArgs
{
  struct ppm_pixel *brightMap;
  struct ppm_pixel *newPixels;
  struct ppm_pixel *pixels;
  int w;
  int h;
  int id;
  pthread_barrier_t *barrier;
  int blurSize;
  int threshold;
};

int findAverage(struct ppm_pixel *brightMap, int r, int c,
                int w, int h, int b)
{

  //  printf("%d \n", r);

  int highW, lowW, highH, lowH;
  int div = 0;
  int sum = 0;
  int dist = (b - 1) / 2;

  if ((w - c) <= dist)
  {
    highW = w;
  }
  else
  {
    highW = c + dist;
  }

  if ((h - r) <= dist)
  {
    highH = h;
  }
  else
  {
    highH = r + dist;
  }

  if ((c) <= dist)
  {
    lowW = 0;
  }
  else
  {
    lowW = c - dist;
  }

  if ((r) <= dist)
  {
    lowH = 0;
  }
  else
  {
    lowH = r - dist;
  }

  for (int i = lowH; i < highH; i++)
  {
    for (int j = lowW; j < highW; j++)
    {
      sum += brightMap[(w * i) + j].red;
      div += 1;
    }
  }
  // printf("%d %d\n", r, c);
  return sum / div;
}

void *glowEffect(void *arguments)
{
  struct threadArgs *args = (struct threadArgs *)arguments;
  int w = args->w;
  int h = args->h;
  int start = h * args->id;
  h = h + start;
  printf("Thread sub-image slice: rows (%d, %d)\n",start, h);
  int brightness = 0;

  for (int i = start; i < h; i++)
  {
    for (int j = 0; j < args->w; j++)
    {

      brightness = (args->pixels[(w * i) + j].red +
                    args->pixels[(w * i) + j].blue + args->pixels[(w * i) + j].green) /
                   3;

      if (brightness > args->threshold)
      {
        args->newPixels[(w * i) + j].red = brightness;
        args->newPixels[(w * i) + j].blue = brightness;
        args->newPixels[(w * i) + j].green = brightness;
      }
      else
      {
        args->newPixels[(w * i) + j].red = 0;
        args->newPixels[(w * i) + j].blue = 0;
        args->newPixels[(w * i) + j].green = 0;
      }
    }
  }
  pthread_barrier_wait(args->barrier);

  int blurVal = 0;

  for (int i = start; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      blurVal = findAverage(args->newPixels, i, j, w, h, args->blurSize);
      args->brightMap[(w * i) + j].blue = blurVal;
      args->brightMap[(w * i) + j].red = blurVal;
      args->brightMap[(w * i) + j].green = blurVal;
    }
  }

  int index = 0;
  int sum = 0;

  for (int i = start; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      index = (w * i) + j;
      sum = args->pixels[index].red + args->brightMap[index].red;

      if (sum > 255)
      {
        args->pixels[index].red = 255;
      }
      else
      {
        args->pixels[index].red = sum;
      }

      sum = args->pixels[index].blue + args->brightMap[index].blue;

      if (sum > 255)
      {
        args->pixels[index].blue = 255;
      }
      else
      {
        args->pixels[index].blue = sum;
      }

      sum = args->pixels[index].green + args->brightMap[index].green;

      if (sum > 255)
      {
        args->pixels[index].green = 255;
      }
      else
      {
        args->pixels[index].green = sum;
      }
    }
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  pthread_barrier_t barrier;
  int N = 4;
  int threshold = 200;
  int blursize = 24;
  const char *filename = "earth-small.ppm";

  int opt;
  while ((opt = getopt(argc, argv, ":N:t:b:f:")) != -1)
  {
    switch (opt)
    {
    case 'N':
      N = atoi(optarg);
      break;
    case 't':
      threshold = atof(optarg);
      break;
    case 'b':
      blursize = atof(optarg);
      break;
    case 'f':
      filename = optarg;
      break;
    case '?':
      printf("usage: %s -N <NumThreads> -t <brightness threshold> -b <box blur size> -f <ppmfile>\n", argv[0]);
      break;
    }
  }
  pthread_barrier_init(&barrier, NULL, N);
  int w, h;
  struct ppm_pixel *pixels = read_ppm(filename, &w, &h);

  // printf("%d \n", h);
  struct ppm_pixel *newPixels = (struct ppm_pixel *)malloc(
      sizeof(struct ppm_pixel) * w * h);

  struct ppm_pixel *blurred = (struct ppm_pixel *)malloc(
      sizeof(struct ppm_pixel) * w * h);

  if (pixels == NULL || newPixels == NULL || blurred == NULL)
  {
    printf("Error: failed to create array.");
    return 0;
  }
  pthread_barrier_init(&barrier, NULL, N);

  pthread_t *tids = (pthread_t *)malloc(sizeof(pthread_t) * N);

  struct threadArgs *threads = (struct threadArgs *)
      malloc(sizeof(struct threadArgs) * N);

  int chunk = h / N;

  for (int i = 0; i < N; i++)
  {
    threads[i].id = i;
    threads[i].w = w;
    threads[i].h = chunk;
    threads[i].pixels = pixels;
    threads[i].newPixels = newPixels;
    threads[i].brightMap = blurred;
    threads[i].barrier = &barrier;
    threads[i].blurSize = blursize;
    threads[i].threshold = threshold;
    pthread_create(&tids[i], NULL, glowEffect, (void *)&threads[i]);
  }

  for (int i = 0; i < N; i++)
  {
    pthread_join(tids[i], NULL);
  }
 
  write_ppm("glow.ppm", pixels, w, h);

  free(threads);
  free(pixels);
  free(newPixels);
  free(blurred);
  free(tids);
  return 0;

}
