#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

int parentId;
int childId;

void childHandler(int sig) {
    printf("Marco [%d]\n", parentId);
    kill(parentId, SIGALRM);
}

void parentHandler(int sig) {
    printf("Polo [%d]\n", childId);
}

int main()
{
    parentId = getpid();
 
    printf("Parent is %d\n", getpid());
    char comm; //short for command
    unsigned long hasChild = fork(); 
    if (hasChild) {
        
        childId = hasChild;
        signal(SIGALRM, parentHandler);

        while(1) {

            scanf("%c",&comm);

            if (comm == 'm') {

                kill(hasChild, SIGALRM);
 
            } else if (comm == 'q') {
                kill(hasChild, SIGKILL);
                return 0;
            }

        }
    } else {
        signal(SIGALRM, childHandler);
        while(1){}
    }
    
  return 0;
}
