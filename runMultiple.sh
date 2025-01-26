#!/bin/bash

(cd build; ninja)
if [ "$?" -ne 0 ]; then
	exit 1
fi

if [ "$#" -eq 1 ]; then 
	target=$1
else
	target=5
fi

iteration=0
errorCount=0
while [ "$iteration" -lt "$target" ];
do
	echo -en '\e[38;5;33m|==['"$iteration"']===========================|\e[0m\n'
	./build/alloy ./example
	if [ "$?" -ne 0 ]; then
		errorCount=$((errorCount + 1))
	fi
	iteration=$((iteration + 1))
done
if [ "$errorCount" -eq 0 ]; then
	echo -en '\e[38;5;2m'
else 
	echo -en '\e[38;5;1m'
fi
echo -en 'ErrorCount:'"$errorCount"'/'"$target"'\e[0m\n'
