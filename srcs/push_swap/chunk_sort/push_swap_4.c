#include "push_swap.h"

int	reset_and_test_hash(t_hash *best)
{
        if (best->head_index == -1)
        {
                best->current_score = 0;
                best->best_score = 0;
                best->best_index = 0;
                best->head_index = 0;
                best->last_index = -1;
                best->final_index = -1;
                return (1);
        }
        else if (best->head_index == best->final_index)
                return (0);
        else
        {
                if (best->current_score > best->best_score)
                {
                        best->best_score = best->current_score;
                        best->best_index = best->head_index;
                }
                best->final_index = -1;
                best->last_index = best->head_index;
                best->current_score = 0;
                best->head_index++;
                return (1);
        }
        return (0);
}

t_llist *classify(t_llist *head)
{
        t_llist         *ref;
        t_hash          best;
        int             i;

        best.head_index = -1;
        ref = head;
        while (reset_and_test_hash(&best))
        {
                while(head->index != best.head_index)
                        head = head->next;
                i = 0;
                while (best.final_index < 0)
                {
                        if (head->index == best.last_index + 1)
                        {
                                best.last_index++;
                                best.current_score++;
                        }
                        if (head->next->index == best.head_index)
                                best.final_index = i;
                        head->next->last = head;
                        head = head->next;
                        ++i;
                }
        }
        return (label(ref, best));
}

int	next_bigger_index(int *stack, int value)
{
        int     i;
        int     j;
        int     next;

        i = 1;
        j = 1;
        next = value;
        while (i < stack[0])
        {
                if (stack[i] > value)
                {
                        if (next == value)
                        {
                                next = stack[i];
                                j = i;
                        }
                        else if (stack[i] < next)
                        {
                                next = stack[i];
                                j = i;
                        }
                }
                ++i;
        }
        return (j);
}

int	smallest_index(int *things)
{
        int     i;
        int     j;
        int     small;

        small = things[1];
        i = j = 1;
        while (i < things[0])
        {
                if (things[i] < small)
                {
                        j = i;
                        small = things[i];
                }
                ++i;
        }
        return (j);
}

int	*index_stack(int *stack)
{
        int     *out;
        int     i = 1;
        int     j = 0;

        if (!(out = (int *)malloc(sizeof(int) * stack[0])))
                exit(1);
        out[0] = stack[0];
        while (j < stack[0] - 1)
        {
                if (j == 0)
                        i = smallest_index(stack);
                else
                        i = next_bigger_index(stack, stack[i]);
                out[i] = j++;
        }
        return (out);
}
