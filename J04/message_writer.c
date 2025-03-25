#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct metadata {

float version;
unsigned int year;
unsigned int length;

};


void writeBin(const char* filename) {
    
    FILE* writeTo = fopen(filename, "wb");
    const char* comment = "#This is a comment\n";
    const char* message = "This is the message";
    struct metadata* meta = malloc(sizeof(struct metadata));
    meta->version = 1.0;
    meta->year = 2025;
    meta->length = 20;
    fwrite(comment, sizeof(char), strlen(comment), writeTo); 
    fwrite(meta, sizeof(struct metadata), 1, writeTo);
    fwrite(message, sizeof(char), meta->length, writeTo);
    free(meta);
    fclose(writeTo);
}

int main(int arg, char** argv) {
    writeBin(argv[1]);
}
     
