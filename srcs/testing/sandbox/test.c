

/* This just tests to make sure you are using correct syntax for mallocing a string of ints and then iterating over it in array fashion. It does seem to work just fine. 
*/

#include <stdio.h>
#include <stdlib.h>


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

int	main()
{
	int *array;
	int i;
	
	i = 0;
	array = make_array(5, 1);

	while (i < 5)
	{
		printf ("%i, ", array[i]);
		i++;
	}
}
