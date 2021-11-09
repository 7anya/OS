//
// Created by root on 01/11/21.
//

//C1 is a compute-intensive process which adds n1 numbers in the range 1 to 1 million.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shared_memory.h"
#include <stdbool.h>

int n1 = 1000000;
pthread_cond_t condShm;
pthread_mutex_t mutexShm;
int fd[2];
char *block;

char *readFromSharedMemory(char *filename) {

//    this function reads from a shared memory identified by a particular file name and returns the char*
    char *block = attach_memory_block(filename, BLOCK_SIZE);
    if (block == NULL) {
        printf("ERROR couldnt get block \n");
        return NULL;
    }
    printf("30 Reading:%s\n", block);
    char temp[10];
    strcpy(temp, block);
    printf("32 Reading:%s\n", temp);
    detach_memory_block(block);
    printf("333 Reading:%s\n", temp);
    char *t;
    t[0] = temp[0];
    return t;
}


char *readFromSharedMemoryOf(char name[3]) {
    // this is a wrapper function of the above function, this differentiates the locations of all 3 processes' shared memory
    if (strcmp(name, "c1") == 0) {
        char *temp = readFromSharedMemory("sharedMemoryC1.c");
        printf("40 %s\n", temp);
        return temp;

    } else if (strcmp(name, "c2") == 0) {
        return readFromSharedMemory("sharedMemoryC3.c");

    } else
        return readFromSharedMemory("sharedMemoryC3.c");
}


void *task(void *vargp) {
    //this is our main task thread
    printf("in task\n");
//    block = readFromSharedMemoryOf("c1");
    printf("57: %s\n", block);
//    here the mutex is around the shared memory and the cond_wait is triggered whenever
//    the shared memory is not 1, and quits the loop when it becomes 1 thus waking the process up
    pthread_mutex_lock(&mutexShm);
    while (block[0] != '1') {
        printf("C1 is waiting/sleeping\n");
        pthread_cond_wait(&condShm, &mutexShm);
    }
    pthread_mutex_unlock(&mutexShm);

//    printf("57\n");
    long long sum = 0;
    for (int i = 0; i <= n1; i++) {
        sum += i;

        //    here the mutex is around the shared memory and the cond_wait is triggered whenever
        //    the shared memory is not 1, and quits the loop when it becomes 1 thus waking the process up

        pthread_mutex_lock(&mutexShm);

        while (block[0] != '1') {
            printf("C1 is waiting/sleeping\n");
            pthread_cond_signal(&condShm);
//            pthread_mutex_unlock(&mutexShm);
            pthread_cond_wait(&condShm, &mutexShm);
        }
        pthread_mutex_unlock(&mutexShm);
        printf("sum= %lld\n", sum);

    }
    printf("87= %lld\n", sum);
    isvalid[0] = false;
    printf("\nisvalid=%d,%d,%d\n", isvalid[0], isvalid[1], isvalid[2]);


//    writeToPipe(fd, sum);
    return NULL;
}

void *monitor(void *vargp) {
// this is the monitor thread

    printf("in monitor\n");

    while (1) {
        // here again the mutex is around the shared memory pointer,
        // and it signals to the cond-wait that there could be a change in the block value.
        // This loop repeats after 20 nano seconds
        pthread_mutex_lock(&mutexShm);
        block = readFromSharedMemoryOf("c1");
        pthread_cond_signal(&condShm);
        printf("100 hereeee\n");
        pthread_mutex_unlock(&mutexShm);
        usleep(20);
        if (!isvalid[0]) {
            break;
        }

    }
    return NULL;

}

int main(int argc, char *argv[]) {
    printf("enter n1: ");
    scanf("%d",&n1);
//    n1 = atoi(argv[1]);

    block = "0";
    isvalid[0] = 1;
    //thread and mutex housing
    pthread_mutex_init(&mutexShm, NULL);
    pthread_cond_init(&condShm, NULL);
    pthread_t thread_id_task, thread_id_monitor;
    pthread_create(&thread_id_task, NULL, task, NULL);
    pthread_create(&thread_id_monitor, NULL, monitor, NULL);
    pthread_join(thread_id_task, NULL);
    pthread_join(thread_id_monitor, NULL);
    pthread_mutex_destroy(&mutexShm);
    pthread_cond_destroy(&condShm);

    exit(0);
}