#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <stdbool.h>
#include    <stdint.h>
#include    <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include    <unistd.h>
#include    <sys/wait.h>
#include <time.h>
#include <sys/time.h>
#include    "utility.h"

int readDataFromPipe(char* pipename, char *str1){

    int fd1;
    fd1 = open(pipename, O_RDONLY);
    read(fd1, str1, 80);

    // Print the read string and close
    printf("Pipe spits out %s\n", str1);
    close(fd1);
}

int main(int argc, char** argv)
{
    clock_t t;
    t = clock();
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("Master thread starts at %f seconds \n", time_taken);
	char n1[16], n2[16], c2_file[32], n3[16], c3_file[32];
	char str[80];
    int time_quantum;
	printf("N1: ");
	scanf("%s", n1);
	printf("N2: ");
	scanf("%s", n2);
    printf("Filename for C2: ");
    scanf("%s", c2_file);
	printf("N3: ");
	scanf("%s", n3);
    printf("Filename for C3: ");
    scanf("%s", c3_file);    	
    printf("FCFS/RR [1 for FCFS, 2 for RR]: ");
    scanf("%d", &time_quantum);
    if(time_quantum == 1)
    {
        printf("Stub. Unimplemented. Shoo. Go away.\n");
        exit(1);
    }
    printf("Time Quantum for RR in microseconds: ");
    scanf("%d", &time_quantum);

    write_to_shared_memory("c1.c", false);
    write_to_shared_memory("c2.c", false);
    write_to_shared_memory("c3.c", false);        
	t = clock();
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("Child 1 starts at %f seconds \n", time_taken);
	int pid1 = fork();
 
    if (pid1 == 0)
    {
// spawning C1
        execlp("./c1", "./c1", n1, NULL);
    }
    else
    {
    t = clock();
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("Child 2 starts at %f seconds \n", time_taken);
    	
        int pid2 = fork();

        if (pid2 == 0)
        {
// spawning C2
            execlp("./c2", "./c2", n2, c2_file, NULL);
        }
        else
        {
        t = clock();
    	time_taken = ((double)t)/CLOCKS_PER_SEC;
    	printf("Child 3 starts at %f seconds \n", time_taken);
            int pid3 = fork();
        
            if (pid3 == 0)
            {
// spawning C3
                execlp("./c3", "./c3", n3, c3_file, NULL);
            }  
            else
            {
// parent can now setup scheduling.
                for(uint64_t i = 0; i < INT64_MAX; i++)
                {
                    write_to_shared_memory("c1.c", ((i % 3) == 0));
                    write_to_shared_memory("c2.c", ((i % 3) == 1));
                    write_to_shared_memory("c3.c", ((i % 3) == 2));   
                    usleep(time_quantum);                      
                }
                        //uncomment this pipe line @Kevin to begin the reading
                //readDataFromPipe("/tmp/c1Data", str);
                fflush(stdout);
                //readDataFromPipe("/tmp/c2Data", str);
                fflush(stdout);
                //readDataFromPipe("/tmp/c3Data", str);
                fflush(stdout);
            } 
        }
    }
    return 0;
}
