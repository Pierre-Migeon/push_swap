#ifndef CHECKER_H
# define CHECKER_H

#include "../../../includes/libft/libft.h"
#include <sys/uio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

# define read_error(i) (i < 0) ? error() : 0;

typedef struct		s_params
{
	int		print;
	int		winner;
	int		visualize;
	int		color;
}			t_params;

typedef struct	s_dir
{
	int	dir;
	int	target_index;
	int	best_distance;
	int	current_distance;
}		t_dir;

typedef struct	s_llist
{
	int	val;
	int	index;
	int	keep;
	int	max_index;
	struct	s_llist *next;
	struct	s_llist *last;
} 		t_llist;

typedef struct	s_listy
{
        char 	*str;
        int 	list_count;
        struct 	s_listy *next;
}		t_listy;

typedef struct	s_hash
{
        int     current_score;
        int     best_score;
        int     best_index;
        int     head_index;
        int     last_index;
        int     final_index;
}		t_hash;

void		swap(int *a, int *b);
void		rotate(int *stack);
void		reverse_rotate(int *stack);
int		remove_top(int *stack);
int		*push(int *stack_source, int *stack_destination);
void		error(void);
int		check_int(char *str);
int		check_seen(char **argv, int i);
int		check_input(int argc, char **argv);
int		check_sorted(int *stack_a);
int		*get_stack(int argc, char **argv);
int		*initialize_stack(void);
int		check_rotate(int i, int *stack, int *commands);
void		print_array(int *array);
int		*push_end(int *commands, int option);
void		run_command(int command, int *stack);
void		perform_operation(int **stack_a, int **stack_b, int command);
char		*command_convert(int i);
void		ints_to_commands(int *commands, int winner);
int		id_largest(int *stack);
int		id_smallest(int *stack);
int		check_rotate_dir(int *stack_a, int min);
void		push_swap_bsort(int *stack_a, int *stack_b, int **commands);
void		free_arrays(int *stack_a, int *commands);
int		*copy_original(int *stack_a);
int		*push_swap(int *stack_a, int print);
int		main(int argc, char **argv);
t_llist		*label(t_llist *head, t_hash best);
int		reset_and_test_hash(t_hash *best);
t_llist		*classify(t_llist *head);
int		next_bigger_index(int *stack, int value);
int		smallest_index(int *things);
int		*index_stack(int *stack);
void		init_node(t_llist *node, int val, int index, int max);
t_llist		*make_order(int *stack_a);
int		edge_indexes(t_llist *stack, int ref_index);
int		shortest_path_2(t_llist *stack_a, t_llist *stack_b);
int		shortest_path_3(t_llist *stack_a);
void		push_a(t_llist **stack_a, t_llist **stack_b, int **commands);
int		check_push_a(t_llist *stack_a, t_llist *stack_b);
void		push_b(t_llist **stack_a, t_llist **stack_b, int **commands);
int		shortest_path(t_llist *stack);
int		not_sorted(t_llist *stack);
void		push_swap_indexed(t_llist *stack_a, int **commands);
void		push_swap_quicksort(t_llist *stack_a, int **commands);
void		push_swap_chunks(t_llist *stack_a, int **commands, int print);
int		stack_a_too_big(t_llist *stack_a);
void		index_llist(t_llist *stack);
int		is_lower_than_median(t_llist *stack_a, int median);
int		list_swap(t_llist **stack, int **commands, int i);
void		sort_b(t_llist **stack_b, int **commands);
int		bottom_three(t_llist *stack_a);
int		three_in(t_llist *stack_b);
int		find_median(t_llist *stack_a);
int		list_rotate(t_llist **stack, int **commands, int i);
int		*make_int_stack(t_llist *stack);
void		print_stacks(t_llist *a, t_llist *b);
int		quickest_path(t_llist *stack_a);
int		quickest_path_2(t_llist *stack_b, int max_index);
void		sort_a(t_llist **stack_a, int **commands);
int		correct_end(t_llist **stack_a, t_llist **stack_b, int **commands, int max);
int		is_within_range(t_llist *stack_a, int *range);
void		print_range_table(int	indexes[12]);
void		push_swap_chunks_stack_b(t_llist **stack_a, t_llist **stack_b, int **commands, int print);
int		*find_range(t_llist *stack_a);
int		quickest_path_chunks(t_llist *stack_a, int *range);
int		shortest_path_4(t_llist *head, t_llist *target, int flag);
int		should_shift_b(t_llist *a, t_llist *b, t_dir *dir);
int		no_numbers_just_options(char **argv, int argc);
void		print_stack(t_llist *a);
int		is_flag(char *str);
int		two_in(t_llist *stack);
int		numlen(int num);
int		get_offset(int *stack);
void		run_and_print(int *commands, int *stack, int color);
void		free_list(t_llist *stack);
void		write_line(int a, int b, int offset, int print_code, int color);
void		print_boxes(t_llist *stack_a, t_llist *stack_b, int offset, int color);
void		run_commands(t_llist **stack_a, t_llist **stack_b, int command);
char		*long_command_convert(int i);
void		write_header(int offset);
void		ft_putstr_color(char *str, int code);
int		color_code(int command);

#endif
