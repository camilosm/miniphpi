#!/bin/bash

red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`

cases=()

clear
for n in {1..15}; do
    source=case${n}-*.mphp;
    input=case${n}-*.in;
    output=case${n}-*.out;

    executed=$(timeout 5 ../mphpi ${source} < $input 2>/dev/null)
	difference=$(diff <(echo "$executed") <(cat ${output}))
	if [ $? -eq 0 ]
		then
			echo "Case $n: ${green}passed${reset}"
		else
			echo "Case $n: ${red}failed${reset}"
			echo "--- Expected output ---";
			cat ${output};
			echo "--- Executed output ---";
			(timeout 1 ../mphpi ${source} < $input);
	fi
	echo ""
done
