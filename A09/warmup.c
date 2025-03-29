#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

    
int main() {
    int name = 0xA0;
    pid_t pid = getpid();
    printf("%d[ %x\n", pid, name);
    int isChild = fork();
    name += 0x10;

    if (isChild == 0) {
        name += 0x1;
    }

    pid = getpid(); 
    printf("%d[ %x\n", pid, name);

    if (isChild) {
        isChild = fork();        
        name += 0x10;
        if (isChild == 0) {
            name += 0x1;
        }
        pid = getpid();
        printf("%d[ %x\n", pid, name);
    }
    printf("Bye\n");
    return 0;
}
