NAME = checker
COMPILER = gcc
SRCS = checker_1.c checker_2.c checker_3.c command2int.c checks.c commands.c
INCLUDES = ../../includes/libft/libft.a
FLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME):
	@$(COMPILER) $(FLAGS) $(SRCS) $(INCLUDES) -o checker
	@echo checker compiled!
clean:
	@rm ./checker
	@echo checker removed!
re: clean all
