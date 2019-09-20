
#include <stdio.h>


int	error(void)
{
	write(1, "error\n", 6);
	return (1);
}

int	check_int(char *str)
{
	while (*str)
	{
		if (*str > '0' || *str > '9')
			return (1);
		str++;
	}
}

int	check_seen(char **argv, int i)
{
	int j;

	j = i - 1;
	while(j > 0)
		if (ft_strcmp(argv[j--], argv[i] == 0)
			return (1);
	return (0);
}

int	check_input(int, argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (check_int(argv[i]))
			return (1);
		check_seen(argv, i);
			return (1);	
	}
	return (0);
}


int	check_sorted(int *stack_a, int stack_size)
{
	int i;
	int last;

	i = 0;
	while (i < stack_size)
	{
		if (i > 0)
			if (stack_a[i] < stack_a[i - 1])
				return (0);
		i++;
	}
	return (1);
}

void	swap(int *a, int *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void	rotate(int *stack, int stack_size)
{
	int i;

	i = 0;
	while (i < stack_size - 1)
	{
		swap(&stack[i], &stack[i + 1]);
		++i;
	}
}


void	reverse_rotate(int *stack, int stack_size)
{
	while(--stack_size > 0)
		swap(&stack[stack_size], &stack[stack_size - 1]);
}

int	*push(int *stack, int element, int stack_size)
{
	int *out;
	int i;

	if (!(out = (int *)malloc(sizeof(int) * stack_size + 1)))
		return (0);
	i = 1;
	while(i < stack_size + 1)
	{
		out[i] = stack[i - 1];
		i++;
	}
	out[0] = element;
	free(stack);
	return (out);
}

int	*to_ints(int argc, char **argv)
{
	int	*stack_a;
	int 	i;
	
	if (!((int *)malloc(sizeof(int) * argc)))
		return (0);
	i = 1;
	while (i < argc)
	{
		stack_a[i] = ft_atoi(argv[i];
		++i;
	}
	return (stack_a);
}


int	main(int argc, char **argv)
{
	if (argc < 2)
		return (error());
	if (check_input(argc, argv);
		return (error());
	push_swap(to_ints(argc, argv), argc - 1);
	return (0);
}
