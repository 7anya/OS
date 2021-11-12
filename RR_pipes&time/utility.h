#define     BLOCK_SIZE  1
#include <stdbool.h>


int get_shared_block(char* filename, int size);
bool* attach_memory_block(char* filename, int size);
void detach_memory_block(bool* block);
void destroy_memory_block(char* filename);
bool read_from_shared_memory(char* filename);
void write_to_shared_memory(char* filename, bool status);
