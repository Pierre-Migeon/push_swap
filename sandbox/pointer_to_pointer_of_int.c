
#include <stdlib.h>
#include <stdio.h>

int	**make_new_stuff(int **commands)
{
	int 	new = 5;
	int 	i = 0;
	int	j;

	
	while (i < new)
	{
		*(commands + i) = (int *)malloc(sizeof(int) * 5);
		j = 0;
			while(j < new)
			{
				(*(commands + i))[j] = (j == 0) ? new : i + j; 
				j++;
			}
		i++;
	}
	return (commands);
}





int	main()
{
	int **commands;
	commands = (int **)malloc(sizeof(int *) * 5);

	commands = make_new_stuff(commands);

	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			printf ("%i ", commands[i][j]);
		}
		printf ("\n");
	}

	return (0);
}
