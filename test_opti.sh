#!/bin/bash
# IF ARGS get args
# IF ARGS == folder; read from folder
# ELIF ARGS = record + folder; record tests in new folder
OUTPUT_DIR=""
INPUT_DIR=""
EXE="lem-in"
GENERATOR_ARG="--big-superposition"
TEST_AMOUNT=1
OUT_FILES_PREFIX="test_"
OUT_FILES_SUFFIX=".map"
AVG_FILENAME=".avg"
TIME_AVG_PATTERN="TIME_AVG"
RESULT_AVG_PATTERN="RESULT_AVG"
GENERATOR_NAME="generator"

readonly GREEN="\e[92m"
readonly RED="\e[31m"
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
		printf " (input file : %s)" $file
	else
		printf "|% 7s     |" "N/A"
	fi
}

function record_map
{
	result=$1
	input="$2"
	output=$3
	if [[ $OUTPUT_DIR != "" ]]; then
		input_contents="$(echo "$input" | grep -v "#PREVIOUS_RESULT")"
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

function get_output_size
{
	output_size=$((echo "$file_content" | ./$EXE)2>&1)
	output_size=`echo "$output_size" | grep '^L' | wc -l | sed 's/^ *//'`
	echo $output_size
}

function run_from_folder
{
	print_header
	for file in $INPUT_DIR/*; do
		output_file=$file
		target_solution="$(grep -m 1 '#Here is the number*' $file | awk 'NF>1{print $NF}')"
		if [[ $target_solution != "" ]]; then
			file_content="$(cat $file)"
			time=$((echo "$file_content" | /usr/bin/time ./$EXE) 2>&1 | grep real | awk '{print $1}')
			solution=$(get_output_size)
			let answer=$solution-$target_solution
			print_formatted_results $time $target_solution $solution $answer $file
			record_map $answer "$file_content" $OUTPUT_DIR/"$(basename $output_file)"
		fi
		((TEST_AMOUNT+=1))
	done
}

function run_from_generator
{
	if [[ ! -e $GENERATOR_NAME ]]; then
		echo "Error : couldn't find generator program."
		exit 1
	fi

	print_header
	padding="$(echo -n $TEST_AMOUNT | wc -c | sed 's/ //g')"
	for (( i = 1; i < $TEST_AMOUNT+1; i++ )) do
		formatted_index="$(printf "%.${padding}d" $i)"
		output_file="$OUT_FILES_PREFIX$formatted_index$OUT_FILES_SUFFIX"
		file_content=$(./$GENERATOR_NAME $GENERATOR_ARG)
		target_solution="$(echo $file_content | grep -m 1 '#Here is the number*' | awk 'NF>1{print $NF}')"
		time=$((echo "$file_content" | /usr/bin/time ./$EXE) 2>&1 | grep real | awk '{print $1}')
		solution=$(get_output_size)
		let answer=$solution-$target_solution
		print_formatted_results $time $target_solution $solution $answer $output_file
		results_sum="$(echo ${results_sum}+\(${solution}-${target_solution}\) | bc -l)"
		time_sum="$(echo ${time_sum}+${time} | bc -l | awk '{printf "%.2f", $0}')"
		record_map $answer "$file_content" $OUTPUT_DIR/$output_file
		wait_for_next_generator_seed $time
	done
}

function print_avg
{
	printf "|    average time : "
	if (( $(echo "$time_avg < 1.0" | bc -l) )); then
		printf "${GREEN}"
	elif (( $(echo "$time_avg < 3.0" | bc -l) )); then
		printf "${ORANGE}"
	else
		printf "${RED}"
	fi
	printf "%s" $time_avg
	printf "${CLR}"
	printf "    |"

	printf "   average result : "
	if (( $(echo "$results_avg < 1.0" | bc -l) )); then
		printf "${GREEN}"
	elif (( $(echo "$results_avg < 6.0" | bc -l) )); then
		printf "${ORANGE}"
	else
		printf "${RED}"
	fi
	printf "%-9s" $results_avg
	printf "${CLR}"
	printf "|\n"
}

function print_previous_avg
{
	avg_file_contents=$(cat ${INPUT_DIR}/${AVG_FILENAME})
	previous_time_avg=$(echo "$avg_file_contents" | grep "$TIME_AVG_PATTERN=.*" | sed "s/${TIME_AVG_PATTERN}=//g")
	previous_result_avg=$(echo "$avg_file_contents" | grep "$RESULT_AVG_PATTERN=.*" | sed "s/${RESULT_AVG_PATTERN}=//g")
	time_avg_diff="$(echo ${time_avg}- ${previous_time_avg} | bc -l | awk '{printf "%.2f", $0}')"
	results_avg_diff="$(echo ${results_avg}- ${previous_result_avg} | bc -l | awk '{printf "%.2f", $0}')"

	printf "|    previous : "
	if (( $(echo "$time_avg_diff <= -0.25" | bc -l) )); then
		printf "${GREEN}"
	elif (( $(echo "$time_avg_diff <= 0.25" | bc -l) )); then
		printf ""
	elif (( $(echo "$time_avg_diff <= 0.75" | bc -l) )); then
		printf "${ORANGE}"
	else
		printf "${RED}"
	fi
	printf "%-8s" $time_avg_diff
	printf "${CLR}"
	printf "    |"

	printf "   previous : "
	if (( $(echo "$results_avg_diff <= -0.25" | bc -l) )); then
		printf "${GREEN}"
	elif (( $(echo "$results_avg_diff <= 0.25" | bc -l) )); then
		printf ""
	elif (( $(echo "$results_avg_diff <= 0.55" | bc -l) )); then
		printf "${ORANGE}"
	else
		printf "${RED}"
	fi
	printf "%-15s" $results_avg_diff
	printf "${CLR}"
	printf "|\n"

}

function print_footer
{
	echo "|---------------------------------------------------------|"
	print_avg
	if [[ $INPUT_DIR != "" && -e $INPUT_DIR/$AVG_FILENAME ]]; then
		print_previous_avg
	fi
	echo " ---------------------------------------------------------"
}

function dump_avg
{
	printf "$TIME_AVG_PATTERN=$time_avg\n$RESULT_AVG_PATTERN=$results_avg" > $OUTPUT_DIR/$AVG_FILENAME
}

get_cmdl_options $@

if [[ ! -e $EXE ]]; then
	make
fi


time_sum=0
time_avg=0
results_sum=0
results_avg=0

if [[ $INPUT_DIR == "" ]]; then
	run_from_generator
elif [[ $INPUT_DIR != "" ]]; then
	run_from_folder
fi

time_avg="$(echo ${time_sum}/${TEST_AMOUNT} | bc -l | awk '{printf "%.2f", $0}')"
results_avg="$(echo ${results_sum}/${TEST_AMOUNT} | bc -l | awk '{printf "%.2f", $0}')"

if [[ $OUTPUT_DIR != "" ]]; then
	dump_avg
fi

print_footer
