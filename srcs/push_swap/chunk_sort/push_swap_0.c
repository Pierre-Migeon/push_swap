#include "push_swap.h"

void    free_arrays(int *stack_a, int *commands)
{       
        free(stack_a);
        free(commands);
        exit(0);
}

void	print_stack(t_llist *a)
{
	t_llist *head;
	char 	*num;
	int	i;

	head = a;
	while (a)
	{
		i = 0;
		num = ft_itoa(a->val);
		while (*(num + i))
			write(1, (num + i++), 1);
		free(num);
		a = a->next;
		if (a == head)
			break;
		write(1, " ", 1);
	}
	write(1, "\n", 1);
}

int set_zero(t_params *params)
{
        params->print = 0;
        params->winner = 0;
        params->winner = 0;
        params->color = 0;
	return (1);
}

int	not_command(char *c)
{
	return ((ft_strcmp(c, "-w") == 0) || (ft_strcmp(c, "-p") == 0) || (ft_strcmp(c, "-v") == 0) || (ft_strcmp(c, "-c") == 0));
}

t_params	*get_params(int argc, char **argv)
{
	int i;
	t_params	*params;

	if (!(params = (t_params *)malloc(sizeof(params) * 1)))
		exit(1);
	i = set_zero(params);
	while (i < argc)
	{
		if (!(ft_strncmp(argv[i], "-", 1)))
		{
			params->winner += (!(ft_strcmp(argv[i], "-w")));
			params->print += (!(ft_strcmp(argv[i], "-p")));
			params->visualize += (!(ft_strcmp(argv[i], "-v")));
			params->color += (!(ft_strcmp(argv[i], "-c")));
			if (not_command(argv[i]) == 0 && !(ft_isdigit(argv[i][1])))
			{
				write(1, "\n\tUsage: push_swap [-w] [-v] [-c] [-p] numbers_to_sort\n\n", 56);
				free(params);
                        	exit (0);
			}
		}
		else
			return (params);
		++i;
	}
	return (params);
}

int	main(int argc, char **argv)
{
	int 		*commands;
	int		*stack_a_initial;
	t_params 	*params;

	if (argc < 2 || no_numbers_just_options(argv, argc))
		return (0);
	if (check_input(argc, argv))
		error();
	params = get_params(argc, argv);
	stack_a_initial = get_stack(argc, argv);
	commands = push_swap(stack_a_initial, params->print);
	if (params->visualize)
		run_and_print(commands, stack_a_initial, params->color);
	else
	{
		ints_to_commands(commands, params->winner);
		free(stack_a_initial);
	}
	free(params);
	return (0);
}
