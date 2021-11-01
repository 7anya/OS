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
void *task(void *vargp)
{
    int n3=5;
    long long sum=0;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char *ptr;
    fp = fopen("numbers.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1 && n3>0) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
        sum+= strtol(line,&ptr,10);
        n3--;
    }
    printf("the sum is :%lld",sum);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
    return NULL;
}
void *monitor(void *vargp){

    // monitor task and communicate with master process

}
int main()
{
    pthread_t thread_id_task, thread_id_monitor;
    printf("Before Thread\n");
    pthread_create(&thread_id_task, NULL, task, NULL);
    pthread_join(thread_id_task, NULL);
    pthread_create(&thread_id_monitor, NULL, monitor, NULL);
    pthread_join(thread_id_monitor, NULL);
    printf("After Thread\n");
    exit(0);
    return 0;
}