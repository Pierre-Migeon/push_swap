
#include <stdio.h>
#include <stdlib.h>


void	swap(int *a, int *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void	rotate(int *stack, int stack_size)
{
	int i;

	i = 0;
	while (i < stack_size - 1)
	{
		swap(&stack[i], &stack[i + 1]);
		++i;
	}
}


void	reverse_rotate(int *stack, int stack_size)
{
	while(--stack_size > 0)
		swap(&stack[stack_size], &stack[stack_size - 1]);
}

int	*push(int *stack, int element, int stack_size)
{
	int *out;
	int i;

	if (!(out = (int *)malloc(sizeof(int) * stack_size + 1)))
		return (0);
	i = 1;
	while(i < stack_size + 1)
	{
		out[i] = stack[i - 1];
		i++;
	}
	out[0] = element;
	free(stack);
	return (out);
}




int	*make_array(int size, int fill)
{
	int *out;
	int i;

	i = 0;
	out = (int *)malloc(sizeof(int) * size);
	while (i < size)
		out[i++] = fill;
	return (out);
}


void	print_array(int *array, int array_size)
{
	int i = 0;
	while (i < array_size)
	{
		printf ("%i, ", array[i]);
		i++;
	}
	printf ("\n");
}



int	main()
{
	int *array;

	array = make_array(3, 1);
	array[1] = 5;
	array[0] = 3;
	array[2] = 6;

	print_array(array, 3);
	array = push(array, 9, 3);
	print_array(array, 4);


	return (0);
}
