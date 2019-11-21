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

t_params	*get_params(int argc, char **argv)
{
	int i;
	t_params	*params;

	if (!(params = (t_params *)malloc(sizeof(params) * 1)))
		error();
	params->print = 0;
	params->winner = 0;
	i = 1;
	while (i < argc)
	{
		if (!(ft_strncmp(argv[i], "-", 1)))
		{
			if (!(ft_strcmp(argv[i], "-w")))
				params->winner++;
			if (!(ft_strcmp(argv[i], "-p")))
				params->print++;
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
	t_params 	*params;

#ifndef DEBUG
	if (argc < 2 || no_numbers_just_options(argv, argc))
		return (0);
	if (check_input(argc, argv))
		error();
#else 
	//int array[25] = {25, 109, 16, 370, 270, 396, 238, 458, 352, 323, 308, 289, 338, 463, 281, 81, 223, 313, 251, 450, 280, 126, 465, 149, 123}; 
	int array[3] = {3, 82, 68};

	commands = push_swap(array, 0);
#endif
#ifndef DEBUG
	params = get_params(argc, argv);
	commands = push_swap(get_stack(argc, argv), params->print);
#endif
	ints_to_commands(commands, params->winner);
	return (0);
}
