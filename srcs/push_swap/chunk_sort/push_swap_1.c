#include "push_swap.h"

char	*command_convert(int i)
{
	if (i == 0)
		return ("sa\n");
	if (i == 1)
		return ("ra\n");
	if (i == 2)
		return ("rra\n");
	if (i == 3)
		return ("sb\n");
	if (i == 4)
		return ("rb\n");
	if (i == 5)
		return ("rrb\n");
	if (i == 6)
		return ("pa\n");
	if (i == 7)
		return ("pb\n");
	if (i == 8)
		return ("ss\n");
	if (i == 9)
		return ("rr\n");
	if (i == 10)
		return ("rrr\n");
	return ("Error\n");
}

void	ints_to_commands(int *commands, int winner)
{
	int i;

	i = 1;
	while (i < commands[0])
		ft_putstr(command_convert(commands[i++]));
	if (winner)
		write(1, "Chunk-Sort\n", 11);
	free(commands);
}

int	no_numbers_just_options(char **argv, int argc)
{
	int i;
	
	i = 1;
	while (i < argc)
	{
		while (i < argc && !(ft_strncmp(argv[i], "-", 1)))
			++i;
		if (i == argc)
		{
			write(1, "\n\tUsage: push_swap [-w] [numbers to sort]\n\n", 43);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

void	free_list(t_llist *stack)
{
	while (stack->next)
	{
			stack = stack->next;
			free(stack->last);
	}
	free(stack);
}

int	*push_swap(int *stack_a, int print)
{
	int		*commands;
	t_llist 	*order;

	commands = initialize_stack();
	if (check_sorted(stack_a))
		free_arrays(stack_a, commands);
	order = make_order(stack_a);
#ifndef DEBUG
	free(stack_a);
#endif
	push_swap_chunks(order, &commands, print);
	//free_list(order);
	return (commands);
}