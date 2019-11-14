




#include <stdio.h>

void	function_1(int a)
{
	printf ("You have called function 1 with value %i\n", a);
}

void	function_2(void)
{
	printf ("You have called function 2\n");
}

void	function_3(void)
{
	printf ("You have called function 3!\n");
}

void	what_function(int i)
{
	void	(*f_array[3])();

	f_array[0] = function_1;
	f_array[1] = function_2;	
	f_array[2] = function_3; 


	if (i == 0 )
		(f_array[i])(6);
	else
		(f_array[i])();
}



int	main()
{
	what_function(2);
	return (0);
}
