#include "libft.h"

char	*ft_stradd(char *base, const char *addition)
{
	char	*result;
	char	*buffer;
	char	*trash;

	result = malloc(ft_strlen(base) + ft_strlen(addition) + 1);
	buffer = result;
	trash = base;
	while (*base)
	{
		*buffer = *base;
		buffer++;
		base++;
	}
	free(trash);
	while (*addition)
	{
		*buffer = *addition;
		buffer++;
		addition++;
	}
	*buffer = '\0';
	return (result);
}
