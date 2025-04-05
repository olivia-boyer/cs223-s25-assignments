#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define MAGENTA "\x1b[35m"
#define BLUE "\x1b[34m"
#define NORMAL "\x1b[0m"

/*Name: Olivia Boyer
 *Description: searches inputted files for keyword using n threads.
*/

pthread_mutex_t mutex;

typedef struct scanFileArgs {
    char** files;
    int numFiles;
    int ID;
    int* total;
} *scanFileArgs;


void* scanFiles (void* inputs) {

    char* line = malloc(sizeof(char) * 81);
    int occurences = 0;

    pthread_mutex_lock(&mutex);

    scanFileArgs args = (scanFileArgs) inputs;     
    int ID = args->ID;
    args->ID++;

    pthread_mutex_unlock(&mutex);

    int startID = (ID * (args->numFiles)) + 3;

    printf("Thread [%d] searching %d files (%d to %d)\n",
        ID, args->numFiles, startID, startID + args->numFiles);

    for (int i = startID; i < startID + args->numFiles; i++) {
  
      FILE* file = fopen(args->files[i], "r");

        if (file == NULL) {

            perror("Error");
            fclose(file);
            continue;

        }

        while (fgets(line, 81, file)) {

            char* p = strstr(line, args->files[2]);

            if (p) {

                printf("%s%d) %s%s:%s %s", MAGENTA, ID, args->files[i],
                     BLUE, NORMAL, p);
                occurences += 1;

            }

        }
        fclose(file);

    }

        printf("Thread [%d] found %d lines containing keyword: %s\n", 
        ID, occurences, args->files[2]); 

    free(line);
    *(args->total) += occurences;
    return NULL;
}

int main(int argc, char** argv) {

    pthread_mutex_init(&mutex, NULL);


    int numThreads = atoi(argv[1]);
    char* keyword = argv[2];
    int numFiles = argc - 3;
    numThreads = numThreads % numFiles; //make sure threads <= files

    int readNum = numFiles / numThreads;
    int startId = 0;
    int total = 0;

    pthread_t* threads = malloc(sizeof(pthread_t) * (numThreads - 1));

        
    struct scanFileArgs args;

    args.files = argv;
    args.numFiles = readNum;
    args.ID = startId;
    args.total = &total;
    
    
    struct timeval start, end;

    gettimeofday(&start, 0);

    printf("searching %d files for keyword: %s \n", numFiles, keyword);

    for (int i = 0; i < numThreads - 1; i++) {
        pthread_create(&threads[i], NULL, scanFiles, &args);
    }

    for (int i = 0; i < numThreads - 1; i++) {
        pthread_join(threads[i], NULL);
    }

    args.numFiles = argc - ((args.ID * args.numFiles) + 3);
    scanFiles(&args);
    
    gettimeofday(&end, 0);

    printf("Total occurances: %d\n", total);

    float elapsedTime = ((end.tv_sec * 1000000) + (end.tv_usec) - 
        ((start.tv_sec * 1000000) + (start.tv_usec)));

    elapsedTime = elapsedTime / 1000000;

    printf("Elapsed time is %f\n", elapsedTime);

    free(threads);
    return 0;
}
