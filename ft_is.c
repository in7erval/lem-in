#include <stdbool.h>
#include "lem-in.h"

int		ft_isknowncommand(char *str)
{
	if (!ft_strcmp(str, "##start"))
		return (START);
	else if (!ft_strcmp(str, "##end"))
		return (END);
	return (0);
}

int		ft_iscomment(const char *str)
{
	if (*str == '#')
		return (COMMON);
	return (0);
}

int		ft_isants(char *str)				// 0037 +15
{
	int		length;

	length = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
		length++;
	}
	str--;
	if (length == 0 || (length == 1 && *str == '0'))
		return (0);
	return (1);
}

static int		count_of_words(const char *str, char c)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str != c && (*(str + 1) == c || *(str + 1) == '\0'))
				i++;
		str++;
	}
	return (i);
}

int		ft_isrooms(char *str)
{
	char	**parts;

	if (count_of_words(str, ' ') != 3)
		return (0);
	parts = ft_strsplit(str, ' ');
	if (parts[0][0] == 'L' || !ft_isinteger(parts[1]) || !ft_isinteger(parts[2]))
	{
		ft_freesplit(parts);
		return (0);
	}
	ft_freesplit(parts);
	return (1);
}

int		ft_islinks(char *str)
{
	char	**parts;

	if (count_of_words(str, '-') != 2)
		return (0);
	parts = ft_strsplit(str, '-');
	if (parts[0][0] == 'L' || parts[1][0] == 'L' || !ft_strcmp(parts[0], parts[1]))
	{
		ft_freesplit(parts);
		return (0);
	}
	ft_freesplit(parts);
	return (1);
}
