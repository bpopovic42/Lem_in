#!/bin/bash
# IF ARGS get args
# IF ARGS == folder; read from folder
# ELIF ARGS = record + folder; record tests in new folder
OUTPUT_DIR=""
INPUT_DIR=""
EXE="lem-in"
GENERATOR_ARG="--big-superposition"
TMP_FILE="big_tmp.map"
TEST_AMOUNT=1
OUT_FILES_PREFIX="test_"
OUT_FILES_SUFFIX=".map"

readonly GREEN="\e[92;m"
readonly RED="\e[31;m"
readonly CLR="\e[0;m"
readonly ORANGE="\e[38;5;208m"

function print_help
{
	echo "OPTIONS: 
		-h : print this message
		-i : specify input directory to read maps
		-o : specify output directory to write maps
		-n : specifies number of executions (default 1)"
}

function get_cmdl_options
{
	while getopts "hi:o:n:" opt; do
		case $opt in
			n)
				TEST_AMOUNT=$OPTARG
				;;
			i)
				INPUT_DIR="$OPTARG"
				if [[ ! -e $INPUT_DIR ]]; then
					echo "$INPUT_DIR not found"
					exit 1
				fi
				;;
			o)
				OUTPUT_DIR="$OPTARG"
				if [[ ! -e $OUTPUT_DIR ]]; then
					echo "/$OUTPUT_DIR not found"
					exit 1
				fi
				;;
			h)
				print_help
				exit 0
				;;
			\?)
				echo "Invalid option: -$OPTARG"
				exit 1
		esac
	done
}

function print_previous_result
{
	new_result=$2
	if [[ -e $1 ]]; then
		previous_result="$(grep -m 1 '#PREVIOUS_RESULT*' $1 | awk 'NF>1{print $NF}')"
		if [[ $previous_result > $new_result ]]; then
			printf "${GREEN}(better than previous : $previous_result)\n${CLR}"
		elif [[ $previous_result < $new_result ]]; then
			printf "${RED}(worst than previous : $previous_result)\n${CLR}"
		else
			printf " (same as previous : $previous_result)\n"
		fi
	fi
}

function record_map
{
	result=$1
	input=$2
	output=$3
	if [[ $OUTPUT_DIR != "" ]]; then
		input_contents="$(cat $input | grep -v "#PREVIOUS_RESULT")"
		echo "#PREVIOUS_RESULT = $result" > $output
		echo "$input_contents" >> $output
	fi
}

function print_result
{
	result=$1
	printf "result = "
	if (( $result <= 0 )); then
		printf "${GREEN}"
	elif (( $result < 10 )); then
		printf "${ORANGE}"
	else
		printf "${RED}"
	fi
	printf "%d${CLR}" $result
}

function print_time
{
	time=$1
	if (( $(echo "$time < 1.0" | bc -l) )); then
		printf "${GREEN}"
	elif (( $(echo "$time < 3.0" | bc -l) )); then
		printf "${ORANGE}"
	else
		printf "${RED}"
	fi
	echo $time
	printf "${CLR}"
}

function wait_for_next_generator_seed
{
	time=$1
	if (( $(echo "$time < 1.0" | bc -l) )); then
		sleep $(echo "1.0 - $time" | bc -l)
	fi
}

function run_from_folder
{
	for file in $INPUT_DIR/*; do
		output_file=$file
		echo "Processing file : $file"
		target_solution="$(grep -m 1 '#Here is the number*' $file | awk 'NF>1{print $NF}')"
		time="$((/usr/bin/time ./$EXE < $file) 2>&1 | grep real | awk '{print $1}')"
		out="$((./$EXE < $file) 2>&1)"
		solution=`echo "${out}" | wc -l | sed 's/^ *//'`
		print_time $time
		echo "$solution - $target_solution"
		let answer=$solution-$target_solution
		print_result $answer
		print_previous_result $file $answer
		record_map $answer $file $OUTPUT_DIR/"$(basename $output_file)"
		echo ""
	done
}

function run_from_generator
{
	for (( i = 0; i < $TEST_AMOUNT; i++ )) do
		output_file="$OUT_FILE_PREFIX$i$OUT_FILE_SUFFIX"
		./generator $GENERATOR_ARG > $TMP_FILE
		target_solution="$(grep -m 1 '#Here is the number*' $TMP_FILE | awk 'NF>1{print $NF}')"
		time="$((/usr/bin/time ./$EXE < $TMP_FILE) 2>&1 | grep real | awk '{print $1}')"
		out="$((./$EXE < $TMP_FILE) 2>&1)"
		solution=`echo "${out}" | wc -l | sed 's/^ *//'`
		print_time $time
		echo "$solution - $target_solution"
		let answer=$solution-$target_solution
		print_result $answer
		record_map $answer $TMP_FILE $OUTPUT_DIR/$output_file
		echo ""
		echo ""
		wait_for_next_generator_seed $time
	done
}

get_cmdl_options $@
echo $OUTPUT_DIR

if [[ ! -e $EXE ]]; then
	make
fi

if [[ $INPUT_DIR == "" ]]; then
	run_from_generator
elif [[ $INPUT_DIR != "" ]]; then
	run_from_folder
fi

if [[ -e $TMP_FILE ]]; then
	rm -i $TMP_FILE
fi

#time="$((time (./lem-in < big_tmp.txt)) | grep -E real)"
#time=`echo ${lem_in_out} | awk '{print $3}'`
#echo "target = $target_solution, solution = $solution"
