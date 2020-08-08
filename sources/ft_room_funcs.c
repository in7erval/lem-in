/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_room_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:23 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*find_room_by_name(t_list *rooms, char *name)
{
	t_list *buf;

	buf = rooms;
	while (buf)
	{
		if (ft_strcmp(((t_room *)(buf->content))->name, name) == 0)
			return (((t_room *)(buf->content)));
		buf = buf->next;
	}
	return (NULL);
}

t_room	*find_room_by_signal(t_list *rooms, int signal)
{
	t_list *buf;

	buf = rooms;
	while (buf)
	{
		if (((t_room *)(buf->content))->status == signal)
			return ((t_room *)(buf->content));
		buf = buf->next;
	}
	return (NULL);
}

t_room	*find_room_by_coordinates(t_list *rooms, int x, int y)
{
	t_list *buf;

	buf = rooms;
	while (buf)
	{
		if (((t_room *)(buf->content))->x == x &&
			((t_room *)(buf->content))->y == y)
			return ((t_room *)(buf->content));
		buf = buf->next;
	}
	return (NULL);
}
