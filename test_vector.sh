#!/bin/bash

make vector

./ft_vector > ft.out;
./std_vector > std.out;

diff -a ft.out std.out > diff.out;

if [ -s diff.out ];
then
	echo "KO /!\\ Outputs differ /!\\ check \"diff.out\" for more details"
else
	echo "OK"
	rm -f diff.out
fi
