#!/bin/bash
if [ $# -lt 2 ]; then
	#echo usage:$0
	exit 1;
fi

file=$1
shift
routes=$@
re='^[0-9]+$'

for route in $routes; do
	if ! [[ $route =~ $re ]] ; then
		exit 1
	else
		xd=$(grep "^$route;" $file)
		numbers=$(echo $xd | awk -F ';' '{for (i=3;i<=NF;i+=3) print $i}')
		sum=0
		for num in $numbers; do
			sum=$(($sum + $num))
		done
		if [ $sum -ne 0 ]; then
			echo $sum
		fi
	fi
done

exit 0