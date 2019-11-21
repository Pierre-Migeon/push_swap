NAME = push_swap

all: $(NAME)

$(NAME):
	gcc -g -Wall -Wextra -Werror  ./push_swap_*.c ../../../includes/libft/libft.a -o push_swap 
debug: clean
	gcc -g -D DEBUG *.c ../../../includes/libft/libft.a -o push_swap
debug2: clean
	gcc -g -D GETIT -Wall -Wextra -Werror ./push_swap_*.c ../../../includes/libft/libft.a -o push_swap

clean:
	rm ./push_swap
re: clean all

