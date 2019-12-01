COMPILER = gcc
FLAGS = -Wall -Wextra -Werror
SOURCES_1 = ./srcs/push_swap/chunk_sort/*.c
SOURCES_2 = ./srcs/checker/checker_1.c ./srcs/checker/checker_2.c ./srcs/checker/checker_3.c ./srcs/checker/command2int.c ./srcs/checker/checks.c ./srcs/checker/commands.c
SOURCES_3 = ./srcs/testing/random_lists/main.c
NAME_1 = push_swap
NAME_2 = checker
NAME_3 = tester
LIBFT = ./includes/libft/libft.a

all: libft $(NAME_1) $(NAME_2) $(NAME_3)

$(NAME_1):
	@$(COMPILER) $(FLAGS) $(SOURCES_1) $(LIBFT)  -o ./push_swap
	@echo "compiled push_swap"

$(NAME_2):
	@$(COMPILER) $(FLAGS) $(SOURCES_2) $(LIBFT)  -o ./checker
	@echo "compiled checker"

$(NAME_3):
	@$(COMPILER) $(FLAGS) $(SOURCES_3) $(LIBFT) -o ./tester
	@echo "compiled tester"

libft:
	@cd ./includes/libft && make re && cd ../../

clean:
	@/bin/rm -f $(NAME_1) $(NAME_2) $(NAME_3)
	@cd ./includes/libft && make fclean && cd ../../

re: clean all
