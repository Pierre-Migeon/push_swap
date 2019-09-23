
#include "push_swap.h"


void	pop_stack(int *stack)
{
	int	i;

	i = 0;
	while (++i < stack[0] - 1)
		stack[i] = stack[i+ 1];
	if (stack[0] > 1)
		stack[0] -= 1;
}

void    swap(int *a, int *b)
{       
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
}

void    rotate(int *stack)
{       
        int i;
        
        i = 1;
        while (i < stack[0] - 1)
        {       
                swap(&stack[i], &stack[i + 1]);
                ++i;
        }
}

void    reverse_rotate(int *stack)
{       
        int stack_size = stack[0];
        
        while(--stack_size > 1)
                swap(&stack[stack_size], &stack[stack_size - 1]);
}

int     remove_top(int *stack)
{       
        int out;
        int i;
        
        i = 1;
        out = stack[1];
        while (i < stack[0] - 1)
        {       
                stack[i] = stack[i + 1];
                i++;
        }
        stack[0] -= 1;
        return (out);
}

int     *push(int *stack_source, int *stack_destination)
{       
        int *out;
        int pushed_element;
        int i;
        
        if (stack_source[0] == 1)
                return (stack_destination);
        pushed_element = remove_top(stack_source);
        stack_destination[0] += 1;
        if (!(out = (int *)malloc(sizeof(int) * stack_destination[0])))
                return (0);
        out[0] = stack_destination[0];
        out[1] = pushed_element;
        i = 2;
        while(i < stack_destination[0])
        {
                out[i] = stack_destination[i - 1];
                i++;
        }
        free(stack_destination);
        return (out);
}

void	error(void)
{
	write(1, "Error\n", 6);
	exit (0);
}

int	check_int(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
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

int     check_input(int argc, char **argv)
{       
        int i;
        
        i = 1;
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

int     check_sorted(int *stack_a, int *stack_b)
{       
        int i;
        
        if (stack_b[0] > 1)
                return (0);
        i = 2;
        while (i < stack_a[0])
        {               
		if (stack_a[i] < stack_a[i - 1])
			return (0);
                i++;
        }
        return (1);
}

int     *get_stack(int argc, char **argv)
{       
        int *stack;
        int i;
        
        if (!(stack = (int *)malloc(sizeof(int) * argc)))
                return (0);
        stack[0] = argc;
        i = 1;
        while (i < stack[0])
        {       
               	stack[i] = ft_atoi(argv[i]);
                ++i;
        }
        return (stack);
}

int     *initialize_stack(void)
{       
        int *out;
        
        if (!(out = (int *)malloc(sizeof(int) * 1)))
                return (0);
        out[0] = 1;
        return (out);
}

void	push_swap(int *stack_a)
{
	int	*stack_b;
	int	*commands;

	stack_b = initialize_stack();
	commands = initialize_stack();
	if (check_sorted(stack_a, stack_b))
		return;
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		error();
	if (check_input(argc, argv))
		error();
	push_swap(get_stack(argc, argv));
	return (0);
}
