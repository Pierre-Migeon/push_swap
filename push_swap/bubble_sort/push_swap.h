


#ifndef CHECKER_H
# define CHECKER_H

#include "../../includes/get_next_line/get_next_line.h"
#include <sys/uio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

# define read_error(i) (i < 0) ? error() : 0;

typedef struct  s_listy
{
        char *str;
        int list_count;
        struct s_listy *next;
}       t_listy;


#endif
