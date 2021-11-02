#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <stdio.h>

int main(int argc, char *argv[]) {
	printf("%s\n", argv[1]);
	key_t key = ftok(argv[1], 0);
	int shm_id = shmget(key, 4*sizeof(int), IPC_CREAT | 0666);
	if (shm_id < 0) {
    		printf("shmget error\n");
     		return 0;
	}
	printf("%d\n", shm_id);
}
