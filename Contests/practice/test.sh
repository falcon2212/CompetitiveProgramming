#!/bin/bash

g++ Solution.cpp -o Solution
g++ Brute.cpp -o Brute

for ((i = 1;i < 10 ;i++)) do
	python2 gen.py > inp.in
	./Solution < inp.in > outSol.in
	./Brute < inp.in > outBrute.in
	if ! cmp -s outSol.in outBrute.in
	then
		echo 'Found failing test!!'
		break
	fi
done
echo 'Correct Answer'
