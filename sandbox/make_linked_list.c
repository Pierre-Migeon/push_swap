#include <stdio.h>
#include <stdlib.h>
#include "make_linked_list.h"



typedef struct	s_listy
{
	char *str;
	struct s_listy *next;
}	t_listy;


int	push_list(t_listy *head, char *line)
{
	t_listy *new;

	while(head->next)
		head = head->next;
	if(!(new = (t_listy *)malloc(sizeof(t_listy) * 1)))
		return (0);
	new->str = ft_strdup(line);
	head->next = new;
	return (1);
}


void	print_list(t_listy *head)
{
	while (head->next)
	{
		printf ("%s ", head->str);
		head = head->next;
	}
	printf ("\n");
}

t_listy	*new_lst(char *str)
{
	t_listy *new;

	if(!(new = (t_listy *)malloc(sizeof(t_listy) * 1)))
		return (0);
	new->str = ft_strdup(str);
	new->next = NULL;
	return (new);
}

int     *read_commands()
{
        int     *commands = NULL;
        int     r;
	int	i;
        char    *line;
        t_listy  *head;

	i = 0;
	while ((r = get_next_line(0, &line)) == 0)
                ;
        while ((r = get_next_line(0, &line)) > 0)
	{
		if (line[0] == '\0')
			break;
		if (i++ == 0)
			head = new_lst(line);
		else
			i += push_list(head, line);
	}

	//print_list(head);
	//commands = lst_to_commands();
        return (commands);
}

int	main()
{
	int *commands;

	commands = read_commands();

	return (0);
}
