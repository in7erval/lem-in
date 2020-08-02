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

t_path	*new_elem_path(t_room *room)
{
	t_path *path;

	path = (t_path *)malloc(sizeof(t_path));
	path->room = room;
	path->next = NULL;
	path->ants = NULL;
	return (path);
}

void	add_elem_path(t_path **path, t_room *room)
{
	t_path *elem;
	t_path *buf;

	elem = new_elem_path(room);
	if (*path == NULL)
		*path = elem;
	else
	{
		buf = *path;
		while (buf->next)
			buf = buf->next;
		buf->next = elem;
	}
}

void	add_elem_path_start(t_path **path, t_room *room)
{
	t_path *elem;

	elem = new_elem_path(room);
	elem->next = (*path);
	(*path) = elem;
}

void	free_path(t_path **path)
{
	t_path *buf;
	t_path *kill;

	if (path && *path)
	{
		buf = *path;
		while (buf)
		{
			kill = buf;
			buf = buf->next;
			if (kill->ants)
				free_ants(&(kill->ants));
			free(kill);
		}
		*path = NULL;
	}
}

size_t	get_length_path(t_path *path)
{
	t_path	*buf;
	size_t	i;

	i = 0;
	buf = path;
	while (buf)
	{
		i++;
		buf = buf->next;
	}
	return (i);
}
