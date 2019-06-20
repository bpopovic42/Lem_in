#!/bin/bash

shopt -s expand_aliases
source $HOME/.usr_cfg/mixins/aliases
source $HOME/.cfg/mixins/aliases

TARGET="lem-in"
MAP=$1
OPTIONS="${@:2}"

if [[ $MAP == "" ]]; then
	exit 1
fi

if [[ $OPTIONS == "" ]]; then
	mkfsn && ASAN_OPTIONS=detect_leaks=1 ./$TARGET < $MAP
else
	make $OPTIONS && ./$TARGET < $MAP
fi

