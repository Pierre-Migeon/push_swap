#include "checker.h"

int	*get_commands(char **argv, int start_args, int argc)
{
	int size;
	int i;
	int *out;

	size = argc - start_args + 1;
	if (!(out = (int *)malloc(sizeof(int) * size)))
		return (NULL);
	out[0] = size;
	i = 1;
	while (start_args < argc)
		out[i++] = command_to_int(argv[start_args++]);
	return (out);
}

void	chomp(char *str)
{
	int len;
	
	len = ft_strlen(str);
	if (str[len - 2] == ' ')
		str[len - 2] = '\0';
	else
		str[--len] = '\0';
}

int	non_char(char *str)
{
	while (*str)
		if (!(ft_isalpha(*(str++))))
			return (1);
	return (0);
}

t_listy *new_lst(char *str)
{       
	t_listy	*new;

	if (non_char(str))
		chomp(str);
	if(!(new = (t_listy *)malloc(sizeof(t_listy) * 1)))
        	return (0);
	new->str = ft_strdup(str);
	new->next = NULL;
	new->list_count = 1;
 	return (new);
}

t_listy	*push_head(t_listy *head, char *str)
{
	t_listy	*first;

	if (!head)
	{
		head = new_lst(str);
		return (head);
	}
	first = head;
	head->list_count++;
	while(head->next)
		head = head->next;		
	head->next = new_lst(str);
	return (first);
}
