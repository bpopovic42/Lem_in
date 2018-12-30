#!/bin/bash

OUTPUT_DIR="test_output"
SEPARATOR="########################################"
MAPS_DIR="map_samples"
EXE="lem-in"
TMP=""
LEAKS=$([[ $1 = "leaks" ]] && echo "1" || echo "0")
FILES_LIST=()

function ask_overwrite_file () {
	read -p "File $1.txt already exists, overwrite ?" yn
	case $yn in
		[Yy]* ) echo 1; return;;
		[Nn]* ) echo 0; return;;
	esac
}

function get_files_to_process () {
	for file in $1/*; do
		outputFile="${file##*/}";
		if [ -e "$OUTPUT_DIR/$outputFile.txt" ]; then
			if [ "$(ask_overwrite_file $outputFile)" == "1" ]; then
				printf "" > $OUTPUT_DIR/$outputFile.txt;
				FILES_LIST+=($outputFile)
			fi
		else
			FILES_LIST+=($outputFile)
		fi
	done
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
	output=$OUTPUT_DIR/$1.txt
	for file in $MAPS_DIR/$dir/*; do
		printf "[ ${file##*/} ] :\n\n" >> $output
		result=$(eval ./$EXE < $file 2>&1 | cat)
		echo -e "$result\n" >> $output 2>&1
		check_leaks $file $output
		echo -e "$SEPARATOR\n\n" >> $output
	done;
}

if [ ! -e $OUTPUT_DIR ]; then
	mkdir $OUTPUT_DIR
fi

if [ $LEAKS == 1 ]; then
	make re DEBUG=-g
elif [ ! -e $EXE ]; then
	make DEBUG=-g
	if [ $? -ne 0 ]; then
		exit 1
	fi
fi

get_files_to_process $MAPS_DIR
for dir in "${FILES_LIST[@]}"; do
	echo Processing $dir...
	test_each_file_in_dir $dir
done

