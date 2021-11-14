#!/bin/bash

for i in {1..100000..1000}
do
	for j in {1..100000..1000}
	do
		for k in {1..100000..1000}
		do
		ARG1=$i
		ARG2=$j
		ARG3=$k
		sh ./compile.sh $ARG1 $ARG2 $ARG3
		done
	done
done

for i in {100000..1000000..5000}
do
	for j in {100000..1000000..5000}
	do
		for k in {100000..1000000..5000}
		do
		ARG1=$i
		ARG2=$j
		ARG3=$k
		sh ./compile.sh $ARG1 $ARG2 $ARG3
		done
	done
done