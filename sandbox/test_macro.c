

#include <unistd.h>
#include <stdlib.h>

# define read_error(i) (i < 0) ? error() : 0;



void	error()
{
	write(1, "error\n", 6);
	exit(0);
}


int	main()
{
	int bytes_read = -1;
	read_error(bytes_read);

	return (0);
}
