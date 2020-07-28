#include "lem-in.h"

void			ft_clean_ants(char **str)
{
	char	*new_str;
	char	*buffer;
	char	*buf;

	buf = *str;
	if (*buf == '+')
		buf++;
	while (*buf == '0')
		buf++;
	new_str = (char*)malloc(ft_strlen(buf) * sizeof(char) + 1);
	buffer = new_str;
	while (*buf)
	{
		*new_str = *buf;
		new_str++;
		buf++;
	}
	*new_str = '\0';
	free(*str);
	*str = buffer;
}

static size_t	ft_newstrlen(char *str)		// with \0
{
	size_t		length;
	size_t		minus;
	char		*buf;

	length = 0;
	minus = 0;
	buf = str;
	while (*buf != ' ')
	{
		buf++;
		length++;
	}
	buf++;
	length++;
	if (*buf == '+')
		buf++;
	else if (*buf == '-')
	{
		buf++;
		minus++;
	}
	while (*buf == '0')
		buf++;
	if (*buf == ' ')
	{
		length++;
		minus = 0;
	}
	while (*buf != ' ')
	{
		buf++;
		length++;
	}

	buf++;
	length = length + minus + 1;
	minus = 0;
	if (*buf == '+')
		buf++;
	else if (*buf == '-')
	{
		buf++;
		minus++;
	}
	while (*buf == '0')
		buf++;
	if (*buf == '\0')
	{
		length++;
		minus = 0;
	}
	while (*buf != '\0')
	{
		buf++;
		length++;
	}
	return (length + minus + 1);
}

void			ft_clean_rooms(char **str)
{
	char	*new_str;
	char	*buffer;
	char	minus;
	char	*buf;

	new_str = (char*)malloc(ft_newstrlen(*str) * sizeof(char));
	buffer = new_str;
	minus = '\0';
	buf = *str;

	while (*buf != ' ')
	{
		*new_str = *buf;
		new_str++;
		buf++;
	}
	*new_str = *buf;
	new_str++;
	buf++;

	if (*buf == '+')
		buf++;
	else if (*buf == '-')
	{
		minus = '-';
		buf++;
	}
	while (*buf == '0')
		buf++;
	if (*buf == ' ')
	{
		*new_str = '0';
		new_str++;
	}
	else if (minus == '-')
	{
		*new_str = '-';
		new_str++;
	}
	minus = '\0';
	while (*buf != ' ')
	{
		*new_str = *buf;
		new_str++;
		buf++;
	}
	*new_str = *buf;
	new_str++;
	buf++;

	if (*buf == '+')
		buf++;
	else if (*buf == '-')
	{
		minus = '-';
		buf++;
	}
	while (*buf == '0')
		buf++;
	if (*buf == '\0')
	{
		*new_str = '0';
		new_str++;
	}
	else if (minus == '-')
	{
		*new_str = '-';
		new_str++;
	}
	minus = '\0';
	while (*buf != '\0')
	{
		*new_str = *buf;
		new_str++;
		buf++;
	}
	*new_str = '\0';
	
	free(*str);
	*str = buffer;
}
