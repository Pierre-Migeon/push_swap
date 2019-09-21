#include "checker.h"

int	ft_atoi(const char *str)
{
	int out;
	int n;

	out = 0;
	n = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		n = 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		out = out * 10 + *(str++) - '0';
	return (n ? -out : out);
}

int     ft_strcmp(const char *s1, const char *s2)
{
        while(*s1 && *s2 && *((unsigned char *)s1) == *((unsigned char *)s2))
	{
		s1++;
		s2++;
	}
        return (*((unsigned char *)s1) - *((unsigned char *)s2));
}

size_t	ft_strlen(const char *s)
{
	return (*s ? 1 + ft_strlen(++s) : 0);
}

char	*ft_strcpy(char	*dst, const char *src)
{
	int i;

	i = -1;
	while(src[++i])
		*(dst + i) = *(src + i);
	*(dst + i) = '\0';
	return (dst);
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


int	remove_top(int *stack, int *stack_size)
{
	int out;
	int i;

	i = 0;
	out = stack[0];
	while (i < *stack_size - 1)
	{
		stack[i] = stack[i + 1];
		i++;
	}
	*stack_size -= 1;
	return (out);
}

int	*push(int *stack_source, int *stack_destination, int *stack_s_size, int *stack_d_size)
{
	int *out;
	int pushed_element;
	int i;

	if (*stack_s_size == 0)
		return (stack_destination);
	pushed_element = remove_top(stack_source, stack_s_size);
	if (!(out = (int *)malloc(sizeof(int) * *stack_d_size + 1)))
		return (0);
	i = 1;
	while(i < *stack_d_size + 1)
	{
		out[i] = stack_destination[i - 1];
		i++;
	}
	*stack_d_size += 1;
	out[0] = pushed_element;
	free(stack_destination);
	return (out);
}

int	error(void)
{
	write(1, "error\n", 6);
	return (1);
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

/*
char	**read_commands()
{
	int bits_read;
	char temp[3];
	char *out;

	while ((bits_read = read(0, temp, 3)) > 0)
        {
                temp[2] = '\0';

        }
	return (out);
}
*/

int	check_sorted(int *stack_a, int stack_size, int stack_b_size)
{
	int i;

	if (stack_b_size > 0)
		return (0);
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

int	*get_stack(int argc, char **argv, int *start_args)
{
	int stack_size;
	int *stack;
	int i;

	stack_size = (*start_args > 0) ? *start_args - 1 : argc - 1;
	if (!(stack = (int *)malloc(sizeof(int) * stack_size)))
		return (0);
	//stack[0] = stack_size;
	i = 0;
	while (i < stack_size)
	{
		stack[i] = ft_atoi(argv[i + 1]);
		++i;
	}
	*start_args = stack_size;
	return (stack);
}

void	run_command(int command, int *stack, int stack_size)
{
	void	(*f_point[11])();

	if (stack_size == 0)
		return;

	f_point[0] = swap;
	f_point[1] = rotate;
	f_point[2] = reverse_rotate;
	f_point[8] = swap;
        f_point[9] = rotate;
        f_point[10] = reverse_rotate;

	if (command == 0)
		(f_point[command])(&stack[0], &stack[1]);
	else
		(f_point[command])(stack, stack_size);
}

void	print_stack(int *stack, int stack_size)
{
	int i;

	i = 0;
	while (i < stack_size)
	{
		printf ("%i, ", stack[i]);
		++i;
	}
	printf ("\n");
}

int	perform_sort(int *commands, int *stack_a, int *stack_a_size)
{
	int i;
	int stack_b_size = 0;
	int *stack_b = NULL;

	i = 1;
	while (i < commands[0])
	{
		if (commands[i] < 3)
			run_command(commands[i], stack_a, *stack_a_size);
		if (commands[i] > 2 && commands[i] < 6 && stack_b_size > 1)
			run_command(commands[i], stack_b, stack_b_size);
		if (commands[i] == 6)
			stack_a = push(stack_b, stack_a, &stack_b_size, stack_a_size);
		if (commands[i] == 7)
			stack_b = push(stack_a, stack_b, stack_a_size, &stack_b_size);
		if (commands[i] > 7)
		{
			run_command(commands[i], stack_a, *stack_a_size);
			run_command(commands[i], stack_b, stack_b_size);
		}
		printf ("-----------------\n");
		print_stack(stack_a, *stack_a_size);
		print_stack(stack_b, stack_b_size);
		i++;
	}
	return (check_sorted(stack_a, *stack_a_size, stack_b_size));
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
//	if (start_args > 0)
		commands = get_commands(argv, start_args, argc);
	stack = get_stack(argc, argv, &start_args);
	return (grade_it(perform_sort(commands, stack, &start_args)));
}
