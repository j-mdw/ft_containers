#!/bin/bash

make stack

dir=output/

./ft_stack > "$dir"ft_stack.out;
./std_stack > "$dir"std_stack.out;

diff -a "$dir"ft_stack.out "$dir"std_stack.out > "$dir"stack_diff.out;

if [ -s "$dir"stack_diff.out ];
then
	echo "[KO] /!\\ Outputs differ /!\\ check \""$dir"stack_diff.out\" for more details"
else
	echo "[OK]"
	rm -f "$dir"stack_diff.out
fi
