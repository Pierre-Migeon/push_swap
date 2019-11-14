

#include <stdio.h>




void	pop_stack(int *stack)
{
	int	i;

	i = 0;
	while (++i < stack[0] - 1)
		stack[i] = stack[i+ 1];
	if (stack[0] > 1)
		stack[0] -= 1;
}

int	main()
{
	int ints[6] = { 6, 1, 2, 3, 4, 5 };
	

	int	i = 0;
	while (i < ints[0])
	{
		printf("Before the pop, stack[%i] is %i\n", i, ints[i]);
		++i;
	}

	pop_stack(ints);

	i = 0;
        while (i < ints[0])
        {
                printf("after the pop, stack[%i] is %i\n", i, ints[i]);
    		++i;
    	}
	
	        pop_stack(ints);

        i = 0;
        while (i < ints[0])
        {
                printf("after the pop, stack[%i] is %i\n", i, ints[i]);
                ++i;
        }

	        pop_stack(ints);

        i = 0;
        while (i < ints[0])
        {
                printf("after the pop, stack[%i] is %i\n", i, ints[i]);
                ++i;
        }


        pop_stack(ints);

        i = 0;
        while (i < ints[0])
        {
                printf("after the pop, stack[%i] is %i\n", i, ints[i]);
                ++i;
        }

        pop_stack(ints);

        i = 0;
        while (i < ints[0])
        {
                printf("after the pop, stack[%i] is %i\n", i, ints[i]);
                ++i;
        }


	        pop_stack(ints);

        i = 0;
        while (i < ints[0])
        {
                printf("after the pop, stack[%i] is %i\n", i, ints[i]);
                ++i;
        }

        pop_stack(ints);

        i = 0;
        while (i < ints[0])
        {
                printf("after the pop, stack[%i] is %i\n", i, ints[i]);
                ++i;
        }
        pop_stack(ints);

        i = 0;
        while (i < ints[0])
        {
                printf("after the pop, stack[%i] is %i\n", i, ints[i]);
                ++i;
        }

        pop_stack(ints);

        i = 0;
        while (i < ints[0])
        {
                printf("after the pop, stack[%i] is %i\n", i, ints[i]);
                ++i;
        }

	return (0);
}
