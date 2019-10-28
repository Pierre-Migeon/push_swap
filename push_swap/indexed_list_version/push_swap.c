#include "push_swap.h"

/*
You should probably remove the whole "max index" bit, I'm leaving it in for now incase that it comes in handy later, but don't think it will.
What happens with the "is sorted" function if you only have one item in stack_a? Check this edge case.
*/

typedef struct s_llist
{
	int	val;
	int	index;
	int	keep;
	int	max_index;
	struct s_llist *next;
	struct s_llist *last;
} 	t_llist;


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

int	get_dir_2(int *stack_a, int smallest)
{
	int	forward = 0;
	int	backward = 0;
	int	i = 1;

	while (i < stack_a[0])
	{
		if (stack_a[i] > stack_a[i + 1] && stack_a[i + 1] != smallest)
			forward = i - 1;
		i++;
	}
	i--;
	while (i > 0)
        {
		if (stack_a[i] > stack_a[i + 1] && stack_a[i + 1] != smallest)
			backward = stack_a[0] - i;
		--i;
	}
	return((backward <= forward) ? 2 : 1);
}

int	get_dir(int *stack_a, int *stack_b, int smallest, int largest)
{
	int 	forward = 0;
	int 	backward = 0;
	int 	i;

	i = 1;
	if (stack_b[0] > 1)
	{
		while (i < stack_a[0])
		{
			if (stack_a[i] > stack_b[1] || (stack_a[i] == smallest && stack_b[1] == largest))
				forward = i - 1;
			++i;
		}
		while (i > 0)
		{
			if (stack_a[i] > stack_b[1] || (stack_a[i] == smallest && stack_b[1] == largest))
				backward = stack_a[0] - i;
			--i;
		}
		return ((backward <= forward) ? 2 : 1);
	}
	else
		return (get_dir_2(stack_a, smallest));
}

















int	edge_indexes(t_llist *stack, int ref_index)
{
	int 	first_index;
	int	out_index;

	first_index = stack->index;
	out_index = ref_index;
	while (stack)
	{
		if (ref_index == 0)
			if (stack->index > out_index)
				out_index = stack->index;
		if (ref_index != 0)
			if (stack->index < out_index)
				out_index = stack->index;
		stack = stack->next;
		if (stack->index == first_index)
			break;
	}
	return (out_index);
}

int	not_sorted(t_llist *stack)
{
	int tracking[2];
	int min;
	int max;

	tracking[0] = stack->val;
	tracking[1] = stack->index;
	max = edge_indexes(stack, 0);
	min = edge_indexes(stack, max);
	while(stack)
	{
		if (tracking[1] != stack->index && tracking[1] != stack->index - 1)
			if (tracking[1] != max || stack->index != min)
				return (1);
		if (stack->next->val == tracking[0])
			break;
		tracking[1] = stack->index;
		stack = stack->next;
	}
	return (0);
}

void	push_a(t_llist **stack_a, t_llist **stack_b, int **commands)
{
	t_llist *temp;

        *commands = push_end(*commands, 6);
	temp = *stack_b;
	if ((*stack_b)->next == *stack_b)
		*stack_b = NULL;
	else
	{
		*stack_b = (*stack_b)->next;
		(*stack_b)->last->last->next = *stack_b;
		(*stack_b)->last = (*stack_b)->last->last;
	}
	(*stack_a)->last->next = temp;
	temp->next = *stack_a;
	temp->last = (*stack_a)->last;
	(*stack_a)->last = temp;
	*stack_a = (*stack_a)->last;
}

void	push_b(t_llist **stack_a, t_llist **stack_b, int **commands)
{
	t_llist *temp;

	*commands = push_end(*commands, 7);
	if (!*stack_b)
	{
		*stack_b = *stack_a;	
		(*stack_a)->next->last = (*stack_a)->last;
		(*stack_a)->last->next = (*stack_a)->next;
		(*stack_a) = (*stack_a)->next;
		(*stack_b)->last = (*stack_b);
		(*stack_b)->next = (*stack_b);
		return;
	}
	temp = *stack_a;
	(*stack_a) = (*stack_a)->next;
	(*stack_a)->last->last->next = (*stack_a);
	(*stack_a)->last = (*stack_a)->last->last;
	temp->next = *stack_b;
	temp->last = (*stack_b)->last;
	(*stack_b)->last->next = temp;
	(*stack_b)->last = temp;
	*stack_b = (*stack_b)->last;
}

int	shortest_path(t_llist *stack)
{
	t_llist		*ra;
	t_llist		*rra;

	ra = stack;
	rra = stack;
	while (1)
	{
		if (ra->keep == 0)
			return (1);
		if (rra->keep == 0)
			return (2);
		ra = ra->next;
		rra = rra->last;
	}
	return (1);
}

int	check_push_a(t_llist *stack_a, t_llist *stack_b)
{
	int max;
	int min;

	max = edge_indexes(stack_a, 0);
	min = edge_indexes(stack_a, max);
	if (stack_a->index > stack_b->index && stack_a->last->index < stack_b->index)
		return (1);
	if (stack_b->index < min && stack_a->index == min)
		return (1);
	if (stack_b->index > max && stack_a->last->index == max)
		return (1);
	return (0);
}

void	print_stacks(t_llist *a, t_llist *b)
{
	int first;

	first = a->index;
	while(a)
	{
		printf ("%i->", a->val);
		a = a->next;
		if (a->index == first)
			break;
	}
	printf ("\n");
        while(a)
        {
                printf ("%i->", a->index);
                a = a->next; 
                if (a->index == first)
                        break;
        }
	printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	if (b)
		printf ("%i->", b->val);
	printf ("\n");
	if (b)
        	printf ("%i->", b->index);
	printf ("\n");
}

void	print_one_stack(t_llist *stack)
{
	int first;

	first = stack->index;
	while(stack)
	{
		printf ("%i->", stack->val);
		stack = stack->next;
		if (stack->index == first)
			break;
	}
	printf ("\n\n");
}


int	shortest_path_2(t_llist *stack_a)
{
	t_llist *ra;
	t_llist	*rra;

	ra = stack_a;
	rra = stack_a;

	while (1)
	{
		if (ra->index == 0)
			return (1);
		if (rra->index == 0)
			return (2);
		ra = ra->next;
		rra = rra->last;
	}
	return (1);
}



void	push_swap_indexed(t_llist *stack_a, int **commands)
{
	t_llist *stack_b = NULL;
	int	dir;

	while (not_sorted(stack_a))
	{
		dir = shortest_path(stack_a);
		if (stack_a->keep == 0)
			push_b(&stack_a, &stack_b, commands);
		else
		{
			stack_a = (dir == 1) ? stack_a->next : stack_a->last;
			*commands = push_end(*commands, dir);
		}
	}
	while (stack_b)
	{
		if (check_push_a(stack_a, stack_b))
			push_a(&stack_a, &stack_b, commands);
		else
                {       
                       	stack_a = stack_a->next;
                        *commands = push_end(*commands, 1);
                }
	}	
	while (stack_a->index != 0)
	{
		dir = shortest_path_2(stack_a);
		stack_a = (dir == 1) ? stack_a->next : stack_a->last;
		*commands = push_end(*commands, dir);
	}
}

void	free_arrays(int *stack_a, int *stack_b, int *commands)
{
	free(stack_a);
	free(stack_b);
	free(commands);
}

typedef struct  s_hash
{
        int     current_score;
	int	best_score;
	int	best_index;
        int     head_index;
	int	last_index;
	int	final_index;
}       t_hash;

int	reset_and_test_hash(t_hash *best)
{
	if (best->head_index == -1)
	{
		best->current_score = 0;
		best->best_score = 0;
		best->best_index = 0;
		best->head_index = 0;
		best->last_index = -1;
		best->final_index = -1;
		return (1);
	}
	else if (best->head_index == best->final_index)
		return (0);
	else
	{
		if (best->current_score > best->best_score)
		{
			best->best_score = best->current_score;
			best->best_index = best->head_index;
		}
		best->final_index = -1;
		best->last_index = best->head_index;
		best->current_score = 0;
		best->head_index++;
		return (1);
	}
	return (0);
}

t_llist	*label(t_llist *head, t_hash best)
{
	t_llist		*ref;
	int		current_index;
	int		i;

	current_index = best.best_index - 1;
	ref = head;
	i = 0;
	while (i < 2)
	{
		if (head->index == current_index + 1)
		{
			head->keep = 1;
			current_index++;
		}
		else
			head->keep = 0;
		head = head->next;
		if (head->index == best.best_index)
			++i;
	}
	return (ref);
}

t_llist	*classify(t_llist *head)
{
	t_llist		*ref;
	t_hash		best;
	int		i;

	best.head_index = -1;
	ref = head;
	while (reset_and_test_hash(&best))
	{
		while(head->index != best.head_index)
			head = head->next;
		i = 0;
		while (best.final_index < 0)
		{
			if (head->index == best.last_index + 1)
			{
				best.last_index++;
				best.current_score++;
			}
			if (head->next->index == best.head_index)
				best.final_index = i;
			head->next->last = head;
			head = head->next;
			++i;
		}
	}
	return (label(ref, best));
}

int	next_bigger_index(int *stack, int value)
{
	int	i;
	int	j;
	int	next;

	i = 1;
	j = 1;
	next = value;
	while (i < stack[0])
	{
		if (stack[i] > value)
		{
			if (next == value)
			{
				next = stack[i];
				j = i;
			}
			else if (stack[i] < next)
			{
				next = stack[i];
				j = i;
			}
		}
		++i;
	}
	return (j);
}

int	smallest_index(int *things)
{
	int 	i;
	int	j;
	int 	small;

	small = things[1];
	i = j = 1;
	while (i < things[0])
	{
		if (things[i] < small)
		{
			j = i;
			small = things[i];
		}
		++i;
	}
	return (j);
}

int	*index_stack(int *stack)
{
	int	*out;
	int	i = 1;
	int	j = 0;

	if (!(out = (int *)malloc(sizeof(int) * stack[0])))
		error();
	out[0] = stack[0];
	while (j < stack[0] - 1)
	{	
		if (j == 0)
			i = smallest_index(stack);
		else
			i = next_bigger_index(stack, stack[i]);
		out[i] = j++;
	}
	return (out);
}

void	init_node(t_llist *node, int val, int index, int max)
{
	node->val = val;
	node->index = index;
	node->max_index = max;
}

t_llist	*make_order(int *stack_a)
{
	t_llist		*order;
	t_llist 	*head;
	int		*indexes;
	int		i;

	i = 1;
	if (!(order = (t_llist *)malloc(sizeof(t_llist))))
		error();
	indexes = index_stack(stack_a);
	head = order;
	while (i < stack_a[0])
	{
		init_node(order, stack_a[i], indexes[i], stack_a[0] - 2);
		if (i < stack_a[0] - 1)
		{
			if (!(order->next = (t_llist *)malloc(sizeof(t_llist))))
				error();
			order = order->next;
		}
		else
			order->next = head;
		++i;
	}
	free(indexes);
	return (classify(head));
}

void	push_swap(int *stack_a)
{
	int		*stack_b;
	int		*commands;
	t_llist		*order;

	stack_b = initialize_stack();
	commands = initialize_stack();
	order = make_order(stack_a);
	if (check_sorted(stack_a, stack_b))
		return;
	push_swap_indexed(order, &commands);
	ints_to_commands(commands);
//	free_arrays(stack_a, stack_b, commands);
}

int	main(int argc, char **argv)
{
	if (argc < 2 || !argv)
		error();
	if (check_input(argc, argv))
		error();

//	int artificial_stack_a[11] = {6, 1, 5, 4, 3, 2};
//	push_swap(artificial_stack_a);
	push_swap(get_stack(argc, argv));
	return (0);
}
