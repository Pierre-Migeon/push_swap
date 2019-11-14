


#include <stdio.h>
#include <sys/uio.h>
#include <unistd.h>



void	print_ints(int c)
{
	printf ("%i ", c);
}


void	second_function(void)
{
        int bytes_read;
        char temp[51];

        while ((bytes_read = read(0, temp, 50)) > 0)
        {
                temp[bytes_read] = '\0';
		int i = 0;
		while (temp[i])
			print_ints(temp[i++]);
                printf ("This was read: %s\n", temp);
        }
}

int	main(int argc, char **argv)
{
	printf ("Argc is %i\n", argc);
	printf ("The first argument is %s\n", argv[1]);
	second_function();

	return (0);
}
