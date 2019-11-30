#include "push_swap.h"

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
	int		start;
	int		dir;

	dir = 0;
	start = (*stack_a)->val;
	while ((*stack_a)->val != start || dir == 0)
	{
		if ((*stack_b)->index == max && (*stack_b)->val < (*stack_a)->last->val)
        		list_rotate(stack_a, commands, 2);
		else if ((*stack_b)->index == max && max-- >= 0)
			push_a(stack_a, stack_b, commands);
		else if ((dir = quickest_path_2(*stack_b, max)))
			list_rotate(stack_b, commands, dir);
		dir++;
	}
	return (max);
}



//((*stack_a)->val != start || dir == 0) && max-- >= 0)
//else if (((*stack_a)->val != start || dir == 0) && (dir = quickest_path_2(*stack_b, max)))

