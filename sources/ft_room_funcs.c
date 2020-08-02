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

t_room	*find_room_by_name(t_room *rooms, char *name)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		if (ft_strcmp(buf->name, name) == 0)
			return (buf);
		buf = buf->next;
	}
	return (NULL);
}

t_room	*find_room_by_signal(t_room *rooms, int signal)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		if (buf->status == signal)
			return (buf);
		buf = buf->next;
	}
	return (NULL);
}

t_room	*find_room_by_coordinates(t_room *rooms, int x, int y)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		if (buf->x == x && buf->y == y)
			return (buf);
		buf = buf->next;
	}
	return (NULL);
}
