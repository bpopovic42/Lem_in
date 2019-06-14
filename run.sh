#!/bin/bash

TARGET="lem-in"
OPTIONS="$1"

if [[ $OPTIONS != "" ]]; then
	ASAN_OPTIONS=detect_leaks=1 ./$TARGET < $OPTIONS
else
	exit 1
fi
