FT_VEC = ft_vector
STD_VEC = std_vector

FT_STK = ft_stack
STD_STK = std_stack

FT_MAP = ft_map
STD_MAP = std_map

C = clang++

F = -Wall -Werror -Wextra -std=c++98

INC_DIR =	$(shell find srcs -type d) \
			$(shell find tester -type d)

IFLAGS = $(foreach dir, $(INC_DIR), -I $(dir))

VEC_MAIN = srcs/vector/main.cpp
STK_MAIN = srcs/stack/main.cpp
MAP_MAIN = srcs/map/main.cpp

UTIL_FILES = tester/utils/RandomGenerator.cpp

ifdef DEBUG
	F += -g3
endif

ifdef ASAN
	F += -fsanitize=address
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

map: $(FT_MAP) $(STD_MAP)

$(FT_MAP): $(MAP_MAIN) $(UTIL_FILES)
	$C $F $(IFLAGS) -D NS=ft -D CONTAINER=map $^ -o $@

# $(STD_STK): $(STK_MAIN) $(UTIL_FILES)
# 	$C $F $(IFLAGS) -D NS=std -D CONTAINER=stack $^ -o $@

clean:

fclean:
	rm -f $(FT_VEC) $(STD_VEC) $(FT_STK) $(STD_STK) $(FT_MAP) $(STD_MAP)

re: fclean
