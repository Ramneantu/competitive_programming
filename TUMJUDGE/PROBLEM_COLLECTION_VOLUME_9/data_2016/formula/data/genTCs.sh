#!/bin/bash

g++ generateTC.cpp -o tcgen
g++ ../submissions/accepted/gregor_maxoutput.cpp -o sol

for ((i = 1000; i < 1020; i++)) ;
do
	echo $i | ./tcgen > secret/random$i.in
	cat secret/random$i.in | ./sol > secret/random$i.ans
done

rm tcgen
rm sol
