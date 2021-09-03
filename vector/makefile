NAME = vector

C = clang++

F = -Wall -Werror -Wextra -std=c++98

I = -I 

H = ../iterator ../enable_if ../is_integral

I += $H;

FILES = main.cpp

all: $(NAME)

$(NAME): $(FILES)
	$C $F $I $< -o $@

clean:

fclean:
	rm $(NAME)	
