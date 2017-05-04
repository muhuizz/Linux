#!/bin/bash

ROOT_PATH=$(pwd)
CLIENT_BIN=${ROOT_PATH}/udpclient
conf_file=${ROOT_PATH}/conf/client.conf

proc=$(basename $0)
function usage()
{
	printf "Usage# %s [-s(start) | -t(stop) | -rt(restart)]\n" "$proc"
}

function clientStart()
{
	name=$(basename $CLIENT_BIN)
	pid=`pidof $name`
	if [ $? -eq 0 ]; then
		echo "udpclient is already running!,pid is %s" "$pid"
	else
		ip=$(awk -F: '/^IP/{print $NF}' ${conf_file})
		port=$(awk -F: '/^PORT/{print $NF}' ${conf_file})
		nick_name=$(awk -F: '/^nick_name/{print $NF}' ${conf_file})
		school=$(awk -F: '/^school/{print $NF}' ${conf_file})
		
		${CLIENT_BIN} $ip $port $nick_name $school
	fi
}

function clientStop()
{
	name=$(basename $CLIENT_BIN)
	pid=`pidof $name`
	if [ $? -eq 0 ]; then
		$(kill -9 ${pid})
		echo "udpclient is stoped!"
	else
		echo "udpclient is not start"
	fi
}

function clientRestart()
{
	clientStop
	clientStart
}

if [ $# -ne 1 ];then
	usage
	exit 1
fi

case $1 in 
	-s | start )
		clientStart
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

