#include "push_swap.h"

void	init_node(t_llist *node, int val, int index, int max)
{
        node->val = val;
        node->index = index;
        node->max_index = max;
}

t_llist *make_order(int *stack_a)
{
        t_llist         *order;
        t_llist         *head;
        int             *indexes;
        int             i;

        i = 1;
        if (!(order = (t_llist *)malloc(sizeof(t_llist))))
                exit(1);
        indexes = index_stack(stack_a);
        head = order;
        while (i < stack_a[0])
        {
                init_node(order, stack_a[i], indexes[i], stack_a[0] - 2);
                if (i < stack_a[0] - 1)
                {
                        if (!(order->next = (t_llist *)malloc(sizeof(t_llist))))
                                exit(1);
                        order = order->next;
                }
                else
                        order->next = head;
                ++i;
        }
        free(indexes);
        return (classify(head));
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
		if (strncmp(str, "-", 1) == 0)
			str++;
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
