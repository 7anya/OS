#!/bin/bash

gcc -pthread c3.c shared_memory.c -o c3
gcc -pthread c2.c shared_memory.c -o c2
gcc -pthread c1.c shared_memory.c -o c1
gcc main.c shared_memory.c -o main
./main