#!/bin/bash

src="$PWD/$1"
app="$PWD/a.out"
input="$PWD/$2"

if [ ! -f "$src" ]; then
	echo "$src does not exist. Please try again"
	exit 1
fi

echo "Compiling file $1..."

if [ -f "$app" ]; then
	rm $app
fi

g++ -std=c++17 -O2 -Wall -Wshadow $src

if [ ! -f "$app" ]; then
	echo "Execution failed!"
	exit 1
fi

time $app < $input
