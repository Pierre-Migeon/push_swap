#include <stdio.h>
#include <stdlib.h>
#include "make_linked_list.h"

typedef struct	s_listy
{
	char *str;
	int list_count;
	struct s_listy *next;
}	t_listy;

void	print_list(t_listy *head)
{
	while (head)
	{
		printf ("the element is: %s", head->str);
		head = head->next;
	}
}


/*

int     *read_commands()
{
        int     *commands = NULL;
        int     r;
	int	i;
        char    *line;
        t_listy  *head;

	i = 0;
	head = new_lst(line);		
	free(line);
	while ((r = get_next_line(0, &line)) > 0)
	{
		i += push_list(head, line);
		free(line);
	}
	//print_list(head);
	//commands = lst_to_commands();
        return (commands);
}
*/

char	*add_character(char *dst, char *src)
{
	char 	*out;
	int 	len;
	int	i;

	i = -1;
	len = ft_strlen(dst) + 1;
	if (!(out = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	while(*(dst + ++i))
		*(out + i) = *(dst + i);
	*(out + i++) = src[0];
	*(out + i) = '\0';
	free(dst);
	return (out);
}

int	surgery(char *temp, char *line)
{
	char str_to_store[4];
	int i;
	int j;
	int offset;

	i = 0;
	j = 0;
	offset = 0;
	if (line[0])
	{
		str_to_store[0] = line[0];
		line[0] = '\0';
		offset = 1;
	}
	while (temp[i] != '\n')
	{
		str_to_store[i + offset] = temp[i];
		i++;
	}
	printf ("Line to store is %s\n", str_to_store);
	j = ++i;
	while (temp[i])
	{
		temp[i - j] = temp[i];
		i++;
	}
	temp[i - j] = '\0';
	return (1);
}

int     command_to_int(char *operation)
{       
        if (!(ft_strcmp("sa", operation)))
                return (0);
        if (!(ft_strcmp("ra", operation)))
                return (1);
        if (!(ft_strcmp("rra", operation)))
    return (2);
        if (!(ft_strcmp("sb", operation)))
                return (3);
        if (!(ft_strcmp("rb", operation)))
                return (4);
        if (!(ft_strcmp("rrb", operation)))
                return (5);
        if (!(ft_strcmp("pa", operation)))
                return (6);
        if (!(ft_strcmp("pb", operation)))
    return (7);
        if (!(ft_strcmp("ss", operation)))
                return (8);
        if (!(ft_strcmp("rr", operation)))
    return (9);
        if (!(ft_strcmp("rrr", operation)))
    return (10);
        return (0);
}

void	chomp(char *str)
{
	int len;
	
	len = ft_strlen(str);
	str[--len] = '\0';
}


t_listy *new_lst(char *str)
{       
	t_listy	*new;

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

void	add_char(char temp[6], char *c)
{
	int i;

	i = 0;
	while (temp[i])
		i++;
	temp[i + 1] = '\0';
	while(i > 0)
	{
		temp[i] = temp[i - 1];
		i--;	
	}
	temp[0] = *c;
	*c = '\0';
}

void	error(void)
{
	write(1, "Error\n", 6);
	exit (0);
}

int	*generate_commands(t_listy *head)
{
	int	*out;
	int 	i;

	i = 1;
	if (!(out =(int *)malloc(sizeof(int) * head->list_count + 1)))
		return (0);
	out[0] = head->list_count + 1;
	while(head)
	{
		out[i++] = command_to_int(head->str);
		head = head->next;
	}
	return (out);
}

int	*read_commands_2(int *commands)
{
	int 		bytes_read;
	char 		temp[6];
	char		line[2];
	t_listy		*head = NULL;

	while ((bytes_read = read(0, temp, 1)) == 0)
		;
	line[0] = temp[0];
	while (temp[0] != '\n')
	{
		bytes_read = read(0, temp, 5); 
		temp[bytes_read] = '\0';
		if (line[0] != '\0')
			add_char(temp, &line[0]);
		if (!(temp[0] == '\n') && (ft_strlen(temp) > 4 || ft_strlen(temp) < 3))
			error();
		if (temp[0] != '\n')
			head = push_head(head, temp);
	}
	write(1, "\33[AOK\n", 6);
	commands = generate_commands(head);
	return (commands);
}


void	print_commands(int *commands)
{
	int i = 1;

	while( i < commands[0])
	{
		printf ("%i\n", commands[i]);
		i++;
	}
}

int	main()
{
	int *commands = NULL;

	//commands = read_commands();

	commands = read_commands_2(commands);
	print_commands(commands);

	return (0);
}
