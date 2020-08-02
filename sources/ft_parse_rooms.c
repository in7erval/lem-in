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

static int	ft_check_signal(t_lemin *lemin, int signal, t_room *room)
{
	if (signal)
	{
		if (find_room_by_signal(lemin->rooms, signal))
			return (1);
		room->status = signal;
		if (signal == START)
			lemin->start = room;
		if (signal == END)
			lemin->end = room;
	}
	return (0);
}

static int	ft_rooms_extension(t_lemin *lemin, char *buffer,
								int signal, int bonus)
{
	char	**parts;
	t_room	*room;

	if (bonus == 1)
		ft_clean_rooms(&buffer);
	ft_map_add(&(lemin->map), ft_strdup(buffer));
	parts = ft_strsplit(buffer, ' ');
	free(buffer);
	if (find_room_by_name(lemin->rooms, parts[0]) ||
		find_room_by_coordinates(lemin->rooms, ft_atoi(parts[1]),
	ft_atoi(parts[2])))
	{
		ft_freesplit(parts);
		return (1);
	}
	room = new_room(ft_strdup(parts[0]),
					ft_atoi(parts[1]), ft_atoi(parts[2]));
	ft_freesplit(parts);
	push_back_room(&(lemin->rooms), room);
	if (ft_check_signal(lemin, signal, room))
		return (1);
	return (0);
}

static int	ft_rooms_check(t_lemin *lemin, char *buf,
							int *s, int bonus)
{
	if (ft_isknowncommand(buf) && !(*s) && (*s = ft_isknowncommand(buf)))
	{
		ft_map_add(&(lemin->map), ft_strdup(buf));
		free(buf);
	}
	else if (ft_iscomment(buf))
	{
		ft_map_add(&(lemin->map), ft_strdup(buf));
		free(buf);
		//return (2);
	}
	else if (ft_isrooms(buf))
	{
		if (ft_rooms_extension(lemin, buf, *s, bonus))
			return (0);
		*s = 0;
	}
	else if (ft_islinks(buf) && !*s && lemin->start && lemin->end)
		return (ft_links(lemin, buf));
	else
	{
		free(buf);
		return (0);
	}
	return (2);
}

int			ft_rooms(t_lemin *lemin, int bonus)
{
	char	*buffer;
	int		signal;
	int		check;

	signal = 0;
	while (get_next_line(0, &buffer) > 0)
	{
		check = ft_rooms_check(lemin, buffer, &signal, bonus);
		if (check == 2)
			continue;
		else if (check == 1)
			return (1);
	}
	free(buffer);
	return (0);
}
