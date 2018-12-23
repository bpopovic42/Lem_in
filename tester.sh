#!/bin/bash

TEST_OUT_DIR="test_output"
SEPARATOR="########################################"
MAP_DIR="map_samples"
EXE="lem-in"
TMP=""
LEAKS=$([[ $1 = "leaks" ]] && echo "1" || echo "0")

function overwrite_if_file_exists () {
	if [ -e "$TEST_OUT_DIR/$outputFile.txt" ]; then
		read -p "File $1.txt already exists, overwrite ?" yn
		case $yn in
			[Yy]* ) printf "" > $TEST_OUT_DIR/$1.txt;;
			[Nn]* ) exit;;
		esac
	fi;
}

function check_leaks () {
	file="$1"
	output="$2"
	if [ $LEAKS == 1 ]; then
		vg=$(valgrind --leak-check=full ./$EXE < $file 2>&1)
		vg=$(echo "$vg" | grep -A1 "definitely lost:" | cut -c 14-)
		has_leaks=$(printf "$vg" | sed "s/[^0-9]//g")
		has_leaks=$(echo $has_leaks | sed 's/ //g')
		if [ ! "$has_leaks" == "0000" ]; then
			echo -e "LEAKS :\n$vg\n" >> $output
		fi;
	fi;
}

function test_each_file_in_dir () {
	output="$TEST_OUT_DIR/$2.txt"
	for file in $1/*; do
		printf "[ ${file##*/} ] :\n\n" >> $output
		result=$(eval ./$EXE < $file 2>&1 | cat)
		echo -e "$result\n" >> $output 2>&1
		check_leaks $file $output
		echo -e "$SEPARATOR\n\n" >> $output
	done;
}

if [ ! -e $TEST_OUT_DIR ]; then
	mkdir $TEST_OUT_DIR
fi

if [ $LEAKS == 1 ]; then
	make re DEBUG=-g
elif [ ! -e $EXE ]; then
	make DEBUG=-g
	if [ $? -ne 0 ]; then
		exit 1
	fi
fi

for dir in $MAP_DIR/*; do
	outputFile="${dir##*/}";
	overwrite_if_file_exists $outputFile
	test_each_file_in_dir $dir $outputFile
done

