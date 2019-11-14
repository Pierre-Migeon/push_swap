#include "push_swap.h"

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

int	shortest_path_4(t_llist *head, t_llist *target, int flag)
{
	t_llist *rb;
	t_llist *rrb;
	int distance;

	rb = head;
	rrb = head;
	distance = 0;
	while (1)
	{
		if (rb == target)
			return ((flag == 0) ? distance : 1);
		else if (rrb == target)
			return ((flag == 0) ? distance: 2);
		distance++;
		rb = rb->next;
		rrb = rrb->last;
	}
	return (0);
}


int     shortest_path_3(t_llist *stack_a)
{
        t_llist *ra;
        t_llist *rra;

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

void    push_a(t_llist **stack_a, t_llist **stack_b, int **commands)
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

int     check_push_a(t_llist *stack_a, t_llist *stack_b)
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

void    push_b(t_llist **stack_a, t_llist **stack_b, int **commands)
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

int	shortest_path_2(t_llist *stack_a, t_llist *stack_b)
{
	t_llist *forw;
	t_llist *rev;

	forw = stack_a;
	rev = stack_a;
	while (1)
	{
		if (check_push_a(forw, stack_b))
			return (1);
		if (check_push_a(rev, stack_b))
			return (2);
		forw = forw->next;
		rev = rev->last;
	}
	return (1);
}

int     shortest_path(t_llist *stack)
{       
        t_llist         *ra;
        t_llist         *rra;
        
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

int     not_sorted(t_llist *stack)
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

int	should_shift_b(t_llist *a, t_llist *b, t_dir *dir)
{
	t_llist	*head_a;
	t_llist *head_b;

	head_a = a;
	head_b = b;
	dir->target_index = head_b->index;

	while(b->next != head_b)
	{
		dir->current_distance = 0;
		while (!(check_push_a(a, b)) && (dir->dir = shortest_path_2(a, b)))
		{
			a = (dir->dir == 1) ? a->next : a->last;
			dir->current_distance++;
		}
		dir->current_distance += shortest_path_4(head_b, b, 0);
		if (dir->current_distance < dir->best_distance) 
		{
			dir->best_distance = dir->current_distance;
			dir->target_index = b->index;
			dir->dir = shortest_path_4(head_b, b, 1);
		}
		b = b->next;
		a = head_a;
	}
	return ((dir->target_index != head_b->index) ? 1 : 0);
}

void    push_swap_indexed(t_llist *stack_a, int **commands)
{       
        t_llist 	*stack_b = NULL;
        t_dir		dir;
        
        while (not_sorted(stack_a))
        {
                if (stack_a->keep == 0)
                        push_b(&stack_a, &stack_b, commands);
                else if ((dir.dir = shortest_path(stack_a)))
                {       
                        stack_a = (dir.dir == 1) ? stack_a->next : stack_a->last;
                        *commands = push_end(*commands, dir.dir);
                }
        }
        while (stack_b)
        {       
		if (check_push_a(stack_a, stack_b))
                        push_a(&stack_a, &stack_b, commands);
		//else if (should_shift_b(stack_a, stack_b, &dir))
		//{
		//	while (dir.target_index != stack_b->index)
		//		stack_b = (dir.dir == 1) ? stack_b->next : stack_b->last;
		//}
             	else if ((dir.dir = shortest_path_2(stack_a, stack_b)))
                {       
                        stack_a = (dir.dir == 1) ? stack_a->next : stack_a->last;
                        *commands = push_end(*commands, dir.dir);
                }
        }       
        while (stack_a->index != 0)
        {       
                dir.dir = shortest_path_3(stack_a);
                stack_a = (dir.dir == 1) ? stack_a->next : stack_a->last;
                *commands = push_end(*commands, dir.dir);
        }
}
