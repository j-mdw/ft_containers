#!/bin/bash

set -e

if [ $# -eq 0 ]; then
	echo "test_container: please provide one or more container names (e.g. stack)"
	exit 1
fi

dir=output

#Check if $dir exists and if it is a directory
if [[ ! -e $dir ]]; then
	mkdir $dir
elif [[ ! -d $dir ]]; then
	echo "$dir is not a directory, please remove $dir and run the script again"
	exit 1
fi

dir=$dir/

function test_container()
{
	echo "--Testing $arg--"

	make $arg

	ft=ft_$arg
	std=std_$arg

	./$ft > "$dir$ft".out
	./$std > "$dir$std".out

	set +e	
	diff -a "$dir$ft".out "$dir$std".out > "$dir$arg"_diff.out
	set -e

	if [ -s "$dir$arg"_diff.out ]; then
		echo "[KO] /!\\ Outputs differ /!\\ check \""$dir$arg"_diff.out\" for more details"
	else
		echo "[OK]"
		rm -f "$dir$arg"_diff.out
	fi
}

for arg in $@; do
	test_container
done
