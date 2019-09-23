
int	check_sorted(int *stack_a, int *stack_b)
{
	int i;

	if (stack_b[0] > 1)
		return (0);
	i = 2;
	while (i < stack_a[0])
	{
			if (stack_a[i] < stack_a[i - 1])
			{
				free(stack_a);
				free(stack_b);
				return (0);
			}
		i++;
	}
	free(stack_a);
	free(stack_b);
	return (1);
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
		i++;
	}
	return (check_sorted(stack_a, stack_b));
}
