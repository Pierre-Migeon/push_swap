

#include <stdio.h>
#include <stdlib.h>


void	change_pointer(int **ptr)
{
	int *ptr2;

	ptr2 = (int *)malloc(sizeof(int) * 1);

	ptr2[0] = 5;
	*ptr = ptr2;
}





int	main()
{
	int *ptr;
	ptr = (int *)malloc(sizeof(int) * 1);

	ptr[0] = 1;

	printf ("The ptr points to %i\n", ptr[0]);
	change_pointer(&ptr);

	printf ("Now the ptr points to %i\n", ptr[0]);

	return (0);
}
