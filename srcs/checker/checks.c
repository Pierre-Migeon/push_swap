#include "checker.h"

void    error(void)
{       
        write(1, "Error\n", 6);
        exit (0);
}

int	check_int(char *str)
{
	while (*str)
	{
		if (*str == '-')
			str++;
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

int	check_seen(char **argv, int i)
{
	int j;

	j = i - 1;
	while(j > 0)
		if (ft_strcmp(argv[j--], argv[i]) == 0)
			return (1);
	return (0);
}

int	is_command(char *input)
{
	char valid_com[11][4] = { "sa\0\0", "sb\0\0", "ss\0\0", "pa\0\0", "pb\0\0", "ra\0\0", "rb\0\0", "rr\0\0", "rra\0", "rrb\0", "rrr\0"};
	int match;
	int i;

	if (!(check_int(input)))
		return (0);
	match = 0;
	i = 0;
	while(*valid_com[i])
		if (ft_strcmp(valid_com[i++], input) == 0)
			match = 1;
	return (match);
}

int	is_flag(char *str)
{
	if (ft_strncmp(str++, "-", 1))
		return (0);
	if (ft_isdigit(*str))
		return (0);
	return (1);
}

int	check_input(int argc, char **argv)
{
	int i;
	int start_args;

	i = 1;
	while((i < argc) && is_flag(argv[i]))
		++i;
	if (i == argc)
		return (-2);
	while (i < argc && (!(is_command(argv[i]))))
	{
		if (check_int(argv[i]))
			return (0);
		if (check_seen(argv, i))
			return (0);
		++i;
	}
	start_args = i;
	while (i < argc)
		if (!(is_command(argv[i++])))
			return (0);
	return ((start_args == i) ? -1 : start_args);
}
