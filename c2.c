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
void *task(void *vargp)
{
    int n2=6;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("numbers.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1 && n2>0) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
        n2--;
    }

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