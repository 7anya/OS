//
// Created by root on 01/11/21.
//

//C1 is a compute-intensive process which adds n1 numbers in the range 1 to 1 million.

#include <stdio.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <stdlib.h>
int n1=1000000;

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
    for(int i=0;i<=n1;i++)
    {
        sum+=i;
    }
//    printf("%lld",sum);

//    sleep(1);
//    printf("Printing GeeksQuiz from Thread \n");
    writeToPipe(fd,sum);
    return NULL;
}

void *monitor(void *vargp){

    // monitor task and communicate with master process

}
int main(int argc,char *argv[])
{
//    printf("arg =%s\n",argv[1]);
    n1=atoi(argv[1]);
    fd[0]=atoi(argv[2]);
    fd[1]=atoi(argv[3]);
//    printf("fd[0]= %d\n",fd[0]);
//    printf("fd[1]= %d\n",fd[1]);
//    printf("n=%d\n",n1);
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