
#include <stdio.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>


# define read_error(i) (i < 0) ? error() : 0;

void	error(void)
{
	write(1, "Error\n", 6);
	exit(0);
}

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*((char *)s++) = 0;
}

void	read_commands_2()
{
	int 		bytes_read;
	char 		temp[2];
	char 		line[4];
	int 		i;
//	t_listy		*head = NULL;

	i = 1;
	while((bytes_read = read(0, line, 1)) == 0 && !(line[3] = '\0'))
		;
	read_error(bytes_read);
	while (((bytes_read = read(0, temp, 1)) >= 0) && !(temp[1] = '\0')) 
	{
		if (temp[0] != '\n' && i < 3)
			line[i] = temp[0];
		if (temp[0] == '\n')
		{
			if (i == 0)	
				break;
			i = -1;
			printf ("Line is %s\n", line);
			ft_bzero(line, 4);
		}
		i++;
	}
}


/*
int     *read_commands(int *commands)
{       
        int             bytes_read;
        char            temp[6];
        char            line[4];
        
        while ((bytes_read = read(0, line, 1)) == 0)
                ;
        temp[bytes_read] = '\0';
        read_error(bytes_read);
        line[0] = temp[0];
  	while (temp[0] != '\n')
        {       
                bytes_read = read(0, temp, 1);
                read_error(bytes_read);
                temp[bytes_read] = '\0';
                if (line[0] != '\0')
                        add_char(temp, &line[0]);
                if (!(temp[0] == '\n') && (ft_strlen(temp) > 4 || ft_strlen(temp) < 3))
                {       
                        printf ("The strlen of temp is %zu and temp is %s\n", ft_strlen(temp), temp);
                        error();
                }
        }
}
*/




int	main()
{

	read_commands_2();
	return (0);
}
