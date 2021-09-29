#!/bin/bash

make vector

dir=output/

./ft_vector > "$dir"ft_vector.out;
./std_vector > "$dir"std_vector.out;

diff -a "$dir"ft_vector.out "$dir"std_vector.out > vector_diff.out;

if [ -s "$dir"vector_diff.out ];
then
	echo "[KO] /!\\ Outputs differ /!\\ check \""$dir"diff.out\" for more details"
else
	echo "[OK]"
	rm -f "$dir"vector_diff.out
fi
