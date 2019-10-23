

#include <stdio.h>



int	smallest(int *things)
{
	int 	i;
	int	j;
	int 	small;

	small = things[0];
	i = j = 0;
	while (i < 5)
	{
		if (things[i] < small)
			j = i;
		++i;
	}
	return (j);
}



int	main()
{
	int 	things[5] = {4, 7, 8, 1 , 5};
	int	i;

	i = smallest(things);	
	printf ("Smallest index is %i which corresponds to the value %i\n", i, things[i]);

	return (0);
}
