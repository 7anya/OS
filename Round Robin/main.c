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
//    int n1, n2, n3;
//    printf("Enter n1,n2,n3:");
//    scanf("%d %d %d", &n1, &n2, &n3);
    int timeQuantum;
//    here we input the time quantum in nano seconds, usually 1-5 nano seconds gives good results

    printf("Input time quantum in nano seconds");
    scanf("%d", &timeQuantum);

    int count = 0;
    memset(isvalid, true, sizeof(isvalid));
    //Round robing scheduling of proecesses

    // we set all the shared memory to 0, indicating not to start any tasks yet and keep them waiting
    writeToSharedMemoryOf("c1", "0");
    writeToSharedMemoryOf("c2", "0");
    writeToSharedMemoryOf("c3", "0");

    // here in a loop we run c1, c2,c3 for one time quantum each
    while (1) {
        if (count % 3 == 0) {
            if (!isvalid[count % 3])
                continue;
            //giving the signal to c1 to wake up and c2,c3 to go to sleep
            writeToSharedMemoryOf("c1", "1");
            writeToSharedMemoryOf("c2", "0");
            writeToSharedMemoryOf("c3", "0");
            nanosleep((const struct timespec[]) {{0, timeQuantum}}, NULL);
            //set all them to sleep and prepare for context switch
            writeToSharedMemoryOf("c1", "0");
            writeToSharedMemoryOf("c2", "0");
            writeToSharedMemoryOf("c3", "0");
        } else if (count % 3 == 1) {
            if (!isvalid[count % 3]) // checks if process is still running or done
                continue;
            // now, shared memory of c1,c3 are set to 0, sleeping them, while c2 wakes up
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
        printf("isvalid= %d,%d,%d", isvalid[0], isvalid[1], isvalid[2]);
        if (isvalid[0] == false && isvalid[1] == false && isvalid[2] == false) {
            printf("All processes done\n "); // this doesnt work yet.
            break;
        }
        count++;
    }
//    runC1() but then after timequantum set shared memeory of C1 to '0' & run runC2(), and after timequantum set c2 shared memory to 0 & run c3
//    , and after a time quantum set shared mem of C3 to 0 and continue with C1
// if one of the processes has already ended, then move on to next process
    return 0;
}