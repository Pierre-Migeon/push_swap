#include "push_swap.h"


void	print_range_table(int	indexes[12])
{
	printf ("%20s\t%10s\t%10s\n", "bin #", "start", "end");
	printf ("-------------------------------------\n");
	for (int i = 1; i < 11; i++)
		printf ("%20i\t%10i%10i\n", i, indexes[i], indexes[i + 1]);
}

int	*find_range(t_llist *stack_a)
{
	int		*range;
	int		index_ranges[12];
	int		i[2];

	if (!(range = (int *)malloc(sizeof(int) * 2)))
		error();
	index_ranges[11] = edge_indexes(stack_a, 0) + 1;
	index_ranges[0] = edge_indexes(stack_a, index_ranges[1]);
	index_ranges[1] = 0;
	i[0] = (index_ranges[11] / 10) ? index_ranges[11] / 10 : 1;
	i[1] = 11;
	while (i[1] > 1)
	{
		index_ranges[i[1] - 1] = index_ranges[i[1]] - i[0];
		if (index_ranges[0] >= index_ranges[i[1] - 1] && index_ranges[0] < index_ranges[i[1]])
		{
			range[0] = index_ranges[i[1] - 1];
			range[1] = index_ranges[i[1]];
		}
		i[1]--;
	}
	print_range_table(index_ranges);
	printf ("index in question is %i and the chosen range is [%i-%i)\n",index_ranges[0], range[0], range[1]); 
	return (range);
}

void	push_swap_chunks(t_llist *stack_a, int **commands)
{
	int 		*range;
	int		dir;
	t_llist         *stack_b = NULL;

	//while (stack_a_too_big(stack_a))
	//{
		range = find_range(stack_a);
		printf ("range[0] is %i and range[1] is %i\n", range[0], range[1]);
	//}
}
/*		while (is_within_range(stack_a, range) && stack_a_too_big(stack_a))
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
*/
