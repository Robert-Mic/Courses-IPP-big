#!/bin/bash
if [ $# -lt 2 ]; then
	#echo usage:$0
	exit 1;
fi

file=$1
shift
routes=$@
re='^[0-9]+$'
exitcode=1

for route in $routes; do
	if ! [[ $route =~ $re ]] ; then
		exit 1
	fi
	if [[ $route -lt 1 ]]; then
		exit 1
	fi
	if [[ 999 -lt $route ]]; then
		exit 1
	fi
	
	exitcode=0
	xd=$(grep "^$route;" $file)
	numbers=$(echo $xd | awk -F ';' '{for (i=3;i<=NF;i+=3) print $i}')
	sum=0
	
	for num in $numbers; do
		sum=$(($sum + $num))
	done
	if [ $sum -ne 0 ]; then
		echo "$route;$sum"
	fi
done

if [ $exitcode -ne 0 ]; then
	exit 1
else
	exit 0
fi
