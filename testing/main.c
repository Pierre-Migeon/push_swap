#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../includes/get_next_line/libft/libft.h"

# define ARRAY_SIZE 5

int	factorial(int i)
{
	if (i == 0)
		return (1);
	return (i * factorial(i - 1));
}

void	print_array(int *array)
{
	for (int i = 0; i < 5; i++)
		printf("%i ", array[i]);
	printf ("\n");
}

void	swap(int *a, int *b)
{
	if (*a == *b)
		return;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void	r_permute(int *in_array, int **out_array, int lower, int upper)
{
	static int i = 0;

	if (lower == upper)
	{
		out_array[i] = memcpy(out_array[i], in_array, sizeof(int) * 5);
		i++;
	}
	for (int j = lower; j <= upper; j++)
	{
		swap(&in_array[lower], &in_array[j]);
		r_permute(in_array, out_array, lower + 1, upper);
		swap(&in_array[lower], &in_array[j]);
	}
}

int	**all_possible(int *array, int i)
{
	int **out;

	out = (int **)malloc(sizeof(int *) * i);
	for (int j = 0; j < i; j++)
		out[j] = (int *)malloc(sizeof(int) * ARRAY_SIZE); 
	r_permute(array, out, 0, ARRAY_SIZE - 1);	
	return (out);
}

int	space_of_ints(void)
{
	int spaces;
	int temp;

	spaces = 0;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		temp = i;
		while (temp)
		{	
			spaces++; 
			temp /= 10;
		}
		spaces++;
	}
	return (spaces);
}

char	*array_to_string(int *array)
{
	char *out;
	int j;
	int k;

	j = ARRAY_SIZE - 1;
	k = space_of_ints();
	out = (char *)malloc(sizeof(char) * k);
	out[k] = '\0';
	while (k >= 0)
	{
		if (array[j] == 0)
			out[--k] = '0';
		while (array[j])
		{
			out[--k] = (array[j] % 10) + '0';
			array[j] /= 10;
		}
		out[--k] = ' ';
		--j;
	}
	return (out);
}

char *make_string(int *array)
{
	char *str_a;
	char *str_b;
	char *str_f;
	char *str_g;
	char *str_h;
	char *str_i;
	int i;
	
	i = -1;
	str_a = "../push_swap/indexed_list_version/a.out ";
	str_b = array_to_string(array);
	str_f = ft_strjoin(str_a, str_b);
	str_g = " | ../checker/checker ";
	str_h = ft_strjoin(str_g, str_b);
	str_i = ft_strjoin(str_f, str_h);
//	for checking the number of commands it takes to solve:
//	str_g = ft_strjoin(str_f, " | wc -l");


	free(str_b);
	return (str_i);
}

int	main()
{
	int i;
	int array[ARRAY_SIZE] = {0, 1, 2, 3, 4};
	int **o_array = NULL;
	char *str;

	i = factorial(ARRAY_SIZE);
	o_array = all_possible(array, i);

	for (int j = 1; j < i; j++)
        {
		str = make_string(o_array[j]);
		printf ("%s\n", str);		
		system(str);
	}
	return (0);
}
