/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/10 15:25:10 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

int		count_of_words(const char *str, char c)
{
	int		i;

	i = 0;
	if (str == NULL || *str == c ||
		ft_strlen(str) == 0 || *(str + ft_strlen(str) - 1) == c)
		return (0);
	while (*str)
	{
		if (*str == c && *(str + 1) == c)
			return (0);
		if (*str != c)
			if (*(str + 1) == c || *(str + 1) == '\0')
				i++;
		str++;
	}
	return (i);
}

void	ft_free_lemin(t_lemin *lemin)
{
	if (lemin)
	{
		if (lemin->map)
			ft_map_clean(&(lemin->map));
		if (lemin->rooms)
			free_rooms(&(lemin->rooms));
		if (lemin->group)
			free_group(lemin->group);
		if (lemin->answer)
			free_answer(&(lemin->answer));
		free(lemin);
	}
}

int		ft_free_error(t_lemin *lemin)
{
	ft_free_lemin(lemin);
	ft_putstr_fd("ERROR\n", 2);
	return (1);
}

int		ft_min(int a, int b)
{
	return ((a > b) ? b : a);
}
