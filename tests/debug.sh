#!/bin/bash

red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`

cases=()

for n in {1..2}; do
    source=case${n}-*.mphp;
    input=case${n}-*.in;
    output=case${n}-*.out;

    executed=$(timeout 1 ../mphpi ${source} < $input 2>&1)
	difference=$(diff <(echo "$executed") <(cat ${output}) >/dev/null 2>/dev/null)
	if [ $? -eq 0 ]
		then
			echo "Case $n: ${green}passed${reset}"
		else
			echo "Case $n: ${red}failed${reset}"
			echo "--- Expected output ---"
			cat ${output}
			echo "--- Executed output ---"
			echo $executed
	fi
	echo ""
done
