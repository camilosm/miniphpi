#!/bin/bash

cases=()
clear
for n in {1..15}; do
    source=case${n}-*.mphp;
    input=case${n}-*.in;
    output=case${n}-*.out;

    echo "Running: $(basename ${source})";
    echo "--- Test source ---";
    cat ${input};
    echo "=====";

    echo "--- Expected output ---";
    cat ${output};
    echo "--- Executed output ---";
    (timeout 5 ../mphpi ${source} < $input);
    echo "=====";
    read -p "Passed? " equal;
	if [ $equal = "y" ]
		then
    		cases[$n]="passed"
		else
			cases[$n]="failed"
	fi
	clear
done
echo "Results:"
for case in "${!cases[@]}"; do
	printf "%s -> %s\n" "$case" "${cases[$case]}"
done
