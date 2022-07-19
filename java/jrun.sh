#!/bin/bash

src="$PWD/$1"
input="$PWD/$2"

if [ ! -f "$src" ]; then
	echo "$src does not exist. Please try again"
	exit 1
fi

echo "Compiling file $1..."

time java $src < $input
