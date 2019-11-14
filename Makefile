COMPILER = gcc
FLAGS = -Wall -Wextra -Werror
SOURCES_1 = ./srcs/push_swap/multiple_algorithms/push_swap.c ./srcs/push_swap/multiple_algorithms/push_swap_2.c ./srcs/push_swap/multiple_algorithms/push_swap_3.c ./srcs/push_swap/multiple_algorithms/push_swap_4.c ./srcs/push_swap/multiple_algorithms/push_swap_5.c 
SOURCES_2 = ./srcs/checker/checker_1.c ./srcs/checker/checker_2.c ./srcs/checker/checker_3.c ./srcs/checker/command2int.c ./srcs/checker/checks.c ./srcs/checker/commands.c
NAME_1 = push_swap
NAME_2 = checker
LIBFT = ./includes/libft/libft.a

all: libft $(NAME_1) $(NAME_2)

$(NAME_1):
	@$(COMPILER) $(FLAGS) $(SOURCES_1) $(LIBFT)  -o ./push_swap
	@echo "compiled push_swap"

$(NAME_2):
	@$(COMPILER) $(FLAGS) $(SOURCES_2) $(LIBFT)  -o ./checker
	@echo "compiled checker"

libft:
	@cd ./includes/libft && make re && cd ../../

clean:
	@/bin/rm -f $(NAME_1) $(NAME_2)
	@cd ./includes/libft && make fclean && cd ../../

re: clean all
