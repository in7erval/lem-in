#include "lem-in.h"

int		ft_isknowncommand(char *str)
{
	if (!ft_strcmp(str, "##start"))
		return (START);
	else if (!ft_strcmp(str, "##end"))
		return (END);
	return (0);
}

int		ft_iscomment(char *str)
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

int		ft_isrooms(char *str)
{
	char	**parts;
	int		i;

	parts = ft_strsplit(str, ' ');
	i = 0;
	while (parts[i] != NULL)
		i++;
	if (i != 3)
		return (0);
	if (parts[0][0] == 'L' || !ft_isinteger(parts[1]) || !ft_isinteger(parts[2]))
		return (0);
	free(parts);
	return (1);
}

int		ft_islinks(char *str)
{
	char	**parts;
	int		i;

	parts = ft_strsplit(str, '-');
	i = 0;
	while (parts[i] != NULL)
		i++;
	if (i != 2)
		return (0);
	if (parts[0][0] == 'L' || parts[1][0] == 'L')
		return (0);
	free(parts);
	return (1);
}
