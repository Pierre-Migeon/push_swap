#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "../../includes/libft/libft.h"

long long factorial(long long i)
{
	return ((i == 0) ? 1 : i * factorial(i - 1));
}

void	print_array(int *a, int len)
{
	for (int i = 0; i < len; i++)
		printf ("%i ", a[i]);
	printf ("\n");
}

int	*randomizer(int length)
{
	int 			*out;
	struct timespec 	start;
	int 			counts[5000] = {0};

	out = (int *)malloc(sizeof(int) * length);
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	srandom(start.tv_nsec);
	for (int i = 0; i < length; i++)
	{
		out[i] = random() % 500;
		counts[out[i]]++;
		if (counts[out[i]] > 1)
			counts[out[i--]] -= 1;	
	}
	return (out);
}

int	**random_list(int length, int number)
{
	int **out;

	out = (int **)malloc(sizeof(int *) * number);
        for (int j = 0; j < number; j++)
		out[j] = randomizer(length);
	return (out);
}

int	space_of_ints(int *array, int number)
{
	int spaces;
	int temp;

	spaces = 0;
	for (int i = 0; i < number; i++)
	{
		temp = array[i];
		if (temp == 0)
			spaces++;
		while (temp)
		{
			spaces++;
			temp /= 10;
		}
		spaces++;
	}
	return ((spaces > 1) ? --spaces : spaces);
}

char	*array_to_string(int *array, int members)
{
	char *out;
	int temp;
	int j;
	int k;

	j = members - 1;
	k = space_of_ints(array, members);
	out = (char *)malloc(sizeof(char) * (k + 1));
	out[k] = '\0';
	while (k > 0 && j >= 0)
	{
		temp = array[j];
		if (j < members - 1)
			out[--k] = ' ';
		if (temp == 0)
			out[--k] = '0';
		while (temp)
		{
			out[--k] = (temp % 10) + '0';
			temp /= 10;
		}
		--j;
	}
	return (out);
}

char *make_string(int *array, int members, int mode)
{
	char Buffer[2000];
	char str_a[] = "../../push_swap ";
	char *str_b;
	str_b = array_to_string(array, members);
	char str_c[9] = " | wc -l";
	char str_d[] = " | ../../checker ";
	char *str_e;

	int length = 0;
        length += sprintf(Buffer+length, "%s", str_a);
        length += sprintf(Buffer+length, "%s", str_b);

	if (mode == 1)
        	length += sprintf(Buffer+length, "%s", str_c);
	else
	{
                length += sprintf(Buffer+length, "%s", str_d);
		length += sprintf(Buffer+length, "%s", str_b);
	}
	str_e = ft_strdup(Buffer);
	free(str_b);
	return (str_e);
}

int	main(int argc, char **argv)
{
	int x, y;
	long long i;
	int **o_array = NULL;
	char *str;

	if (argc < 3)
	{
		printf ("Usage:\n ./generate_push_swap_tests [list size] [number of tests] [ -1 for number of moves summary | -2 to test using checker]\n");
		exit(0);
	}
	x = ft_atoi(argv[1]);
	y = ft_atoi(argv[2]);
	o_array = random_list(x, y);

	for (int j = 0; j < y; j++)
        {
		str = make_string(o_array[j], x, ft_atoi(argv[3]));
		printf ("%s\n", str);		
		system(str);
		free(o_array[j]);
	}
	free(o_array);
	return (0);
}
