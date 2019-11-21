#include "push_swap.h"

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


int	edge_indexes(t_llist *stack, int ref_index)
{
	if (!stack)
		return (0);
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


t_llist *label(t_llist *head, t_hash best)
{
        t_llist         *ref;
        int             current_index;
        int             i;

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
