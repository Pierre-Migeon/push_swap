#include "push_swap.h"

typedef struct s_command_scores
{
	int	max_score;

	int s_sa;
	int s_ra;
	int s_rra;
	int s_sb;
	int s_rb;
	int s_rrb;
	int s_pa;
	int s_pb;
	int s_ss;
	int s_rr;
	int s_rrr;
}	t_c_scores;

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
	if (i == 6 && stack_b[0] < 2)
		return (0);
	if (i == 7 && stack_a[0] < 2)
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
		if (i == 0 && (commands[commands[0] - 1] == 0 || stack_a[0] < 3))
			return (0);
		if (i == 3 && (commands[commands[0] - 1] == 3 || stack_b[0] < 3))
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
	return(1);
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
	print_array(*stack_a);
	print_array(*stack_b);
}

void	reverse_operation(int **stack_a, int **stack_b, int command)
{
	if (command == 0)
		swap(((*stack_a) + 1), ((*stack_a) + 2));
	if (command == 1)
		run_command(2, *stack_a);
	if (command == 2)
		run_command(1, *stack_a);
	if (command == 3)
		swap(((*stack_b) + 1), ((*stack_b) + 2));
	if (command == 4)
		run_command(5, *stack_b);
	if (command == 5)
		run_command(4, *stack_b);
	if (command == 6)
		*stack_b = push(*stack_a, *stack_b);
	if (command == 7)
		*stack_a = push(*stack_b, *stack_a);
	if (command == 8)
	{
		run_command(8, *stack_a);
		run_command(8, *stack_b);
	}
	if (command == 9)
	{
		run_command(10, *stack_a);
		run_command(10, *stack_b);
	}
	if (command == 10)
	{
		run_command(9, *stack_a);
                run_command(9, *stack_b);
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

int	*replace_commands(int *commands, int *commands_2)
{
	int 	*out;
	int 	i;

	i = 0;
	if (!(out = (int *)malloc(sizeof(int) * commands[0])))
		error();
	while (i < commands[0])
	{
		out[i] = commands[i];
		i++;
	}
	free(commands_2);
	return (out);
}

void	dep_check(int *depth_check, int max_depth, int *depth)
{
	if (*depth_check != max_depth)
	{
		*depth_check += 1;
		*depth = 0;
	}
	*depth += 1;
}

int	score_it(int *stack_a, int *stack_b)
{
	int i;
	int off;

	i = 0;
	off = 0;
	while (stack_a[0] > 2 && ++i < stack_a[0] - 1)
		if (stack_a[i] > stack_a[i + 1])
			off++;
	i = 0;
	while (stack_b[0] > 2 && ++i < stack_b[0] - 1)
		if (stack_b[i] < stack_b[i + 1])
			off++;
	return (off);
}

int	should_do_action(int command, int **stack_a, int **stack_b)
{
	int score_1;
	int score_2;

	score_1 = score_it(*stack_a, *stack_b);
	perform_operation(stack_a, stack_b, command);
	score_2 = score_it(*stack_a, *stack_b);
	reverse_operation(stack_a, stack_b, command);
	if (score_2 < score_1)
		return (1);
	return (0);
}

void	r_push_swap(int **stack_a, int **stack_b, int **commands, int max_depth)
{
	int 		i;
	static int 	depth = 0;
	static int	depth_check = 1;
	
	dep_check(&depth_check, max_depth, &depth);
	if (depth == max_depth)
		return;
	if (!(i = 0) && check_sorted(*stack_a, *stack_b))
	{
		if (*(*(commands + 1) + 0) == 1 || *(*(commands + 1)) > *(*(commands)))
			(*(commands + 1)) = replace_commands(*commands, *(commands + 1));
		print_array(*commands);
		return ;
	}
	while (i < 11)
	{
		if (can_do_action(i, *stack_a, *stack_b, *commands) )// && should_do_action(i, stack_a, stack_b))
		{
			*commands = push_end(*commands, i);
			print_array(*commands);
			perform_operation(stack_a, stack_b, (*(commands))[(*(commands))[0] - 1]);
			r_push_swap(stack_a, stack_b, commands, max_depth);
			depth--;
			reverse_operation(stack_a, stack_b, (*(commands))[(*(commands))[0] - 1]);
			(*(commands))[0] -= 1;
		}
		i++;
	}
}

void	prepare_for_push(int **stack_a, int **stack_b, int new_value)
{
	int i = 1;
	int insertion_point;
	int reference;

	insertion_point = 0;
	//if it's already the biggest value, then don't touch array B
	if (new_value > *(*(stack_b) + 1))
		return;
	//find out where it fits:
	while (i < **stack_b)
	{
		if (*(*(stack_b) + i) < new_value) 
		{
			insertion_point = 1;
			break;
		}
		i++;
	}
	reference = *(*(stack_b) + i);
	if (insertion_point)
	{
		if (i - 1 <= **stack_b - i)
			while (*(*(stack_b) + 1) != reference)
				perform_operation(stack_a, stack_b, 4);
		else
			while (*(*(stack_b) + 1) != reference)
                                perform_operation(stack_a, stack_b, 5);
	}
}

void	rotate_back_normal(int **stack_a, int **stack_b)
{
	int i;
	int max;
	int max_i;

	if (**stack_b < 3)
		return ;
	i = 1;
	max = *(*(stack_b) + 1);
	max_i = 1;
	while (i < *(*(stack_b)))
	{
		if (*(*(stack_b) + i) > max)
		{
			max_i = i;
			max = *(*(stack_b) + i);
		}		
		i++;
	}
	if (max_i - 1 <= **stack_b - max_i)
		while (*(*(stack_b) + 1) != max)
			perform_operation(stack_a, stack_b, 4);
	else
		while (*(*(stack_b) + 1) != max)
			perform_operation(stack_a, stack_b, 5);
}

void	push_swap_two(int **stack_a, int **stack_b, int **commands)
{
	while (!(check_sorted(*stack_a, *stack_b)))
	{
		//Swap a if it helps or swap both if you can
		if (**stack_a > 2 && *(*(stack_a) + 1) > *(*(stack_a) + 2))
		{
			if (*(*(stack_b) + 1) < *(*(stack_b) + 2))
				perform_operation(stack_a, stack_b, 8);
			else
				perform_operation(stack_a, stack_b, 0);
		}
		//or just swap B if it helps
		if (**stack_b > 2 && (*(*(stack_b) + 1) < *(*(stack_b) + 2)))
			perform_operation(stack_a, stack_b, 3);
		//push onto b
		prepare_for_push(stack_a, stack_b, (*(stack_a))[1]);
		perform_operation(stack_a, stack_b, 7);
		rotate_back_normal(stack_a, stack_b);
		//if there's nothing left in stack_a, then push everything back onto that.
		if ((*(stack_a))[0] < 3)
			while((*(stack_b))[0] > 1)
				perform_operation(stack_a, stack_b, 6);
	}
}

void	free_arrays(int *stack_a, int *stack_b, int **commands)
{
	free(stack_a);
	free(stack_b);
	free(*(commands + 1));
	free(*commands);
	free(commands);
}

void	push_swap(int *stack_a)
{
	int	*stack_b;
	int	**commands;
	int	max_depth;

	max_depth = 1;
	if (!(commands = (int **)malloc(sizeof(int *) * 2)))
		error();
	stack_b = initialize_stack();
	*commands = initialize_stack();
	*(commands + 1) = initialize_stack();
	if (check_sorted(stack_a, stack_b))
		return;
	push_swap_two(&stack_a, &stack_b, commands);
	ints_to_commands(*(commands + 1));
	free_arrays(stack_a, stack_b, commands);
}

int	main(int argc, char **argv)
{
	if (argc < 2 || !argv)
		error();
//	if (check_input(argc, argv))
//		error();
	push_swap(get_stack(argc, argv));
	return (0);
}
