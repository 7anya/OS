//
// Created by tokoyama on 02/11/21.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "shared_memory.h"
#include <stdbool.h>
#include <time.h>

char *to_string(int x) {
    int length = snprintf(NULL, 0, "%d", x);
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", x);
    return str;
}

void runC1(int fd[2], int n1) {
    char *args[] = {"/c1", to_string(n1), to_string(fd[0]), to_string(fd[1]), NULL};
    execv("c1", args);
}

void runC2(int fd[2], int n2) {
    char *args[] = {"/c2", to_string(n2), to_string(fd[0]), to_string(fd[1]), NULL};
    execv("c2", args);
}

void runC3(int fd[2], int n3) {
    char *args[] = {"/c3", to_string(n3), to_string(fd[0]), to_string(fd[1]), NULL};
    execv("c3", args);
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

//char *readFromSharedMemory(char *filename) {
//
//    char *block = attach_memory_block(filename, BLOCK_SIZE);
//    if (block == NULL) {
//        printf("ERROR couldnt get block \n");
//        return -1;
//    }
//    printf("Reading:%s\n", block);
//
//    detach_memory_block(block);
//    return block;
//}

void writeToSharedMemoryOf(char name[3], char *data) {
    if (strcmp(name, "c1") == 0) {
        writeToSharedMemory("sharedMemoryC1.c", data);

    } else if (strcmp(name, "c2") == 0) {
        writeToSharedMemory("sharedMemoryC2.c", data);

    } else
        writeToSharedMemory("sharedMemoryC3.c", data);
}


//void readFromSharedMemoryOf(char name[3]) {
//    if (strcmp(name, "c1") == 0) {
//        readFromSharedMemory("sharedMemC1.c", data);
//
//    } else if (strcmpi(name, "c2") == 0) {
//        readFromSharedMemory("sharedMemC2.c", data);
//
//    } else
//        readFromSharedMemory("sharedMemC3.c", data);
//}
int main(int argc, char *argv[]) {
    int fd_c1[2];
    int fd_c3[2];
    int fd_c2[2];
    int n1, n2, n3;
    printf("Enter n1,n2,n3:");
    scanf("%d %d %d", &n1, &n2, &n3);
    int timeQuantum;
    printf("Input time quantum in nano seconds");
    scanf("%d", &timeQuantum);
    pid_t id= fork();

    if(id==0)
    {
        char *args[] = {"/setup", to_string(n1), to_string(n2), to_string(n3), to_string(fd_c1[0]), to_string(fd_c1[1]),to_string(fd_c2[0]), to_string(fd_c2[1]),to_string(fd_c3[0]), to_string(fd_c3[1]) NULL};
        execv("setup", args);
    }
    if (pipe(fd_c1) == -1) {
        printf("error opening pipe");
        return 1;
    }
    if (pipe(fd_c2) == -1) {
        printf("error opening pipe");
        return 1;
    }
    if (pipe(fd_c3) == -1) {
        printf("error opening pipe");
        return 1;
    }
    int count = 0;
    memset(isvalid, true, sizeof(isvalid));
    //Round robing scheduling of proecesses
    writeToSharedMemoryOf("c1", "0");
    writeToSharedMemoryOf("c2", "0");
    writeToSharedMemoryOf("c3", "0");
    while (1) {
        if (count % 3 == 0) {
            if (!isvalid[count % 3])
                continue;
            writeToSharedMemoryOf("c1", "1");
            writeToSharedMemoryOf("c2", "0");
            writeToSharedMemoryOf("c3", "0");
            nanosleep((const struct timespec[]) {{0, timeQuantum}}, NULL);
            writeToSharedMemoryOf("c1", "0");
            writeToSharedMemoryOf("c2", "0");
            writeToSharedMemoryOf("c3", "0");
        } else if (count % 3 == 1) {
            if (!isvalid[count % 3])
                continue;
            writeToSharedMemoryOf("c1", "0");
            writeToSharedMemoryOf("c2", "1");
            writeToSharedMemoryOf("c3", "0");
            nanosleep((const struct timespec[]) {{0, timeQuantum}}, NULL);
            writeToSharedMemoryOf("c1", "0");
            writeToSharedMemoryOf("c2", "0");
            writeToSharedMemoryOf("c3", "0");
        } else {
            if (!isvalid[count % 3])
                continue;
            writeToSharedMemoryOf("c1", "0");
            writeToSharedMemoryOf("c2", "0");
            writeToSharedMemoryOf("c3", "1");
            nanosleep((const struct timespec[]) {{0, timeQuantum}}, NULL);
            writeToSharedMemoryOf("c1", "0");
            writeToSharedMemoryOf("c2", "0");
            writeToSharedMemoryOf("c3", "0");
        }
        printf("isvalid= %d,%d,%d",isvalid[0],isvalid[1],isvalid[2]);
        if(isvalid[0]==false && isvalid[1]==false && isvalid[2]==false)
        {
            printf("All processes done\n ");
            break;
        }
        count++;
    }
//    runC1() but then after timequantum set shared memeory of C1 to '0' & run runC2(), and after timequantum set c2 shared memory to 0 & run c3
//    , and after a time quantum set shared mem of C3 to 0 and continue with C1
// if one of the processes has already ended, then move on to next process
    return 0;
}