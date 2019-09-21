

#include <stdio.h>
#include <stdlib.h>


int     remove_top(int *stack, int *stack_size)
{       
        int out;
        int i;
        
        i = 0;
        out = stack[0];
        while (i < *stack_size - 1)
        {       
                stack[i] = stack[i + 1];
                i++;
        }
        *stack_size -= 1;
        return (out);
}

int     *push(int *stack_source, int *stack_destination, int *stack_s_size, int *stack_d_size)
{       
        int *out;
        int pushed_element;
        int i;
        
        pushed_element = remove_top(stack_source, stack_s_size);
        if (!(out = (int *)malloc(sizeof(int) * *stack_d_size + 1)))
                return (0);
        i = 1;
        while(i < *stack_d_size + 1)
        {       
                out[i] = stack_destination[i - 1];
                i++;
        }
	*stack_d_size += 1;
        out[0] = pushed_element;
        free(stack_destination);
        return (out);
}

void	print_stack(int *stack, int stack_size)
{
	int i;

	i = 0;
	while (i < stack_size)
	{
		printf ("%i, ", stack[i]);
		++i;
	}
	printf ("\n");
}

int	main()
{
	int *stack_a;
	int *stack_b;
	int stack_a_size;
	int stack_b_size;

	stack_a = (int *)malloc(sizeof(int) * 3);	
	stack_a_size = 3;
	stack_a[0] = 5;
	stack_a[1] = 10;
	stack_a[2] = 9;	

	stack_b = (int *)malloc(sizeof(int) * 1);
	stack_b_size = 1;
	stack_b[0] = 7;

	printf ("The two stacks before the push:\n");
	print_stack(stack_a, stack_a_size);
	print_stack(stack_b, stack_b_size);

	stack_b = push(stack_a, stack_b, &stack_a_size, &stack_b_size);

        printf ("The two stacks after the push:\n");
        print_stack(stack_a, stack_a_size);
        print_stack(stack_b, stack_b_size);




	return (0);
}

