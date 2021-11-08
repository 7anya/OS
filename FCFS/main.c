//
// Created by tokoyama on 02/11/21.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <malloc.h>

char *to_string(int x) {
    int length = snprintf(NULL, 0, "%d", x);
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", x);
    return str;
}

void runC1(int fd[2], int n1) {
    char *args[] = {"/c1", to_string(n1), to_string(fd[0]), to_string(fd[1]), NULL};
    execv("c1", args);
}

void runC2(int fd[2], int n2) {
    char *args[] = {"/c2", to_string(n2), to_string(fd[0]), to_string(fd[1]), NULL};
    execv("c2", args);
}

void runC3(int fd[2], int n3) {
    char *args[] = {"/c3", to_string(n3), to_string(fd[0]), to_string(fd[1]), NULL};
    execv("c3", args);
}


void c3(int fd_c3[], int n3) {
    int pid_c3 = fork();
    if (pid_c3 == 0) { // child process
//        printf("inside child\n");

        runC3(fd_c3, n3);

    } else {
        wait(NULL);
//        printf("inside parent\n");
        close(fd_c3[1]);
        long long tem;
        read(fd_c3[0], &tem, sizeof(tem));
        printf("read from pipe: %lld\n", tem);
        close(fd_c3[0]);
    }
}

void c2(int fd_c2[], int n2, int fd_c3[], int n3) {

    int pid_c2 = fork();
    if (pid_c2 == 0) { // child process
//            printf("inside child\n");
        runC2(fd_c2, n2);
    } else {
        wait(NULL);
//            printf("inside parent\n");
        close(fd_c2[1]);
        char s[100];
        read(fd_c2[0], &s, sizeof(s));
        printf("read from pipe: %s\n", s);
        close(fd_c2[0]);
        c3(fd_c3, n3);


    }
}

void c1(int fd_c1[], int fd_c2[], int fd_c3[], int n1, int n2, int n3) {
    int pid_c1 = fork();
    if (pid_c1 == 0) { // child process
//        printf("inside child\n");
        runC1(fd_c1, n1);
    } else {
        wait(NULL);
//        printf("inside parent\n");
        close(fd_c1[1]);
        long long t;
        read(fd_c1[0], &t, sizeof(t));
        printf("read from pipe: %lld\n", t);
        close(fd_c1[0]);
        c2(fd_c2, n2, fd_c3, n3);

    }
}


int main(int argc, char *argv[]) {
    int fd_c1[2];
    int fd_c3[2];
    int fd_c2[2];
    int n1, n2, n3;
    printf("Enter n1,n2,n3:");
    scanf("%d %d %d", &n1, &n2, &n3);
    if (pipe(fd_c1) == -1) {
        printf("error opening pipe");
        return 1;
    }
    if (pipe(fd_c2) == -1) {
        printf("error opening pipe");
        return 1;
    }
    if (pipe(fd_c3) == -1) {
        printf("error opening pipe");
        return 1;
    }
    c1(fd_c1, fd_c2, fd_c3, n1, n2, n3);

    return 0;
}