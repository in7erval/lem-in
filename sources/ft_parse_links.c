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

#include "lem_in.h"

static int	ft_links_extension(t_lemin *lemin, char *buffer)
{
	char	**parts;
	t_room	*room1;
	t_room	*room2;

	ft_map_add(&(lemin->map), ft_strdup(buffer));
	parts = ft_strsplit(buffer, '-');
	free(buffer);
	room1 = find_room_by_name(lemin->rooms, parts[0]);
	room2 = find_room_by_name(lemin->rooms, parts[1]);
	if (!room1 || !room2 || is_in_union(lemin, room1, room2))
	{
		ft_freesplit(parts);
		return (1);
	}
	add_union(lemin, parts[0], parts[1]);
	ft_freesplit(parts);
	return (0);
}

int			ft_links(t_lemin *lemin, char *buffer, int *has_links)
{
	*has_links = 1;
	if (ft_links_extension(lemin, buffer))
		return (0);
	while (get_next_line(0, &buffer) > 0)
		if (ft_iscomment(buffer))
		{
			ft_map_add(&(lemin->map), ft_strdup(buffer));
			free(buffer);
			continue;
		}
		else if (ft_islinks(buffer))
		{
			if (ft_links_extension(lemin, buffer))
				return (0);
		}
		else
		{
			free(buffer);
			return (0);
		}
	return (1);
}
