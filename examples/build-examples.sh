#!/bin/bash
./clean.sh
mkdir -pv bin
FILES="demo_io demo_iterators hello"
for FILE in $FILES
do
	gcc -o bin/$FILE $FILE.c -ldystring
done
