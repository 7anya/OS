//
// Created by tokoyama on 09/11/21.
//

#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include "shared_memory.h"


char *to_string(int x) {
    int length = snprintf(NULL, 0, "%d", x);
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", x);
    return str;
}

int writeToSharedMemory(char *filename, char *data) {
    if (data == NULL) {
        printf("nothing to write-ERROR");
        return -1;
    }
    char *block = attach_memory_block(filename, BLOCK_SIZE);
    if (block == NULL) {
        printf("ERROR couldnt get block \n");
        return -1;
    }
    printf("Writing:%s\n", data);
    strncpy(block, data, BLOCK_SIZE);
    detach_memory_block(block);
    return 0;
}


void writeToSharedMemoryOf(char name[3], char *data) {
    if (strcmp(name, "c1") == 0) {
        writeToSharedMemory("sharedMemoryC1.c", data);

    } else if (strcmp(name, "c2") == 0) {
        writeToSharedMemory("sharedMemoryC2.c", data);

    } else
        writeToSharedMemory("sharedMemoryC3.c", data);
}



int main(int argc, char *argv[]) {

    //Round robing scheduling of proecesses
    writeToSharedMemoryOf("c1", "0");
    writeToSharedMemoryOf("c2", "0");
    writeToSharedMemoryOf("c3", "0");


    return 0;
}