//
// Created by root on 01/11/21.
//

//C2 is an I/O intensive process which reads n2 numbers (range from 1 to 1 million) from a text
//        file and prints them to the console. Assume that each number is present in a separate line in the
//file. After printing all the numbers, C2 sends the message “Done Printing” to M using a
//pipe.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

int n2 = 6;
int fd[2];
pthread_cond_t condShm;
pthread_mutex_t mutexShm;
char *block;

char *readFromSharedMemory(char *filename) {

    char *block = attach_memory_block(filename, BLOCK_SIZE);
    if (block == NULL) {
        printf("ERROR couldnt get block \n");
        return -1;
    }
    printf("Reading:%s\n", block);

    detach_memory_block(block);
    return block;
}


char *readFromSharedMemoryOf(char name[3]) {
    if (strcmp(name, "c1") == 0) {
        return readFromSharedMemory("sharedMemC1.c");

    } else if (strcmpi(name, "c2") == 0) {
        return readFromSharedMemory("sharedMemC2.c");

    } else
        return readFromSharedMemory("sharedMemC3.c");
}

void writeToPipe(int fd[2]) {
    char data[] = "DONE PRINTING";
    close(fd[0]);
    write(fd[1], &data, sizeof(data));
    close(fd[1]);
}

void *task(void *vargp) {

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("numbers.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    while (*block != '1') {
        printf("C2 is waiting/sleeping\n")
        pthread_cond_wait(condShm, mutexShm);
    }
    while ((read = getline(&line, &len, fp)) != -1 && n2 > 0) {
//        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
        while (*block != '1') {
            printf("C2 is waiting/sleeping\n")
            pthread_cond_wait(condShm, mutexShm);
        }
        n2--;
    }
    writeToPipe(fd);
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
    return NULL;
}

void *monitor(void *vargp) {


    //Lets read from shrared memeory of C1;
//    every iterval do this
    while (1) {
        block = readFromSharedMemoryOf("c2");
        pthread_cond_signal(condShm);
    }

//    pthread_mutex_lock(&mutexShm);
//
//    pthread_mutex_unlock(&mutexShm);
    // checks from shared memeory if its 1, then lets task thread continue or otherwise sleeps it;

    // how to put thread to sleep and wake up;
    //have a conditional variable, whenever this conditional variable is 1, then cool, othwrwise call cond_wait.
//    conditional variable shoud get its value from shared memeory.
// So, step, check shared memeory after every interval, and attach mutex lock to conditional variable, conditonal variable
// call thread_signal from monitor thread;
// if value is 0, then call thread_cond_wait. from inside tast
//
    // monitor task and communicate with master process


}

int main(int argc, char *argv[]) {
//    printf("arg =%s\n",argv[1]);
    n2 = atoi(argv[1]);
    fd[0] = atoi(argv[2]);
    fd[1] = atoi(argv[3]);
//    printf("fd[0]= %d\n",fd[0]);
//    printf("fd[1]= %d\n",fd[1]);
//    printf("n=%d\n",n2);
    printf("n=%d\n", n1);
    pthread_mutex_init(&mutexShm, NULL);
    pthread_cond_init(&condShm, NULL);
    pthread_t thread_id_task, thread_id_monitor;
//    printf("Before Thread\n");
    pthread_create(&thread_id_task, NULL, task, NULL);
    pthread_join(thread_id_task, NULL);
    pthread_create(&thread_id_monitor, NULL, monitor, NULL);
    pthread_join(thread_id_monitor, NULL);
//    printf("After Thread\n");
    pthread_mutex_destroy(&mutexShm);
    pthread_cond_destroy(&condShm);
    exit(0);
    return 0;
}