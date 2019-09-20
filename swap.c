
#include <stdio.h>
#include <stdlib.h>


void	swap(int *stack)
{
	stack[0] ^= stack[1];
	stack[1] ^= stack[0];
	stack[0] ^= stack[1];
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


void	print_array(int *array)
{
	int i = 0;
	while (i < 3)
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

	print_array(array);	
	swap(array);
	print_array(array);


	return (0);
}
