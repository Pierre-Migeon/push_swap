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
	free_arrays(stack_a, stack_b, commands);
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
