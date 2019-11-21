#include "checker.h"

int	*generate_commands(t_listy *head)
{
	t_listy	*last;
	int	*out;
	int 	i;

	i = 1;
	if (!(out = (int *)malloc(sizeof(int) * head->list_count + 1)))
		return (0);
	out[0] = head->list_count + 1;
	while(head)
	{
		out[i++] = command_to_int(head->str);
		last = head;
		head = head->next;
		free(last);
	}
	return (out);
}

int	*generate_zero()
{
	int *zero;

	if (!(zero = (int *)malloc(sizeof(int))))
		return(0);
	zero[0] = 1;
	return (zero);
}

void	init_zero(int	i[3], char line[4])
{
	ft_bzero(line, 4);
	i[0] = 0;
	i[1] = 0;
}

int	*read_commands(void)
{
	int 		i[2];
	char 		temp[2];
	char		line[4];
	t_listy		*head = NULL;

	init_zero(i, line);
        while (((i[1] = read(0, temp, 1)) > 0) && !(temp[1] = '\0'))
        {
		if (temp[0] != '\n' && i[0] < 3)
			line[i[0]] = temp[0];
                if (temp[0] == '\n')
                {
                        if (i[0] == 0)
                                break;
			if (i[0] > 3)
				line[0] = 'z';
                        i[0] = -1;
                	head = push_head(head, line);
			ft_bzero(line, 4);
                }
                i[0]++;
        }
	if (isatty(0))
		write(1, "\33[A", 3);
	return ((head == NULL) ? generate_zero() : generate_commands(head));
}

int	check_sorted(int *stack_a, int *stack_b, int *commands, int f)
{
	int i;

	if (stack_b[0] > 1)
		return (0);
	i = 2;
	while (i < stack_a[0])
	{
			if (stack_a[i] < stack_a[i - 1])
			{
				if (f)
				{
					free(stack_a);
					free(stack_b);
					free(commands);
				}
				return (0);
			}
		i++;
	}
	free(stack_a);
	free(stack_b);
	free(commands);
	return (1);
}

int	*get_stack(int argc, char **argv, int start_args, t_params *params)
{
	int stack_size;
	int *stack;
	int i;
	int j;

	i = 1;
	params->print_list = (!(ft_strncmp(argv[i], "-p", 2))) ? 1 : 0;
	while(i < argc && is_flag(argv[i]))
		++i;
	stack_size = (start_args > 0) ? start_args : argc - i + 1;
	if (!(stack = (int *)malloc(sizeof(int) * stack_size)))
		return (0);
	stack[0] = stack_size;
	j = 1;
	while (j < stack[0])
		stack[j++] = ft_atoi(argv[i++]);
	return (stack);
}
