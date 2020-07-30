#include "lem-in.h"

void	error_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

