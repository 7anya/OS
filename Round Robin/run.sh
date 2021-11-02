#!/bin/bash

gcc -pthread c3.c -o c3
gcc -pthread c2.c -o c2
gcc -pthread c1.c -o c1
gcc main.c -o main 
./main