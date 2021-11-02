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

    while ((read = getline(&line, &len, fp)) != -1 && n2 > 0) {
//        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
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