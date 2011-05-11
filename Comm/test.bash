#!/bin/bash

while [[ 1 ]]; do
	for (( i = 0; i < $((RANDOM % 21)); i +=1  )) do
		echo $((RANDOM % 10))
	done | sort > '1'

	for (( i = 0; i < $((RANDOM % 21)); i +=1  )) do
		echo $((RANDOM % 10))
	done | sort > '2'

	if [[ $(comm '1' '2') != $(./comm) ]]; then
		break
	fi
done
