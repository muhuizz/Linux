#!/bin/bash

ROOT_PATH=$(pwd)
SERVER_BIN=${ROOT_PATH}/udpserver
conf_file=${ROOT_PATH}/conf/server.conf

proc=$(basename $0)
function usage()
{
	printf "Usage# %s [-s(start) | -t(stop) | -rt(restart)]\n" "$proc"
}

function serverStart()
{
	name=$(basename $SERVER_BIN)
	pid=`pidof $name`
	if [ $? -eq 0 ]; then
		echo "udpserver is already running!,pid is %s" "$pid"
	else
		ip=$(awk -F: '/^IP/{print $NF}' ${conf_file})
		port=$(awk -F: '/^PORT/{print $NF}' ${conf_file})
		${SERVER_BIN} $ip $port
	fi
}

function serverStop()
{
	:
}

function serverReStart()
{
	:
}

if [ $# -ne 1 ];then
	usage
	exit 1
fi

case $1 in 
	-s | start )
		serverStart
		echo "start"
	;;
	-t | stop )
		serverStop
	;;
	-rt | restart )
		serverRestart
	;;
	* )
		usage
		exit 1
	;;
esac

