#!/bin/bash

clang++ -Wall -Werror -Wextra -std=c++98 -D STD=true main42.cpp -o std_speed
clang++ -Wall -Werror -Wextra -std=c++98 main42.cpp -o ft_speed