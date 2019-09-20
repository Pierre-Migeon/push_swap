

#include "checker.h"


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

int	main(int argc, char **argv)
{	
	int start_args;
	char **commands;

	if (argc < 2)
		return (0);
	if (!(start_args = check_input(argc, argv)))
		return (error());
	if (start_args > 0)
		commands = get_commands(argv, start_args, argc);
	int i = 0;
	while(start_args < argc)
	{
		printf("%s\n", commands[i++]);
		start_args++;
	}
		
	
/*	else
		commands = read_commands();
*/
	return (0);
}
