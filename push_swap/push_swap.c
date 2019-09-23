
#include "push_swap.h"

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

int	check_previous_swaps(int *stack_a, int *stack_b, int *commands)
{
	if (stack_a[0] < 3 || stack_b[0] < 3)
		return (1);
	if (commands[0] > 1 && commands[commands[0] - 1] == 8)
		return (1);
	if (commands[0] > 2 && commands[commands[0] - 1] == 3)
		if(commands[commands[0] - 2] == 0)
			return (1);
	if (commands[0] > 2 && commands[commands[0] - 1] == 0)
        	if(commands[commands[0] - 2] == 3)
                	return (1);
	return (0);
}

int	check_push_prerequisites(int i, int *stack_a, int *stack_b)
{
	if (i == 6 && stack_b[0] == 1)
		return (0);
	if (i == 7 && stack_a[0] == 1)
		return (0);
	return (1);
}

int	check_rotate(int i, int *stack, int *commands)
{
	if (stack[0] < 3)
		return (1);
	if (commands[0] > 1)
	{
		if (stack[0] == 3 && commands[commands[0] - 1] == i)
			return (1);
		if (i == 1 && commands[commands[0] - 1] == 2)
			return (1);
		if (i == 2 && commands[commands[0] - 1] == 1)
			return (1);
		if (i == 4 && commands[commands[0] - 1] == 5)
			return (1);
		if (i == 5 && commands[commands[0] - 1] == 4)
			return (1);
	}
	return (0);
}

int	check_double_rotate(int i, int *stack_a, int *stack_b, int *commands)
{
	if (stack_a[0] < 3 || stack_b[0] < 3)
		return (1);
	if (commands[0] < 2)
		return (0);
	if (stack_a[0] == 3 || stack_b[0] == 3)
	{
		if (i == commands[commands[0] - 1])
			return (1);
		if (commands[0] > 2 && commands[commands[0] - 1] == i - 5 && commands[commands[0] - 2] == i - 8)
			return (1);
		if (commands[0] > 2 && commands[commands[0] - 1] == i - 8 && commands[commands[0] - 2] == i - 5)
			return (1);
	}
	if (i == 9 && commands[commands[0] - 1] == 10)
		return (1);
	if (i == 10 && commands[commands[0] - 1] == 9)
		return (1);
	return (0);
}

int	can_do_action(int i, int *stack_a, int *stack_b, int *commands)
{
	if (commands[0] > 1)
	{
		if (i == 0 && commands[commands[0] - 1] == 0)
			return (0);
		if (i == 3 && commands[commands[0] - 1] == 3)
			return (0);
	}
	if (i == 8 && check_previous_swaps(stack_a, stack_b, commands))
		return (0);
	if ((i == 6 || i == 7) && !(check_push_prerequisites(i, stack_a, stack_b)))
		return (0);
	if (i == 1 || i == 2 )
		if (check_rotate(i, stack_a, commands))
			return (0);
	if (i == 4 || i == 5 )
		if (check_rotate(i, stack_b, commands))
			return (0);
	if (i == 9 || i == 10)
		if (check_double_rotate(i, stack_a, stack_b, commands))
			return (0);
	return (1);
}

void	print_array(int *array)
{
	int i;

	i = 1;
	while (i < array[0])
		printf ("command is %i\n", array[i++]);
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

void    run_command(int command, int *stack)
{       
        void    (*f_point[3])();
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

void	perform_operation(int *stack_a, int *stack_b, int command)
{
	if (command < 3)
		run_command(command, stack_a);
        if (command > 2 && command < 6)
                run_command(command, stack_b);
        if (command == 6)
                stack_a = push(stack_b, stack_a);
        if (command == 7)
                stack_b = push(stack_a, stack_b);
        if (command > 7)
        {
        	run_command(command, stack_a);
        	run_command(command, stack_b);
        }
}

void	r_push_swap(int *stack_a, int *stack_b, int *commands)
{
	int options[11] = {0,1,2,3,4,5,6,7,8,9,10};
	int i;

	// perform the last command on the stacks:
	perform_operation(stack_a, stack_b, commands[commands[0] - 1]);
	// Base-case:
	if (check_sorted(stack_a, stack_b))
	{
		print_array (commands);	
		exit(0);
	}
	// run through the array of possible actions:
	i = 0;
	while (i < 12)
	{
		if (can_do_action(i, stack_a, stack_b, commands))
		commands = push_end(commands, options[i]);
		r_push_swap(stack_a, stack_b, commands);
		commands[0] -= 1;
		i++;
	}
}

void	push_swap(int *stack_a)
{
	int	*stack_b;
	int	*commands;

	stack_b = initialize_stack();
	commands = initialize_stack();
	if (check_sorted(stack_a, stack_b))
		return;
	r_push_swap(stack_a, stack_b, commands);

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
