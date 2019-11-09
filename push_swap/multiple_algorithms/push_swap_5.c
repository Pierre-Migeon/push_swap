#include "push_swap.h"

void	print_range_table(int	indexes[12])
{
	printf ("%20s\t%10s\t%10s\n", "bin #", "start", "end");
	printf ("%16s-------------------------------------\n", " ");
	for (int i = 1; i < 11; i++)
		printf ("%20i\t%10i%10i\n", i, indexes[i], indexes[i + 1]);
}

int	*find_range(t_llist *stack_a)
{
	int		*range;
	int		index_ranges[12];
	int		i[3];

	if (!(range = (int *)malloc(sizeof(int) * 2)))
		error();
	index_ranges[11] = edge_indexes(stack_a, 0) + 1;
	index_ranges[0] = edge_indexes(stack_a, index_ranges[11]);
	index_ranges[1] = 0;
	i[0] = (index_ranges[11] / 10) ? index_ranges[11] / 10 : 1;
	i[1] = 11;
	i[2] = index_ranges[11] % 10;
	while (i[1] > 1)
	{
		i[0] += (i[2] > 0 && i[1] == i[2]) ? 1 : 0;
		index_ranges[i[1] - 1] = (i[1] - 1 == 1) ? 0 : index_ranges[i[1]] - i[0];
		if (index_ranges[0] >= index_ranges[i[1] - 1] && index_ranges[0] < index_ranges[i[1]])
		{
			range[0] = index_ranges[i[1] - 1];
			range[1] = index_ranges[i[1]];
		}
		i[1]--;
	}
	return (range);
}

int	quickest_path_chunks(t_llist *stack_a, int *range)
{
        t_llist *ra;
        t_llist *rra;

        ra = stack_a;
        rra = stack_a;
        while (1)
        {
                if (ra->index >= range[0] && ra->index < range[1])
                        return (1);
                else if (rra->index >= range[0] && rra->index < range[1])
                        return (2);
                ra = ra->next;
                rra = rra->last;
        }
        return (0);
}

int	is_within_range(t_llist *stack_a, int *range)
{
	t_llist *head;

	head = stack_a;
	while (stack_a)
	{
		if (stack_a->index >= range[0] && stack_a->index < range[1])
			return (1);
		stack_a = stack_a->next;
		if (stack_a == head)
			break;
	}
	free(range);
	return (0);
}

int	correct_end(t_llist **stack_a, t_llist **stack_b, int **commands, int max)
{
	int	hold;
	int	hold2;
	int	dir;

	hold = (*stack_a)->val;
	hold2 = (*stack_a)->next->next->val;
	while (1)
	{
		if ((*stack_b)->index == max && (*stack_b)->val < hold2)
		{
			while ((*stack_a)->last->val > (*stack_b)->val && (*stack_a)->val != hold)
				list_rotate(stack_a, commands, 2);
			if ((*stack_a)->val == hold)
				return (max);
			else
				hold2 = (*stack_a)->last->val;
		}
		else if ((*stack_b)->index == max && (max-- >= 0))
			push_a(stack_a, stack_b, commands);
		else if ((dir = quickest_path_2(*stack_b, max)))
			list_rotate(stack_b, commands, dir);
	}
	return (max);
}

void	push_swap_chunks_stack_b(t_llist **stack_a, t_llist **stack_b, int **commands)
{
	int max;
	int dir;

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
}

void	push_swap_chunks(t_llist *stack_a, int **commands)
{
	int 		*range;
	t_llist         *stack_b = NULL;
	int             dir;
	int		max;

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
		if (three_in(stack_a))
			sort_a(&stack_a, commands);
	}
	push_swap_chunks_stack_b(&stack_a, &stack_b, commands);
}
