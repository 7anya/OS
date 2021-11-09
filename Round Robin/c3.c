//
// Created by root on 01/11/21.
//

//C3 is both compute and I/O intensive which reads n3 numbers (range from 1 to 1 million) from
//        a text file and adds them up.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shared_memory.h"
int n3=5;
int fd[2];
pthread_cond_t condShm;
pthread_mutex_t mutexShm;
char *block;
char *readFromSharedMemory(char *filename) {

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
    if (strcmp(name, "c1") == 0) {
        char *temp = readFromSharedMemory("sharedMemoryC1.c");
        printf("40 %s\n", temp);
        return temp;

    } else if (strcmp(name, "c2") == 0) {
        return readFromSharedMemory("sharedMemoryC3.c");

    } else
        return readFromSharedMemory("sharedMemoryC3.c");
}

void writeToPipe(int fd[2],long long data)
{
    close(fd[0]);
    write(fd[1],&data,sizeof(long long));
    close(fd[1]);
}
void *task(void *vargp)
{
    printf("in task\n");
//    block = readFromSharedMemoryOf("c1");
    printf("57: %s\n", block);
    pthread_mutex_lock(&mutexShm);
    while (block[0] != '1') {
        printf("C1 is waiting/sleeping\n");
        pthread_cond_wait(&condShm, &mutexShm);
    }
    pthread_mutex_unlock(&mutexShm);
    long long sum=0;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char *ptr;
    fp = fopen("numbers.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
//    while(*block!='1')
//    {
//        printf("C3 is waiting/sleeping\n")
//        pthread_cond_wait(condShm,mutexShm);
//    }
    while ((read = getline(&line, &len, fp)) != -1 && n3>0) {
//        printf("Retrieved line of length %zu:\n", read);
//        printf("%s", line);
        sum+= strtol(line,&ptr,10);
        pthread_mutex_lock(&mutexShm);

        while (block[0] != '1') {
            printf("C3 is waiting/sleeping\n");
            pthread_cond_signal(&condShm);
//            pthread_mutex_unlock(&mutexShm);
            pthread_cond_wait(&condShm, &mutexShm);
        }
        pthread_mutex_unlock(&mutexShm);
        n3--;
    }
    printf("the sum is :%lld",sum);
    writeToPipe(fd,sum);
    fclose(fp);
    if (line)
        free(line);
    isvalid[2]=false;
    printf("\nisvalid=%d,%d,%d\n",isvalid[0],isvalid[1],isvalid[2]);


    exit(EXIT_SUCCESS);
    return NULL;
}
void *monitor(void *vargp){

    //Lets read from shrared memeory of C1;
//    every iterval do this
    printf("in monitor\n");

    while (1) {
        pthread_mutex_lock(&mutexShm);
        block = readFromSharedMemoryOf("c3");
        pthread_cond_signal(&condShm);
        printf("100 hereeee\n");
        pthread_mutex_unlock(&mutexShm);
        usleep(20);
        if(!isvalid[2])
        {
            break;
        }


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
int main(int argc,char *argv[])
{
//    printf("arg =%s\n",argv[1]);
    printf("enter n3: ");
    scanf("%d",&n3);
//    n3=atoi(argv[1]);

    block="0";
    isvalid[2]=1;

//    printf("fd[0]= %d\n",fd[0]);
//    printf("fd[1]= %d\n",fd[1]);
//    printf("n=%d\n",n2);
//    printf("fd[0]= %d\n",fd[0]);
//    printf("fd[1]= %d\n",fd[1]);
//    printf("n=%d\n",n1);

    pthread_mutex_init(&mutexShm, NULL);
    pthread_cond_init(&condShm, NULL);
    pthread_t thread_id_task, thread_id_monitor;
//    printf("Before Thread\n");
    pthread_create(&thread_id_task, NULL, task, NULL);
    pthread_create(&thread_id_monitor, NULL, monitor, NULL);
    pthread_join(thread_id_task, NULL);
    pthread_join(thread_id_monitor, NULL);


    pthread_mutex_destroy(&mutexShm);
    pthread_cond_destroy(&condShm);
//    printf("After Thread\n");
    exit(0);
    return 0;
}