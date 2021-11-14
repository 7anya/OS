#!/bin/bash

for i in {30025..100000..10000}
do
	for j in {25..100000..10000}
	do
		for k in {25..100000..10000}
		do
		ARG1=$i
		ARG2=$j
		ARG3=$k
		sh ./compile.sh $ARG1 $ARG2 $ARG3
		done
	done
done

for i in {100000..1000000..50000}
do
	for j in {100000..1000000..50000}
	do
		for k in {100000..1000000..50000}
		do
		ARG1=$i
		ARG2=$j
		ARG3=$k
		sh ./compile.sh $ARG1 $ARG2 $ARG3
		done
	done
done
