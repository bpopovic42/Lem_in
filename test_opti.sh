#!/bin/bash
read -p "Provide amount of tests to perform. " test_amount
for (( i = 0; i < $test_amount; i++ )) do
	./generator --big-superposition > big_tmp.txt
	target_solution="$(grep -m 1 '#Here is the number*' big_tmp.txt | awk 'NF>1{print $NF}')"
	out="$((./lem-in < big_tmp.txt) 2>&1)"
	solution=`echo "${out}" | wc -l | sed 's/^ *//'`
	#time="$((time (./lem-in < big_tmp.txt)) | grep -E real)"
	#time=`echo ${lem_in_out} | awk '{print $3}'`
	#echo "target = $target_solution, solution = $solution"
	echo "$solution - $target_solution"
	let answer=$solution-$target_solution
	echo "result = $answer" #" ; time = $time"
done
