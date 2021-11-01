//
// Created by root on 01/11/21.
//

//C1 is a compute-intensive process which adds n1 numbers in the range 1 to 1 million.

#include <stdio.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <stdlib.h>
void *task(void *vargp)
{
    int n1=1000000;
    long long sum=0;
    for(int i=0;i<n1;i++)
    {
        sum+=i;
    }
    printf("%lld",sum);

//    sleep(1);
//    printf("Printing GeeksQuiz from Thread \n");
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