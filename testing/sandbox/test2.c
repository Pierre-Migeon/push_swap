#include <stdio.h>
#include <stdlib.h>
#include "make_linked_list.h"

typedef struct	s_listy
{
	char *str;
	struct s_listy *next;
}	t_listy;





int     *read_commands_2(int *commands)
{
        int             bytes_read;
        char            temp[51];
        char            line[2];

        while ((bytes_read = read(0, temp, 1)) == 0)
                ;
        line[0] = temp[0];
        while (temp[0] != '\n')
        {
                bytes_read = read(0, temp, 50);
		temp[bytes_read] = '\0';
	//	printf ("THere was read: %s\n", temp);
	}
	write(1, "\33[AOK\n", 6);
	return (commands);
}


int	main()
{

	int *commands = NULL;

	commands = read_commands_2(commands);
	return (0);
}
