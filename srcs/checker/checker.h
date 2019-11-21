#ifndef CHECKER_H
# define CHECKER_H

#include "../../includes/libft/libft.h"
#include <sys/uio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

# define read_error(i) (i < 0) ? error() : 0;

typedef struct  	s_listy
{
        char 		*str;
        int 		list_count;
	int 		piped_in;
        struct s_listy	*next;
}       		t_listy;

typedef struct		s_params
{
	int		print_list;
}			t_params;


void	swap(int *a, int *b);
void	rotate(int *stack);
void	reverse_rotate(int *stack);
int	remove_top(int *stack);
int	*push(int *stack_source, int *stack_destination);
void    error(void);
int	check_int(char *str);
int	check_seen(char **argv, int i);
int	is_command(char *input);
int	check_input(int argc, char **argv);
int	command_to_int(char *operation);
int	*get_commands(char **argv, int start_args, int argc);
void	chomp(char *str);
t_listy *new_lst(char *str);
t_listy	*push_head(t_listy *head, char *str);
void	add_char(char temp[6], char *c);
int	*generate_commands(t_listy *head);
int	*generate_zero();
int	*read_commands(void);
int	check_sorted(int *stack_a, int *stack_b, int *commands, int f);
int	*get_stack(int argc, char **argv, int start_args, t_params *params);
void	run_command(int command, int *stack);
void	print_stack(int *stack_a, int *stack_b);
int	*intialize_stack_b(void);
int	perform_sort(int *commands, int *stack_a, t_params *params);
int	grade_it(int i);
int	main(int argc, char **argv);
int     check_commands(int *commands);
int	is_flag(char *str);

#endif
