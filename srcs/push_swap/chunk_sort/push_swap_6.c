#include "push_swap.h"

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

void	sort_a(t_llist **stack_a, int **commands)
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
