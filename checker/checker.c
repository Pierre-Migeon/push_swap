

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
	char valid_com[11][3] = { "sa\0", "sb\0", "ss\0", "pa\0", "pb\0", "ra\0", "rb\0", "rr\0", "rra", "rrb", "rrr"};
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


char	**get_commands(char **argv, int start_args, int argc)
{
	int size;
	int i;
	char **out;

	size = argc - start_args;
	if (!(out = (char **)malloc(sizeof(char *) * size)))
		return (NULL);
	i = 0;
	while (start_args < argc)
	{
		size = ft_strlen(argv[start_args]);
		if (!(out[i] = (char *)malloc(sizeof(char) * size)))
			return (NULL);
		out[i] = ft_strcpy(out[i], argv[start_args++]);
		++i;
	}
	out[i] = NULL;
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

int	check_sorted(int *stack_a, int stack_size)
{
	int i;

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
	i = 0;
	while (i < stack_size)
	{
		stack[i] = ft_atoi(argv[i + 1]);
		++i;
	}
	*start_args = stack_size;
	return (stack);
}

void	run_commands(int *stack_a, int *stack_a_size, int *stack




int	perform_sort(char **commands, int *stack_a, int stacka_size)
{
	int i;
	int stack_b_size;
	int *stack_b;
	

	i = 0;
	while (commands[i])
		run_commands(stack_a, stack_a_size, stack_b, commands[i++]);
	return (check_sorted(stack_a, stacka_size));
}

int	grade_it(int i)
{
	(i == 1) ? write(1, "OK\n", 3) : write(1, "KO\n", 3);
	return (0);
}

int	main(int argc, char **argv)
{	
	int start_args;
	char **commands;
	int *stack;

	if (argc < 2)
		return (0);
	if (!(start_args = check_input(argc, argv)))
		return (error());
//	if (start_args > 0)
		commands = get_commands(argv, start_args, argc);
	stack = get_stack(argc, argv, &start_args);
	return (grade_it(perform_sort(commands, stack, start_args)));
}
