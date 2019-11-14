#include "checker.h"

void	swap(int *a, int *b)
{
	if (*a == *b)
		return;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void	rotate(int *stack)
{
	int i;

	i = 1;
	while (i < stack[0] - 1)
	{
		swap(&stack[i], &stack[i + 1]);
		++i;
	}
}

void	reverse_rotate(int *stack)
{
	int stack_size = stack[0];

	while(--stack_size > 1)
		swap(&stack[stack_size], &stack[stack_size - 1]);
}

int	remove_top(int *stack)
{
	int out;
	int i;

	i = 1;
	out = stack[1];
	while (i < stack[0] - 1)
	{
		stack[i] = stack[i + 1];
		i++;
	}
	stack[0] -= 1;
	return (out);
}

int	*push(int *stack_source, int *stack_destination)
{
	int *out;
	int pushed_element;
	int i;

	if (stack_source[0] == 1)
		return (stack_destination);
	pushed_element = remove_top(stack_source);
	stack_destination[0] += 1;
	if (!(out = (int *)malloc(sizeof(int) * stack_destination[0])))
		return (0);
	out[0] = stack_destination[0];
	out[1] = pushed_element;
	i = 2;
	while(i < stack_destination[0])
	{
		out[i] = stack_destination[i - 1];
		i++;
	}
	free(stack_destination);
	return (out);
}
