
#include <stdlib.h>
#include <stdio.h>


int     *initialize_stack(void)
{       
        int *out;
        
        if (!(out = (int *)malloc(sizeof(int) * 2)))
                return (0);
        out[0] = 1;
        return (out);
}



void	function_that_does_stuff(int **commands)
{
	
	printf ("that value is %i\n", *(*(commands + 1)));
}

int	main()
{
	int **commands;

	commands = (int **)malloc(sizeof(int *) * 2);
	int *c1 = initialize_stack();
	int *c2 = initialize_stack();

	c1[0] = 2;
	c1[1] = 3;
	c2[0] = 5;
	c2[1] = 6;

	commands[0] = c1;
	commands[1] = c2;
	function_that_does_stuff(commands);
	return (0);
}
