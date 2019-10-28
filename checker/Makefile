NAME = checker
COMPILER = gcc
SRCS = checker_1.c checker_2.c checker_3.c command2int.c checks.c commands.c
INCLUDES = ../includes/get_next_line/libft/libft.a
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@$(COMPILER) $(FLAGS) $(SRCS) $(INCLUDES) -o checker
	@echo checker compiled!
clean:
	@rm ./checker
	@echo checker removed!
