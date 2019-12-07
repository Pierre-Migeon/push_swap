
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

int	main()
{
	char	*str = "Un jour je serai, le meilleur dresseur !";
	assert(ft_strsub(str, 0, (size_t)-10) == NULL);
	assert(strcmp(ft_strsub(str, 8, 8), "je serai") == 0);
	assert(strcmp(ft_strsub(str, 0, 0), "") == 0);
	return (0);
}
