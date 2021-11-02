//
// Created by tokoyama on 02/11/21.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <malloc.h>

char * to_string(int x)
{
    int length = snprintf( NULL, 0, "%d", x );
    char* str = malloc( length + 1 );
    snprintf( str, length + 1, "%d", x );
    return str;
}
int main(int argc, char *argv[]){
    int fd[2];
//    fd[0] read end, fd[1] is write end
    if(pipe(fd)==-1){
        printf("error opening pipe");
        return 1;
    }
    int id=fork();
    if(id==0){ // child process
        printf("inside child");
        close(fd[0]);
        int x;
        printf("Input:");
        scanf("%d",&x);
        write(fd[1],&x,sizeof(int));
        close(fd[1]);
        char *args[] = {"/a.out","5", to_string(fd[0]), to_string(fd[1]), NULL};
        execv("a.out", args);

    }
    else{
        wait(NULL);
        printf("inside parent\n");
        close(fd[1]);
        int t;
        read(fd[0],&t,sizeof(int));
        printf("read from pipe: %d",t);
        close(fd[0]);
    }
    return 0;
}