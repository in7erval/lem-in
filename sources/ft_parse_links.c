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
	char	*first_part;
	char	*second_part;
	char	*curr_dash;
	t_room	*room1;
	t_room	*room2;

	ft_map_add(&(lemin->map), ft_strdup(buffer));
	curr_dash = buffer;
	while ((curr_dash = ft_strchr(curr_dash + 1, '-')))
	{
		first_part = ft_strsub(buffer, 0, curr_dash - buffer);
		second_part = ft_strsub(curr_dash + 1, 0, ft_strlen(curr_dash + 1));
		room1 = find_room_by_name(lemin->rooms, first_part);
		room2 = find_room_by_name(lemin->rooms, second_part);
		free(first_part);
		free(second_part);
		if (room1 && room2 && !is_in_union(room1, room2))
		{
			add_union(room1, room2);
			free(buffer);
			return (0);
		}
	}
	free(buffer);
	return (1);
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
