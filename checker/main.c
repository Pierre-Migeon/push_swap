




int	grade_it(int i, int from_STDIN)
{
	if (from_STDIN == 0)
		(i == 1) ? write(1, "OK\n", 3) : write(1, "KO\n", 3);
	else 
		(i == 1) ? write(1, "\33[AOK\n", 6) : write(1, "\33[AKO\n", 6);
	return (0);
}

int	main(int argc, char **argv)
{
	int start_args;
	int *commands;
	int *stack;
	int from_STDIN;

	if (argc < 2)
		return (0);
	if (!(start_args = check_input(argc, argv)))
		error();
	if (start_args > 0)
	{	
		from_STDIN = 0;	
		commands = get_commands(argv, start_args, argc);
	}
	else
	{
		from_STDIN = 1;
		commands = read_commands(commands);
	}
	stack = get_stack(argc, argv, start_args);
	return (grade_it(perform_sort(commands, stack), from_STDIN));
}
