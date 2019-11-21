#include "checker.h"

void	print_array(int *array)
{
	int i;

	i = 1;
	while (i < array[0])
		printf ("%i ", array[i++]);
	printf ("\n");
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

int	*intialize_stack_b(void)
{
	int *out;

	if (!(out = (int *)malloc(sizeof(int) * 1)))
		return (0);
	out[0] = 1;
	return (out);
}

int	perform_sort(int *commands, int *stack_a, t_params *params)
{
	int 	i;
	int *stack_b;

	stack_b = intialize_stack_b();
	if ((commands[0] == 1) && check_sorted(stack_a, stack_b, commands, 0))
		return (1);
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
		i++;
	}
	if (params->print_list)
		print_stack(stack_a, stack_b);
	free(params);
	return (check_sorted(stack_a, stack_b, commands, 1));
}

int	grade_it(int i)
{
	(i == 1) ? write(1, "OK\n", 3) : write(1, "KO\n", 3);
	return (0);
}

int	shift_argv(int argc, char **argv)
{
	int i;

	i = 0;
	while (i < argc - 1)
	{
		argv[i] = argv[i + 1];
		++i;
	}
	return (argc - 1);
}

int	main(int argc, char **argv)
{
	int 		start_args;
	int 		*commands = NULL;
	int 		*stack;
	t_params	*params;

	if (argc < 2)
		return (0);
	if (!(start_args = check_input(argc, argv)))
		error();
	if (start_args == -2)
		return (0);
	if (!(params = (t_params *)malloc(sizeof(t_params))))
		error();
	stack = get_stack(argc, argv, start_args, params);
	if (start_args > 0)
		commands = get_commands(argv, start_args, argc);
	else
		commands = read_commands();
	if (check_commands(commands))
	{
		free(stack);
		free(commands);
		error();
	}
	return (grade_it(perform_sort(commands, stack, params)));
}
