#include "checker.h"

void	swap(int *a, int *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void	rotate(int *stack)
{
	int i;

	i = 1;
	while (i < stack[0] - 1)
	{
		swap(&stack[i], &stack[i + 1]);
		++i;
	}
}

void	reverse_rotate(int *stack)
{
	printf ("Entered reverse rotate function\n");
	int stack_size = stack[0];

	while(--stack_size > 1)
		swap(&stack[stack_size], &stack[stack_size - 1]);
}

int	remove_top(int *stack)
{
	int out;
	int i;

	i = 1;
	out = stack[1];
	while (i < stack[0] - 1)
	{
		stack[i] = stack[i + 1];
		i++;
	}
	stack[0] -= 1;
	return (out);
}

int	*push(int *stack_source, int *stack_destination)
{
	int *out;
	int pushed_element;
	int i;

	if (stack_source[0] == 1)
		return (stack_destination);
	pushed_element = remove_top(stack_source);
	stack_destination[0] += 1;
	if (!(out = (int *)malloc(sizeof(int) * stack_destination[0])))
		return (0);
	out[0] = stack_destination[0];
	out[1] = pushed_element;
	i = 2;
	while(i < stack_destination[0])
	{
		out[i] = stack_destination[i - 1];
		i++;
	}
	free(stack_destination);
	return (out);
}

int	error(void)
{
	write(1, "error\n", 6);
	return (0);
}

int	check_int(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

int	check_seen(char **argv, int i)
{
	int j;

	j = i - 1;
	while(j > 0)
		if (ft_strcmp(argv[j--], argv[i]) == 0)
			return (1);
	return (0);
}

int	is_command(char *input)
{
	char valid_com[11][4] = { "sa\0\0", "sb\0\0", "ss\0\0", "pa\0\0", "pb\0\0", "ra\0\0", "rb\0\0", "rr\0\0", "rra\0", "rrb\0", "rrr\0"};
	int match;
	int i;

	match = 0;
	i = 0;
	while(*valid_com[i])
		if (ft_strcmp(valid_com[i++], input) == 0)
			match = 1;
	return (match);
}

int	check_input(int argc, char **argv)
{
	int i;
	int start_args;

	i = 1;
	while (i < argc && (!(is_command(argv[i]))))
	{
		if (check_int(argv[i]))
			return (0);
		if (check_seen(argv, i))
			return (0);
		++i;
	}
	start_args = i;
	while (i < argc)
		if (!(is_command(argv[i++])))
			return (0);
	return ((start_args == i) ? -1 : start_args);
}

int	command_to_int(char *operation)
{
	if (!(ft_strcmp("sa", operation)))
		return (0);
	if (!(ft_strcmp("ra", operation)))
		return (1);
	if (!(ft_strcmp("rra", operation)))
    return (2);
	if (!(ft_strcmp("sb", operation)))
	 	return (3);
	if (!(ft_strcmp("rb", operation)))
		return (4);
	if (!(ft_strcmp("rrb", operation)))
		return (5);
	if (!(ft_strcmp("pa", operation)))
		return (6);
	if (!(ft_strcmp("pb", operation)))
    return (7);
	if (!(ft_strcmp("ss", operation)))
		return (8);
	if (!(ft_strcmp("rr", operation)))
    return (9);
	if (!(ft_strcmp("rrr", operation)))
    return (10);
	return (0);
}

int	*get_commands(char **argv, int start_args, int argc)
{
	int size;
	int i;
	int *out;

	size = argc - start_args + 1;
	if (!(out = (int *)malloc(sizeof(int) * size)))
		return (NULL);
	out[0] = size;
	i = 1;
	while (start_args < argc)
		out[i++] = command_to_int(argv[start_args++]);
	return (out);
}

int	*read_commands()
{
	int *commands;
	int r;
	char *line;

	while ((r = get_next_line(0, &line)) == 0)
		;
	while ((r = get_next_line(0, &line)) > 0)
	{
		if (!(is_command(line)))
                        error();
		
	}

	return (commands);	
}

int	check_sorted(int *stack_a, int stack_b_size)
{
	int i;

	if (stack_b_size > 1)
		return (0);
	i = 2;
	while (i < stack_a[0])
	{
			if (stack_a[i] < stack_a[i - 1])
				return (0);
		i++;
	}
	return (1);
}

int	*get_stack(int argc, char **argv, int start_args)
{
	int stack_size;
	int *stack;
	int i;

	stack_size = (start_args > 0) ? start_args : argc;
	if (!(stack = (int *)malloc(sizeof(int) * stack_size)))
		return (0);
	stack[0] = stack_size;
	i = 1;
	while (i < stack[0])
	{
		stack[i] = ft_atoi(argv[i]);
		++i;
	}
	return (stack);
}

void	run_command(int command, int *stack)
{
	void	(*f_point[3])();
        f_point[0] = swap;
        f_point[1] = rotate;
        f_point[2] = reverse_rotate;

	if (stack[0] < 3)
		return;
	if (command > 2 && command < 6)
		command -= 3;
	else if (command > 7)
		command -= 8;
	if (command == 0)
		(f_point[command])(&stack[1], &stack[2]);
	else
		(f_point[command])(stack);
}

void	print_stack(int *stack)
{
	int i;

	i = 1;
	while (i < stack[0])
	{
		printf ("%i, ", stack[i]);
		++i;
	}
	printf("Stack length is %i", stack[0]);
	printf ("\n");
}

int	*intialize_stack_b(void)
{
	int *out;

	if (!(out = (int *)malloc(sizeof(int) * 1)))
		return (0);
	out[0] = 1;
	return (out);
}

int	perform_sort(int *commands, int *stack_a)
{
	int i;
	int *stack_b;

	stack_b = intialize_stack_b();
	i = 1;
	while (i < commands[0])
	{
		if (commands[i] < 3)
			run_command(commands[i], stack_a);
		if (commands[i] > 2 && commands[i] < 6)
			run_command(commands[i], stack_b);
		if (commands[i] == 6)
			stack_a = push(stack_b, stack_a);
		if (commands[i] == 7)
			stack_b = push(stack_a, stack_b);
		if (commands[i] > 7)
		{
			run_command(commands[i], stack_a);
			run_command(commands[i], stack_b);
		}
		printf ("-----------------\n");
		print_stack(stack_a);
		print_stack(stack_b);
		i++;
	}
	return (check_sorted(stack_a, stack_b[0]));
}

int	grade_it(int i)
{
	(i == 1) ? write(1, "OK\n", 3) : write(1, "KO\n", 3);
	return (0);
}

int	main(int argc, char **argv)
{
	int start_args;
	int *commands;
	int *stack;

	if (argc < 2)
		return (0);
	if (!(start_args = check_input(argc, argv)))
		return (error());
	if (start_args > 0)
		commands = get_commands(argv, start_args, argc);
	else
		commands = read_commands();
	stack = get_stack(argc, argv, start_args);
	return (grade_it(perform_sort(commands, stack)));
}
