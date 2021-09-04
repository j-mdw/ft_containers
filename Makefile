FT_EXEC = ft_exec
STD_EXEC = std_exec

F = -Wall 

C = clang++

F = -Wall -Werror -Wextra -std=c++98

INC_DIR =	$(shell find utils -type d) \
			$(shell find tester -type d) \
			$(shell find vector -type d)

IFLAGS = $(foreach dir, $(INC_DIR), -I $(dir)) # Lucas did not add space after "-I"

VEC_MAIN = vector/main.cpp

ifdef DEBUG
	F += -g3
endif

vector: $(FT_EXEC) $(STD_EXEC)

$(FT_EXEC): $(VEC_MAIN)
	$C $F $(IFLAGS) -D NS=ft -D CONTAINER=vector $^ -o $@

$(STD_EXEC): $(VEC_MAIN)
	$C $F $(IFLAGS) -D NS=std -D CONTAINER=vector $^ -o $@

clean:

fclean:
	rm -f $(FT_EXEC) $(STD_EXEC)

re: fclean