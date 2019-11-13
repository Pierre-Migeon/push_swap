#include "push_swap.h"

//Question: Is it really worthwhile to be sorting the three very first and last separately? Test this to see if this is actually saving any steps...

int	find_median(t_llist *stack_a)
{
	int		num_elements;
	int		even;
	t_llist		*head;

	num_elements = 1;
	head = stack_a;
	stack_a = stack_a->next;
	while (stack_a != head && (num_elements++) && (stack_a = stack_a->next))
		;
	even = (num_elements % 2) ? 0 : 1;
	while (stack_a->index != num_elements / 2 - even)
		stack_a = stack_a->next;
	if (!(even))
		return (stack_a->val);
	num_elements = stack_a->val;
	even = stack_a->index;
	while (stack_a->index != even + 1)
		stack_a = stack_a->next;
	return ((num_elements + stack_a->val) / 2);
}

int	is_lower_than_median(t_llist *stack_a, int median)
{
	t_llist *head;

	head = stack_a;
	if (stack_a->val <=  median)
		return (1);
	stack_a = stack_a->next;
	while (stack_a != head)
	{
		if (stack_a->val <=  median)
                	return (1);
		stack_a = stack_a->next;
	}
	return (0);
}

int	bottom_three(t_llist *stack_a)
{
	int 		lowest[4];
	t_llist 	*head;

	lowest[3] = edge_indexes(stack_a, 0);
	lowest[0] = lowest[3];
	lowest[1] = lowest[3];
	lowest[2] = lowest[3];
	head = stack_a;
	while((stack_a = stack_a->next))
	{
		if (stack_a->index < lowest[0])
		{
			lowest[2] = lowest[1];
			lowest[1] = lowest[0];
			lowest[0] = stack_a->index;
		}
		else if (stack_a->index < lowest[1])
		{
			lowest[2] = lowest[1];
			lowest[1] = stack_a->index;
		}
		lowest[2] = (stack_a->index < lowest[2]) ? stack_a->index : lowest[2];
		if (stack_a == head)
			break;
	}
	return ((head->index == lowest[0]) || (head->index == lowest[1]) || (head->index == lowest[2]));
}

int     quickest_path(t_llist *stack_a)
{       
        t_llist *ra;
        t_llist *rra;
        
        ra = stack_a;
        rra = stack_a;
        while (1)
        {       
                if (bottom_three(ra))
                        return (1);
                else if (bottom_three(rra))
                        return (2);
                ra = ra->next;
                rra = rra->last;
        }
        return (0);
}

int	quickest_path_2(t_llist *stack_b, int max_index)
{
        t_llist *ra;
        t_llist *rra;

        ra = stack_b;
        rra = stack_b;
	while (1)
	{
		if (ra->index == max_index)
			return (4);
		if (rra->index == max_index)
			return (5);
		ra = ra->next;
		rra = rra->last;
	}
	return(0);
}

void	print_stacks(t_llist *a, t_llist *b)
{
	int first;

	first = a->val;
	while(a)
	{
		printf ("%i->", a->val);
		a = a->next;
		if (a->val == first)
			break;
	}
	printf ("\n");
	first = b->val;
        while(b)
        {
                printf ("%i->", b->index);
                b = b->next; 
                if (b->val == first)
                        break;
        }
	printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

int	stack_a_too_big(t_llist *stack_a)
{
	t_llist 	*head;
	int 		i;

	i = 1;
	head = stack_a;
	stack_a = stack_a->next;
	while (stack_a != head)
	{
		++i;
		stack_a = stack_a->next;
	}
	return ((i > 3) ? 1 : 0);
}

int	three_in(t_llist *stack_b)
{
	t_llist         *head;
	int		i;
	
	if (!stack_b)
		return (0);
	i = 1;
	head = stack_b;
	stack_b = stack_b->next;
	while (stack_b != head)
	{
		++i;
		stack_b = stack_b->next;
	}
	return ((i == 3) ? 1 : 0);
}

int	list_swap(t_llist **stack, int **commands, int i)
{
	*commands = push_end(*commands, i);
	(*stack)->last->next = (*stack)->next;
	(*stack)->next->last = (*stack)->last;
	(*stack)->next = (*stack)->next->next;
	(*stack)->last = (*stack)->next->last;
	(*stack)->next->last = *stack;
	(*stack)->last->next = *stack;
	*stack = (*stack)->last;
	return (1);
}

int	list_rotate(t_llist **stack, int **commands, int i)
{
	*stack = (i == 1 || i == 4) ? (*stack)->next : (*stack)->last;
	*commands = push_end(*commands, i);
	return (1);
}

void	sort_b(t_llist **stack_b, int **commands)
{
	int max;
	int min;

	max = edge_indexes(*stack_b, 0);
	min = edge_indexes(*stack_b, max);
	if ((*stack_b)->index == max && (*stack_b)->last->index == min)
		return ;
	if ((*stack_b)->index == max && (*stack_b)->next->index == min)
		if (list_swap(stack_b, commands, 3) && list_rotate(stack_b, commands, 4))
			;
	if ((*stack_b)->next->index == max && (*stack_b)->last->index == min)
		list_swap(stack_b, commands, 3);
	if ((*stack_b)->next->index == min && (*stack_b)->last->index == max)
		list_rotate(stack_b, commands, 5);
	if ((*stack_b)->index == min && (*stack_b)->last->index == max)
		if (list_swap(stack_b, commands, 3) && list_rotate(stack_b, commands, 5))
			;
	if ((*stack_b)->index == min && (*stack_b)->next->index == max)
		list_rotate(stack_b, commands, 4);
}

void    sort_a(t_llist **stack_a, int **commands)
{       
        int max;
        int min;
        
        max = edge_indexes(*stack_a, 0);
        min = edge_indexes(*stack_a, max);
        if ((*stack_a)->index == min && (*stack_a)->last->index == max)
                return ;
        if ((*stack_a)->index == max && (*stack_a)->next->index == min)
                list_rotate(stack_a, commands, 1);
        if ((*stack_a)->next->index == max && (*stack_a)->last->index == min)
                list_rotate(stack_a, commands, 2);
        if ((*stack_a)->next->index == min && (*stack_a)->last->index == max)
                list_swap(stack_a, commands, 0);
        if ((*stack_a)->index == max && (*stack_a)->last->index == min)
                if (list_swap(stack_a, commands, 0) && list_rotate(stack_a, commands, 2))
                        ;
        if ((*stack_a)->index == min && (*stack_a)->next->index == max)
                if (list_swap(stack_a, commands, 0) && list_rotate(stack_a, commands, 1))
			;
}

int	*make_int_stack(t_llist *stack)
{
	t_llist *head;
	int *out;
	int i;

	i = 1;
	head = stack;
	stack = stack->next;
	while (stack != head)
	{	
		++i;
		stack = stack->next;
	}
	if(!(out = (int *)malloc(sizeof(int) * (i + 1))))
		error();
	out[0] = i + 1;
	i = 1;
	out[i] = stack->val;
	stack = stack->next;
        while (stack != head)
        {       
		out[++i] = stack->val;
		stack = stack->next;
	}
	return (out);
}

void	index_llist(t_llist *stack)
{
	if (!stack)
		return;
	t_llist *head;
	int	*i_stack;
	int	*indexes;
	int	i;

	i_stack = make_int_stack(stack);
	indexes = index_stack(i_stack);
	free(i_stack);
	head = stack;
	i = 1;
	while(stack)
	{
		stack->index = indexes[i++];
		stack = stack->next;
		if (stack == head)
			break;
	}
	free(indexes);
}

void	push_swap_quicksort(t_llist *stack_a, int **commands)
{
	int 		median;
	int		dir;
	t_llist         *stack_b = NULL;
	t_llist		*head;

	while (stack_a_too_big(stack_a))
	{
		if (stack_b)
			index_llist(stack_a);
		median = find_median(stack_a);
		while (is_lower_than_median(stack_a, median) && stack_a_too_big(stack_a))
		{
			if (bottom_three(stack_a))
				push_b(&stack_a, &stack_b, commands);
			else if ((dir = quickest_path(stack_a)))
                	{
	 	        	stack_a = (dir == 1) ? stack_a->next : stack_a->last;
                        	*commands = push_end(*commands, dir);
			}		
			if (three_in(stack_b))
				sort_b(&stack_b, commands);
		}
	}
	if (three_in(stack_a))
		sort_a(&stack_a, commands);
	index_llist(stack_b);
	int max = edge_indexes(stack_b, 0);
	while (stack_b)
	{
		if (stack_b->index == max && (max-- >= 0))
			push_a(&stack_a, &stack_b, commands);
		else if ((dir = quickest_path_2(stack_b, max)))
		{
			stack_b = (dir == 4) ? stack_b->next : stack_b->last;
			*commands = push_end(*commands, dir);
		}
	}
}
