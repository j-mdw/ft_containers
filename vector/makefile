NAME = vector

C = clang++

F = -Wall -Werror -Wextra -std=c++98

I = -I ../iterator -I ../enable_if -I ../is_integral

FILES = main.cpp

DEBUG = debug

DEBUG_F = -g3

all: $(NAME)

$(NAME): $(FILES)
	$C $F $I $< -o $@

$(DEBUG):  $(FILES)
	$C $F $(DEBUG_F) $I $< -o $(NAME)

clean:

fclean:
	rm -f $(NAME)

re: fclean all
