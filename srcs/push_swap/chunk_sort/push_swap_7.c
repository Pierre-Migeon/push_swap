#include "push_swap.h"

void	push_swap_chunks_stack_b(t_llist **stack_a, t_llist **stack_b, int **commands, int print)
{
	int max;
	int dir;

	if (!stack_b)
	{
		if (print)
			print_stack(*stack_a);
		return;
	}
        index_llist(*stack_b);
        max = edge_indexes(*stack_b, 0);
        while (*stack_b)
        {
                if ((*stack_b)->index == max && (*stack_b)->val < (*stack_a)->val && (max-- >= 0))
                        push_a(stack_a, stack_b, commands);
                else if ((*stack_b)->index == max && (*stack_b)->val > (*stack_a)->val)
                        max = correct_end(stack_a, stack_b, commands, max);
                else if ((dir = quickest_path_2(*stack_b, max)))
                        list_rotate(stack_b, commands, dir);
    	}
	if (print)
		print_stack(*stack_a);
}

void	push_swap_chunks(t_llist *stack_a, int **commands, int print)
{
	int 		*range;
	t_llist         *stack_b = NULL;
	int             dir;

	while (stack_a_too_big(stack_a))
	{
		range = find_range(stack_a);
		while (is_within_range(stack_a, range) && stack_a_too_big(stack_a))
                {
			if (stack_a->index >= range[0] && stack_a->index < range[1])
				push_b(&stack_a, &stack_b, commands);
			else if ((dir = quickest_path_chunks(stack_a, range)))
				list_rotate(&stack_a, commands, dir);
		}
		if (three_in(stack_b))
			sort_b(&stack_b, commands);
	}
	if (three_in(stack_a) || two_in(stack_a))
		sort_a(&stack_a, commands);
	push_swap_chunks_stack_b(&stack_a, &stack_b, commands, print);
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
	if (stack_b->next->next->next == stack_b)
		return (1);
	return (0);
}

int	two_in(t_llist *stack)
{
	if (stack->next->next == stack)
		return (1);
	return (0);
}
