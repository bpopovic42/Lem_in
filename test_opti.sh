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
	file=$1
	new_result=$2
	if [[ -e $file ]]; then
		previous_result="$(grep -m 1 '#PREVIOUS_RESULT*' $file | awk 'NF>1{print $NF}')"
		if [[ $previous_result > $new_result ]]; then
			printf "|${GREEN}% 6d${CLR}      |" $previous_result
		elif [[ $previous_result < $new_result ]]; then
			printf "|${RED}% 6d${CLR}      |" $previous_result
		else
			printf "|% 6d${CLR}      |" $previous_result
		fi
		printf " (file : %s)" $file
	else
		printf "|% 6s      |" "N/A"
		printf " (file : %s)" "N/A"
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
	printf "|"
	if (( $result <= 0 )); then
		printf "${GREEN}"
	elif (( $result < 10 )); then
		printf "${ORANGE}"
	else
		printf "${RED}"
	fi
	printf "% 6d${CLR}" $result
	printf "    "
}

function print_time
{
	time=$1
	printf "|"
	if (( $(echo "$time < 1.0" | bc -l) )); then
		printf "${GREEN}"
	elif (( $(echo "$time < 3.0" | bc -l) )); then
		printf "${ORANGE}"
	else
		printf "${RED}"
	fi
	printf "% 6s" $time
	printf "${CLR}"
	printf "  |"
}

function wait_for_next_generator_seed
{
	time=$1
	if (( $(echo "$time < 1.0" | bc -l) )); then
		sleep $(echo "1.0 - $time" | bc -l)
	fi
}

function print_header
{
	echo " ---------------------------------------------------------"
	printf "|  TIME  |  GENERATOR  |  LEM-IN  |  RESULT  |  PREVIOUS  |\n"
	#echo "|--------|-------------|----------|----------|------------|"
}

function print_formatted_results
{
	timer=$1
	generator=$2
	lemin=$3
	result=$4
	file=$5
	echo "|--------|-------------|----------|----------|------------|"
	print_time $timer
	printf "% 8s     |% 6s    " $generator $lemin
	print_result $result
	print_previous_result $file $result
	echo ""
}

function run_from_folder
{
	for file in $INPUT_DIR/*; do
		output_file=$file
		target_solution="$(grep -m 1 '#Here is the number*' $file | awk 'NF>1{print $NF}')"
		time="$((/usr/bin/time ./$EXE < $file) 2>&1 | grep real | awk '{print $1}')"
		out="$((./$EXE < $file) 2>&1)"
		solution=`echo "${out}" | wc -l | sed 's/^ *//'`
		let answer=$solution-$target_solution
		print_formatted_results $time $target_solution $solution $answer $file
		record_map $answer $file $OUTPUT_DIR/"$(basename $output_file)"
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
		let answer=$solution-$target_solution
		print_formatted_results $time $solution $target_solution $answer
		record_map $answer $TMP_FILE $OUTPUT_DIR/$output_file
		wait_for_next_generator_seed $time
	done
}

get_cmdl_options $@
echo $OUTPUT_DIR

if [[ ! -e $EXE ]]; then
	make
fi

print_header

if [[ $INPUT_DIR == "" ]]; then
	run_from_generator
elif [[ $INPUT_DIR != "" ]]; then
	run_from_folder
fi
echo " ---------------------------------------------------------"
if [[ -e $TMP_FILE ]]; then
	rm -i $TMP_FILE
fi

#time="$((time (./lem-in < big_tmp.txt)) | grep -E real)"
#time=`echo ${lem_in_out} | awk '{print $3}'`
#echo "target = $target_solution, solution = $solution"
