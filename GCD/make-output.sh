#!/bin/bash

g++ sol.cpp -o sol -O2

for x in *.in; do
	cp $x gcd.in
	./sol
	mv gcd.out ${x%in}out
done;

rm gcd.in
rm sol
