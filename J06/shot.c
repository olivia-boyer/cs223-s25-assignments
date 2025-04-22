#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigHandler(int sig){
  printf("Help! I've been shot!\n");
  exit(1);
}

int main()
{
  signal(SIGINT, sigHandler);
  while (1);
  return 0;
}
