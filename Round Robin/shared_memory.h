//
// Created by root on 02/11/21.
//

#ifndef OS_SHARED_MEMORY_H
#define OS_SHARED_MEMORY_H


#include <stdbool.h>


//attach a shared memory block
//associated with filename
//create it if it doesnt exist

char *attach_memory_block(char *filename, int size);

bool detach_memory_block(char *block);

bool destroy_memory_block(char *filename);

//all programs will share values below
#define BLOCK_SIZE 4096
#define  BLOCK_SIZE 4096
//#define FILENAME "writeshmem.c"

#endif //OS_SHARED_MEMORY_H