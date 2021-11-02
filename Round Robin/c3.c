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
int n3=5;
int fd[2];
void writeToPipe(int fd[2],long long data)
{
    close(fd[0]);
    write(fd[1],&data,sizeof(long long));
    close(fd[1]);
}
void *task(void *vargp)
{

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
//        printf("Retrieved line of length %zu:\n", read);
//        printf("%s", line);
        sum+= strtol(line,&ptr,10);
        n3--;
    }
//    printf("the sum is :%lld",sum);
    writeToPipe(fd,sum);
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
    return NULL;
}
void *monitor(void *vargp){

    // monitor task and communicate with master process

}
int main(int argc,char *argv[])
{
//    printf("arg =%s\n",argv[1]);
    n3=atoi(argv[1]);
    fd[0]=atoi(argv[2]);
    fd[1]=atoi(argv[3]);
//    printf("fd[0]= %d\n",fd[0]);
//    printf("fd[1]= %d\n",fd[1]);
//    printf("n=%d\n",n3);
    pthread_t thread_id_task, thread_id_monitor;
//    printf("Before Thread\n");
    pthread_create(&thread_id_task, NULL, task, NULL);
    pthread_join(thread_id_task, NULL);
    pthread_create(&thread_id_monitor, NULL, monitor, NULL);
    pthread_join(thread_id_monitor, NULL);
//    printf("After Thread\n");
    exit(0);
    return 0;
}