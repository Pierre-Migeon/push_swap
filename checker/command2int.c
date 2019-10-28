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
