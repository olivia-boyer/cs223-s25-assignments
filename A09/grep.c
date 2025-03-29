#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int  scanFiles (char** files, int numFiles, int startID) {
    char* line = malloc(sizeof(char) * 81);
    int occurences = 0;

    printf("Process [%d] searching %d files (%d to %d)\n",
        getpid(), numFiles, startID, startID + numFiles);

    for (int i = startID; i < startID + numFiles; i++) {
        FILE* file = fopen(files[i], "r");
        if (file == NULL) {
            perror("Error");
            continue;
        }
        while (fgets(line, 81, file)) {
            char* p = strstr(line, files[2]);
            if (p) {
                printf("%d) %s: %s\n", getpid(), files[i], p);
                occurences += 1;
            }
        }
        fclose(file);
    }
     
    free(line);
    return occurences;       
}

int main(int argc, char** argv) {
    int numProc = atoi(argv[1]);
    char* keyword = argv[2];
    int numFiles = argc - 3;
    int readNum = numFiles / numProc;    
    int isParent = 1;
    int startId = 3;
    int* children = malloc(sizeof(int) * (numProc - 1));
    
    printf("searching %d files for keyword: %s \n", numFiles, keyword);
    

    for (int i = 0; i < numProc - 1; i++) {
        if (isParent) {
            isParent = fork();
            children[i] = isParent;
        } 

        if (!isParent) {
            int exitCode = scanFiles(argv, readNum, startId);
            exit(exitCode);
        }

        startId += readNum;
    }

    int temp = 0;
    int res = 0;

        if (isParent) {
            readNum = argc - startId;
            res = scanFiles(argv, readNum, startId);

            for (int i = 0; i < numProc - 1; i++) {
                waitpid(children[i], &temp, 0);
                res += WEXITSTATUS(temp);
                printf("%d %d\n", children[i], WEXITSTATUS(temp));
            }
        }

    printf("%d\n", res);
    free(children);
    return 0;
}
