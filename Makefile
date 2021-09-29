FT_VEC = ft_vector
STD_VEC = std_vector

FT_STK = ft_stack
STD_STK = std_stack

F = -Wall 

C = clang++

F = -Wall -Werror -Wextra -std=c++98

INC_DIR =	$(shell find utils -type d) \
			$(shell find tester -type d) \
			$(shell find vector -type d) \
			$(shell find stack -type d)

IFLAGS = $(foreach dir, $(INC_DIR), -I $(dir)) # Lucas did not add space after "-I"

VEC_MAIN = vector/main.cpp
STK_MAIN = stack/main.cpp

UTIL_FILES = tester/utils/RandomGenerator.cpp

ifdef DEBUG
	F += -g3 -fsanitize=address
endif

all:
	@echo "Please enter container name after \"make\" (e.g. \"make vector\")"

vector: $(FT_VEC) $(STD_VEC)

$(FT_VEC): $(VEC_MAIN) $(UTIL_FILES)
	$C $F $(IFLAGS) -D NS=ft -D CONTAINER=vector $^ -o $@

$(STD_VEC): $(VEC_MAIN) $(UTIL_FILES)
	$C $F $(IFLAGS) -D NS=std -D CONTAINER=vector $^ -o $@

stack: $(FT_STK) $(STD_STK)

$(FT_STK): $(STK_MAIN) $(UTIL_FILES)
	$C $F $(IFLAGS) -D NS=ft -D CONTAINER=stack $^ -o $@

$(STD_STK): $(STK_MAIN) $(UTIL_FILES)
	$C $F $(IFLAGS) -D NS=std -D CONTAINER=stack $^ -o $@

clean:

fclean:
	rm -f $(FT_VEC) $(STD_VEC) $(FT_STK) $(STD_STK)

re: fclean
