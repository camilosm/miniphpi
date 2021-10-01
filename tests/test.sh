#!/bin/bash

cases=()

for n in {1..15}; do

    source=case${n}-*.mphp;
    input=case${n}-*.in;
    output=case${n}-*.out;

	executed=$(timeout 5 ../mphpi ${source} < $input 2>/dev/null)
	diff <(echo "$executed") <(echo "$output") >/dev/null
	if [ $? -eq 0 ]
		then
			cases[$n]="passed"
		else
			cases[$n]="failed"
	fi
done

for case in "${!cases[@]}"; do
	printf "%s -> %s\n" "$case" "${cases[$case]}"
done
