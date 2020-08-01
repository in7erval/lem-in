/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/02/07 13:43:30 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int				ft_isknowncommand(char *str)
{
	if (!ft_strcmp(str, "##start"))
		return (START);
	else if (!ft_strcmp(str, "##end"))
		return (END);
	return (0);
}

int				ft_iscomment(const char *str)
{
	if (*str == '#')
		return (COMMON);
	return (0);
}

int				ft_isants(char *str)
{
	if (ft_isinteger(str) && ft_atoi(str) > 0)
		return (1);
	return (0);
}

int				ft_isrooms(char *str)
{
	char	**parts;

	if (count_of_words(str, ' ') != 3)
		return (0);
	parts = ft_strsplit(str, ' ');
	if (parts[0][0] == 'L' ||
		!ft_isinteger(parts[1]) || !ft_isinteger(parts[2]))
	{
		ft_freesplit(parts);
		return (0);
	}
	ft_freesplit(parts);
	return (1);
}

int				ft_islinks(char *str)
{
	char	**parts;

	if (count_of_words(str, '-') != 2)
		return (0);
	parts = ft_strsplit(str, '-');
	if (parts[0][0] == 'L' || parts[1][0] == 'L'
		|| !ft_strcmp(parts[0], parts[1]))
	{
		ft_freesplit(parts);
		return (0);
	}
	ft_freesplit(parts);
	return (1);
}
