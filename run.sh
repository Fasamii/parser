#!/bin/bash

echo -en '\e[38;5;5m|==[BUILD]===============================|\e[0m\n'
mkdir -p build
(cd build; cmake .. -G Ninja)
if [ "$?" -ne 0 ]; then
	exit 1
fi

(cd build; ninja)
if [ "$?" -ne 0 ]; then
	exit 1
fi
echo -en '\e[38;5;5m|==[BUILD_END]===========================|\e[0m\n'

if [ "$#" -eq 1 ]; then 
	target=$1
else
	target=1
fi

iteration=0
errorCount=0

while [ "$iteration" -lt "$target" ];
do
	echo -en '\e[38;5;33m|==['"$(($iteration + 1))"']===================================|\e[0m\n'
	(./build/alloy ./examples/ehe.al)
	if [ "$?" -ne 0 ]; then
		errorCount=$((errorCount + 1))
	fi
	iteration=$((iteration + 1))
done
echo -en '\e[38;5;33m|==[END]=================================|\e[0m\n'
if [ "$errorCount" -eq 0 ]; then
	echo -en '\e[38;5;2m'
else 
	echo -en '\e[38;5;1m'
fi

echo -en 'ErrorCount:'"$errorCount"'/'"$target"'\e[0m\n'
if [ "$errorCount" -gt 0 ]; then
	exit 1
else
	exit 0
fi
