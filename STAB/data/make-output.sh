#!/bin/bash

g++ ../solutions/junhua-full.cpp -o sol -O2

for x in *.in; do
	./sol < $x > ${x%in}out
done;

