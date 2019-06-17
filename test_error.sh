#!/bin/bash

OUTPUT_DIR="test_output"
SEPARATOR="########################################"
MAPS_DIR="map_samples"
EXE="./lem-in"
TMP=""
LEAKS=$([[ $1 = "leaks" ]] && echo "1" || echo "0")
LEAKS_FOUND=0
FILES_LIST=()
OVERRIDE=-1

readonly GREEN="\e[92m"
readonly RED="\e[31m"
readonly CLR="\e[0;m"
readonly ORANGE="\e[38;5;208m"

function prompt_override() {
	read -p "Some files already exists, override ?" yn
	case $yn in
		[Yy]* ) echo 1; return;;
		[Nn]* ) echo 0; return;;
	esac
}

function get_files_to_process () {
	for dir in $1/*; do
		if [[ -d $dir ]]; then
			outputFile="${dir##*/}"
			if [[ -e "$OUTPUT_DIR/$outputFile.txt" && $OVERRIDE == -1 ]]; then
				OVERRIDE=$(prompt_override)
			fi
			if [[ -e "$OUTPUT_DIR/$outputFile.txt" && $OVERRIDE == 1 ]]; then
				printf "" > $OUTPUT_DIR/$outputFile.txt
				FILES_LIST+=($outputFile)
			elif [[ ! -e "$OUTPUT_DIR/$outputFile.txt" ]]; then
				FILES_LIST+=($outputFile)
			fi
		fi
	done
}

function test_each_file_in_dir () {
	output=$OUTPUT_DIR/$1.txt
	for file in $MAPS_DIR/$dir/*; do
		printf "[ ${file##*/} ] :\n\n" >> "${output}"
		result=$(sh run.sh $file 2>&1)
		exit_status=$(echo $?)
		if (( $exit_status == 0 )); then
			printf "${GREEN}OK\n${CLR}" >> "${output}"
		else
			echo -e "$result" >> "${output}"
			ERROR_STATUS=1
		fi;
		echo -e "\n$SEPARATOR\n\n" >> "${output}"
	done;
	if (( $ERROR_STATUS == 1 )); then
		ERROR_STATUS=0
		printf "${RED}\t\tErrors found\n${CLR}"
	else
		printf "${GREEN}\t\tOK\n${CLR}"
	fi;

}

if [ ! -e $OUTPUT_DIR ]; then
	mkdir $OUTPUT_DIR
fi

get_files_to_process $MAPS_DIR

if [ $? -ne 0 ]; then
	exit 1
fi

for dir in "${FILES_LIST[@]}"; do
	printf "Processing $dir : "
	test_each_file_in_dir $dir
done
