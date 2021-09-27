#!/bin/bash

cases=()

for n in {1..15}; do

    source=case${n}-*.mphp;
    input=case${n}-*.in;
    output=case${n}-*.out;
    
    clear;

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
    cases[$n]=$equal
done

for case in "${!cases[@]}"; do
	printf "%s -> %s\n" "$case" "${cases[$case]}"
done
