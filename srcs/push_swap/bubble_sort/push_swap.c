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

void	print_array(int *array)
{
	int i;

	i = 1;
	while (i < array[0])
		printf ("%i ", array[i++]);
	printf ("\n");
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

void	perform_operation(int **stack_a, int **stack_b, int command)
{
	if (command < 3)
		run_command(command, *stack_a);
        if (command > 2 && command < 6)
                run_command(command, *stack_b);
        if (command == 6)
                *stack_a = push(*stack_b, *stack_a);
        if (command == 7)
                *stack_b = push(*stack_a, *stack_b);
        if (command > 7)
        {
        	run_command(command, *stack_a);
        	run_command(command, *stack_b);
        }
}

char	*command_convert(int i)
{
	if (i == 0)
		return ("sa\n");
	if (i == 1)
		return ("ra\n");
	if (i == 2)
		return ("rra\n");
	if (i == 3)
		return ("sb\n");
	if (i == 4)
		return ("rb\n");
	if (i == 5)
		return ("rrb\n");
	if (i == 6)
		return ("pa\n");
	if (i == 7)
		return ("pb\n");
	if (i == 8)
		return ("ss\n");
	if (i == 9)
		return ("rr\n");
	if (i == 10)
		return ("rrr\n");
	return ("Error\n");
}

void	ints_to_commands(int *commands)
{
	int i;

	i = 1;
	while (i < commands[0])
		ft_putstr(command_convert(commands[i++]));
}

int	id_largest(int *stack)
{
	int i;
	int largest;

	i = 1;
	largest = stack[1];
	while (i < stack[0])
	{
		if (stack[i] > largest)
			largest = stack[i];
		i++;
	}
	return (largest);
}

int     id_smallest(int *stack)
{
        int i;
        int smallest;

        i = 1;
        smallest = stack[1];
        while (i < stack[0])
        {       
                if (stack[i] < smallest)
                        smallest = stack[i];
                i++;
        }
        return (smallest);
}

int	check_rotate_dir(int *stack_a, int min)
{
	int	i;
	int	min_in;

	i = 1;
	while (i < stack_a[0] - 1)
	{
		if (stack_a[i + 1] != min && stack_a[i] > stack_a[i + 1])
			return (1);
		if (stack_a[i] == min)
			min_in = i;
		++i;
	}
	if ((min_in - 1) >= (stack_a[0] - min_in)) 
		return (0);
	return (1);
}

void	push_swap_bsort(int *stack_a, int *stack_b, int **commands)
{
	int 	smallest;
	int 	largest;
	int 	flag;

	smallest = id_smallest(stack_a);
	largest = id_largest(stack_a);
	while (!(check_sorted(stack_a, stack_b)))
	{
		if (*(stack_a + 1) > *(stack_a + 2) && (*(stack_a + 1) != largest || *(stack_a + 2) != smallest))
		{
			perform_operation(&stack_a, &stack_b, 0);
			*commands = push_end(*commands, 0);
		}
		if(check_rotate_dir(stack_a, smallest))
	        {
			perform_operation(&stack_a, &stack_b, 1);
        	        *commands = push_end(*commands, 1);
		}
		else
		{
			perform_operation(&stack_a, &stack_b, 2);
                        *commands = push_end(*commands, 2);
		}
	}
}

void	free_arrays(int *stack_a, int *stack_b, int *original, int *commands)
{
	free(stack_a);
	free(stack_b);
	free(original);
//	free(commands);
}

int	*copy_original(int *stack_a)
{
	int i;
	int *copy;

	i = 0;
	if (!(copy = (int *)malloc(sizeof(int) * stack_a[0])))
		error();
	copy[0] = stack_a[0];
	while (++i < stack_a[0])
		copy[i] = stack_a[i];
	return (copy);
}

void	push_swap(int *stack_a)
{
	int	*stack_b;
	int	**commands;
	int	*original;

	stack_b = initialize_stack();
	commands[0] = initialize_stack();
	commands[1] = initialize_stack();
	original = copy_original(stack_a);
	if (check_sorted(stack_a, stack_b))
		return;
	push_swap_bsort(stack_a, stack_b, &commands[0]);
	ft_memcpy(stack_a, original, original[0] * sizeof(int));
		
	ints_to_commands(commands[0]);
	free_arrays(stack_a, stack_b, original, commands[0]);
}

int	main(int argc, char **argv)
{
	if (argc < 2 || !argv)
		error();
	if (check_input(argc, argv))
		error();
	push_swap(get_stack(argc, argv));
	return (0);
}
