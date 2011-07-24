#!/bin/bash

arr=(0 0.2785 1.6895 11.9999 12.2785 71.9999 72 72.3492 72.9999 73 73.0135 73.0185 73.8218)

for decimal in "${arr[@]}"; do
	echo -e "$decimal\t\t$(./main.py $decimal)"
done
