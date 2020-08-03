/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:15 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	ft_ants_check(t_map **map, char *buffer, int *num_ants, int bonus)
{
	if (ft_iscomment(buffer))
	{
		ft_map_add(map, ft_strdup(buffer));
		free(buffer);
		return (2);
	}
	else if (ft_isants(buffer))
	{
		if (bonus == 1)
			ft_clean_ants(&buffer);
		ft_map_add(map, ft_strdup(buffer));
		*num_ants = ft_atoi(buffer);
		free(buffer);
		return (1);
	}
	else
	{
		free(buffer);
		return (0);
	}
}

static int	ft_ants(t_map **map, int bonus)
{
	char	*buffer;
	int		num_ants;
	int		check;

	while (get_next_line(0, &buffer) > 0)
	{
		check = ft_ants_check(map, buffer, &num_ants, bonus);
		if (check == 2)
			continue;
		else if (check == 1)
			return (num_ants);
		else
			return (0);
	}
	return (0);
}

int			ft_parse(t_lemin *lemin)
{
	lemin->num_ants = ft_ants(&(lemin->map), lemin->c_bonus);
	if (lemin->num_ants != 0 && ft_rooms(lemin) && lemin->end && lemin->start)
		return (1);
	return (0);
}
