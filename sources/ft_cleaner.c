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

size_t 			ft_strlen_number(char *number)
{
	size_t size;

	size = 0;
	if (*number == '+')
		number++;
	if (*number == '-')
	{
		number++;
		size++;
	}
	while (*number == '0')
		number++;
	while (*number)
	{
		size++;
		number++;
	}
	return (size);
}

char 			*ft_clean_number(char *number)
{
	char *pure;
	char *start;

	pure = ft_strnew(ft_strlen_number(number));
	start = pure;
	if (*number == '+')
		number++;
	if (*number == '-')
	{
		*(pure++) = '-';
		number++;
	}
	while (*number == '0')
		number++;
	while (*number)
	{
		*pure = *number;
		number++;
		pure++;
	}
	return (start);
}

char			*ft_strjoin_three(char *str1, char *str2, char *str3)
{
	char *new_str;
	char *start;

	new_str = ft_strnew(ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 2);
	start = new_str;
	while (*str1)
		*(new_str++) = *(str1++);
	*(new_str++) = ' ';
	while (*str2)
		*(new_str++) = *(str2++);
	*(new_str++) = ' ';
	while (*str3)
		*(new_str++) = *(str3++);
	return (start);
}

void			ft_clean_rooms(char **str)
{
	char **split;
	char *new_str;
	char *x;
	char *y;
	char *del;

	split = ft_strsplit(*str, ' ');
	x = ft_clean_number(split[1]);
	y = ft_clean_number(split[2]);
	new_str = ft_strjoin_three(split[0], x, y);
	ft_freesplit(split);
	free(x);
	free(y);
	del = *str;
	*str = new_str;
	free(del);
}