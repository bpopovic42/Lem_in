#!/bin/bash

TEST_OUT_DIR="test_output"
MAP_DIR="map_samples"
EXE="lem-in"

if [ ! -e $EXE ]; then
	make
	if [ $? -ne 0 ]; then
		exit 1
	fi
fi

for dir in $MAP_DIR/*; do
	outputFile="${dir##*/}";
	if [ -e "$TEST_OUT_DIR/$outputFile.txt" ]; then
		read -p "File $outputFile.txt already exists, overwrite ?" yn
		case $yn in
			[Yy]* ) printf "" > $TEST_OUT_DIR/$outputFile.txt;;
			[Nn]* ) exit;;
		esac
	fi;
	for file in $dir/*; do
		echo "[ ${file##*/} ] :" >> $TEST_OUT_DIR/$outputFile.txt
		result=$(eval ./$EXE < $file 2>&1 | cat)
		echo $result >> $TEST_OUT_DIR/$outputFile.txt 2>&1
		printf "***************************************\n" >> $TEST_OUT_DIR/$outputFile.txt
	done;
done

