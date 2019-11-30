#include "push_swap.h"

char	*long_command_convert(int i)
{
	if (i == 0)
		return ("Swap A:\n");
	if (i == 1)
		return ("Rotate A:\n");
	if (i == 2)
		return ("Reverse Rotate A:\n");
	if (i == 3)
		return ("Swap B:\n");
	if (i == 4)
		return ("Rotate B:\n");
	if (i == 5)
		return ("Reverse Rotate B:\n");
	if (i == 6)
		return ("Push A:\n");
	if (i == 7)
		return ("Push B:\n");
	if (i == 8)
		return ("Swap both:\n");
	if (i == 9)
		return ("Rotate Both:\n");
	if (i == 10)
		return ("Reverse Rotate Both:\n");
	return ("Error\n");
}

int	numlen(int num)
{
	int i;

	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		++i;
	while (num)
	{
		++i;
		num /= 10;
	}
	return (i);
}

int	get_offset(int *stack)
{
	int 	i;
	int	len[2];
	
	i = 1;
	len[0] = 0;
	while (i < stack[0])
	{
		len[1] = numlen(stack[i]);
		if (len[1] > len[0])
			len[0] = len[1];
		++i;
	}
	return (len[0]);
}

void	write_header(int offset)
{
	write(1, "--", 2);
	for(int i = 0; i < offset; i++)	
		write(1, "-", 1);
	write(1, "-+-", 3);
	for(int j = 0; j < offset; j++)
		write(1, "-", 1);
	write(1, "--\n", 3);
}

void	write_line(int a, int b, int offset, int print_code)
{
	int 	spaces;

	spaces = (print_code == 2) ? 0 : numlen(a);
	write(1, "| ", 2);
	write(1, ft_itoa(a), spaces);
	for(int i = 0; i < offset - spaces; i++)
		write(1, " ", 1);
	write(1,  " | ", 3);
	spaces = (print_code == 1) ? 0 : numlen(b);
	write(1, ft_itoa(b), spaces);
	for(int i = 0; i < offset - spaces; i++)
		write(1, " ", 1);	
	write(1, " |\n", 3);
}

void	print_boxes(t_llist *stack_a, t_llist *stack_b, int offset)
{
	int head_a[2] = {0};
	int head_b[2] = {0};
	int print_code;

	write_header(offset);
	if (!stack_b && (head_b[1] = 1))
		stack_b = stack_a;
	head_a[0] = stack_a->val;
	head_b[0] = stack_b->val;
	print_code = 0;
	while(1)
	{
		print_code = (head_b[1] == 1) ? 1 : print_code;
		print_code = (head_a[1] == 1) ? 2 : print_code;
		write_line(stack_a->val, stack_b->val, offset, print_code);
		stack_a = stack_a->next;
		stack_b = stack_b->next;
		if (stack_a->val == head_a[0])
			head_a[1] = 1;
		if (stack_b->val == head_b[0])
			head_b[1] = 1;
		if (head_a[1] && head_b[1])
			break;
	}
	write_header(offset);
}

void	run_commands(t_llist **stack_a, t_llist **stack_b, int command)
{
	int *dummy_commands;

	dummy_commands = (int *)malloc(sizeof(int) * 1);

	if (command == 0)	
		 list_swap(stack_a, &dummy_commands, 0);
	if (command == 1 || command == 2)
		list_rotate(stack_a, &dummy_commands, command);
	if (command == 3)
		list_swap(stack_b, &dummy_commands, 3);
	if (command == 4 || command == 5)
		list_rotate(stack_b, &dummy_commands, command);
	if (command == 6)
		push_a(stack_a, stack_b, &dummy_commands);
	if (command == 7)
		push_b(stack_a, stack_b, &dummy_commands);
//	if (command == 8)
		
//	if (command == 9)

//	if (command == 10)
		
	free(dummy_commands);
}

void	run_and_print(int *commands, int *stack)
{
	t_llist		*stack_a;
	t_llist         *stack_b;
	int		i;
	int		offset;

	i = 1;
	stack_a = make_order(stack);	
	stack_b = NULL;
	offset = get_offset(stack);
	free(stack);
	write(1, "Start:\n", 7);
	print_boxes(stack_a, stack_b, offset);
	while (i < commands[0])
	{
		run_commands(&stack_a, &stack_b, commands[i]);
		ft_putstr(long_command_convert(commands[i]));
		print_boxes(stack_a, stack_b, offset);
		++i;
	}
	free_list(stack_a);
	free(commands);
}
