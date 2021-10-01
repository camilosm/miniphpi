#!/bin/bash

red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`

cases=()

for n in {1..15}; do

    source=case${n}-*.mphp;
    input=case${n}-*.in;
    output=case${n}-*.out;

	executed=$(timeout 5 ../mphpi ${source} < $input 2>/dev/null)
	diff <(echo "$executed") <(cat ${output}) >/dev/null 2>/dev/null
	if [ $? -eq 0 ]
		then
			cases[$n]="${green}passed${reset}"
		else
			cases[$n]="${red}failed${reset}"
	fi
done

for case in "${!cases[@]}"; do
	printf "%s -> %s\n" "$case" "${cases[$case]}"
done
