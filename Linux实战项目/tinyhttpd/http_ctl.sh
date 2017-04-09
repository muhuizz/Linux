#!/bin/bash


proc=$( basename $0 )
function Usage(){
	printf "%s [start(-s) | stop(-t) | restart(-rt)]\n" "$proc"
}


[[ $# -ne 1 ]] && {
	Usage
	exit 1
}

case $1 in
	'start' | '-s' )
		fun_start
		;;
	'stop' | '-t' )
		fun_stop
		;;
	'restart' | '-rt' )
		fun_stop
		fun_start
		;;
	* )
		echo "default"
		;;
esac





