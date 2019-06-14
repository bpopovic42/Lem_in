#!/bin/bash

shopt -s expand_aliases
source $HOME/.usr_cfg/mixins/aliases

TARGET="lem-in"
OPTIONS="$1"

if [[ $OPTIONS != "" ]]; then
	mkfsn
	ASAN_OPTIONS=detect_leaks=1 ./$TARGET < $OPTIONS
else
	exit 1
fi
