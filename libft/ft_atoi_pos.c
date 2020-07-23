#include "libft.h"

int			ft_atoi_pos(const char *str)
{
    int     result;

    result = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		if (result * 10 + *str - '0' < result)
			return (0);
		result = result * 10 + *str - '0';
        str++;
	}
	return (result);
}
