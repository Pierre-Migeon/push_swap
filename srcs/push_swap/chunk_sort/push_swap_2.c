#include "push_swap.h"

int	check_input(int argc, char **argv)
{
        int i;

        i = 1;
	while (i < argc && is_flag(argv[i]))
		i++;
        while (i < argc)
        {
                if (!(check_int(argv[i])))
                        return (1);
                if (check_seen(argv, i))
                        return (1);
                ++i;
        }
        return (0);
}

int	check_sorted(int *stack_a)
{
        int i;

        i = 2;
        while (i < stack_a[0])
        {
		if (stack_a[i] < stack_a[i - 1])
			return (0);
                i++;
        }
        return (1);
}

int	*get_stack(int argc, char **argv)
{
        int *stack;
        int i;
	int x;

	i = 0;
	while (i < argc && is_flag(argv[i + 1]))
		i++;
        if (!(stack = (int *)malloc(sizeof(int) * (argc - i))))
                return (0);
        stack[0] = argc - i;
        x = 1;
        while (x < stack[0])
        {
	      	stack[x] = ft_atoi(argv[x + i]);
		++x;
	}	
        return (stack);
}

int	*initialize_stack(void)
{
        int *out;

	if (!(out = (int *)malloc(sizeof(int) * 1)))
		return (0);
	out[0] = 1;
        return (out);
}

int	*push_end(int *commands, int option)
{
	int *new_commands;
	int i;

	commands[0] += 1;
	if (!(new_commands = (int *)malloc(sizeof(int) * commands[0])))
		error();
	i = -1;
	while (++i < commands[0] - 1)
		new_commands[i] = commands[i];
	new_commands[i] = option;
	free(commands);
	return (new_commands);
}
