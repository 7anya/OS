#! bin/bash

killall master

rm c1
rm c2
rm c3

rm master

gcc -pthread c1.c utility.c -o c1
gcc -pthread c2.c utility.c -o c2 
gcc -pthread c3.c utility.c -o c3 

gcc -pthread master.c utility.c -o master
./master
