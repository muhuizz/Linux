#!/bin/bash

ROOT_PATH=$(pwd)
client_BIN=${ROOT_PATH}/udpclient
conf_file=${ROOT_PATH}/conf/client.conf

proc=$(basename $0)
function usage()
{
	printf "Usage# %s [-s(start) | -t(stop) | -rt(restart)]\n" "$proc"
}

function clientStart()
{
	name=$(basename $client_BIN)
	pid=`pidof $name`
	if [ $? -eq 0 ]; then
		echo "udpclient is already running!,pid is %s" "$pid"
	else
		ip=$(awk -F: '/^IP/{print $NF}' ${conf_file})
		port=$(awk -F: '/^PORT/{print $NF}' ${conf_file})
		${client_BIN} $ip $port
	fi
}

function clientStop()
{
	:
}

function clientReStart()
{
	:
}

if [ $# -ne 1 ];then
	usage
	exit 1
fi

case $1 in 
	-s | start )
		clientStart
		echo "start"
	;;
	-t | stop )
		clientStop
	;;
	-rt | restart )
		clientRestart
	;;
	* )
		usage
		exit 1
	;;
esac

