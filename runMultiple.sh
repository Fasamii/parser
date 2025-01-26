#!/bin/bash

ninja

if [ "$#" -eq 1 ]; then 
	target=$1
else
	target=5
fi


iteration=0
while [ "$iteration" -lt "$target" ];
do
	echo -en '\e[38;5;33m|=============================|\e[0m\n'
	./alloy ../example
	iteration=$((iteration + 1))
done
