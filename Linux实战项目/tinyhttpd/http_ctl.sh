#!/bin/bash

Path=$(pwd)
BIN=${Path}/httpd
PID=${Path}/httpd.pid
CONF=${Path}/conf/httpd.conf
proc=$( basename $0 )
LIB=${Path}/lib
function Usage(){
	printf "%s [start(-s) | stop(-t) | restart(-rt)]\n" "$proc"
}

function fun_start(){
	[[ -f $PID ]] && {
		printf "httpd is running, pid is $(cat $PID)\n"
		return 
	}
	_ip=$(grep -E "^IP:" $CONF | awk -F: '{print $2}')
	_port=$(grep -E "^PORT:" $CONF | awk -F: '{print $2}')
	${BIN} ${_ip} ${_port}
	pidof $(basename $BIN) > $PID
#	echo ${LIB}
#	export LD_LIBRARY_PATH=${LIB}
#	export | grep "LD"
	printf "httpd start... pid is : $(cat ${PID}) \n"
}

function fun_stop(){
	[[ ! -f ${PID} ]] &&{
		printf "httpd is not start\n"
		return
	}
	pid=$(cat ${PID})
	kill -9 ${pid}
	[[ $? -ne 0 ]] && {
		printf "stop faild\n"
		return
	}
	 
	rm -f ${PID}
	printf "stop done...\n"
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
		Usage
		exit 2
		;;
esac





