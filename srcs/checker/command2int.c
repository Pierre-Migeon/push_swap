#include "checker.h"

int     command_to_int(char *operation)
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
	return (-1);
}

int	check_commands(int *commands)
{
	int i;

	i = 1;
	while (i < commands[0])
	{
		if (commands[i] == -1)
			return (1);
		++i;
	}
	return (0);
}

void	print_stack(int *stack_a, int *stack_b)
{
	int i;
	int j;
	char *str;

	i = 1;
	while (i < stack_a[0])
	{
		j = 0;
		str = ft_itoa(stack_a[i++]);
		while (*(str + j))
			write(1, (str + j++), 1);
		write(1, " ", 1);
		free(str);
	}
	write(1, "\n", 1);
	i = 1;
	if (stack_b[0] > 1)
		write(1, "Stack_B: \n", 10);
	else
		return ;
	while (i < stack_b[0])
		write(1, &stack_b[i++], 1);
}
