NAME = push_swap

all: $(NAME)

$(NAME):
	gcc -g push_swap.c push_swap_2.c push_swap_3.c push_swap_4.c push_swap_5.c ../../includes/get_next_line/libft/libft.a -o push_swap

debug: clean
	gcc -g -D DEBUG push_swap.c push_swap_2.c push_swap_3.c push_swap_4.c push_swap_5.c ../../includes/get_next_line/libft/libft.a -o push_swap
clean:
	rm ./push_swap
re: clean all

