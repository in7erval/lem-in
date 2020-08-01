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

t_room	*new_room(char *name, int x, int y)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	room->x = x;
	room->y = y;
	room->name = name;
	room->next = NULL;
	room->prev = NULL;
	room->bfs_level = -1;
	room->status = COMMON;
	room->count_input = 0;
	room->count_output = 0;
	return (room);
}

void	push_back_room(t_room **head, t_room *room)
{
	t_room *buf;

	buf = *head;
	if (*head == NULL)
	{
		*head = room;
		return ;
	}
	while (buf->next)
		buf = buf->next;
	buf->next = room;
	room->prev = buf;
}

void	free_rooms(t_room **rooms)
{
	t_room *kill;
	t_room *buf;

	if (rooms && *rooms)
	{
		buf = *rooms;
		while (buf)
		{
			kill = buf;
			free(kill->name);
			buf = buf->next;
			free(kill);
		}
		*rooms = NULL;
	}
}

void	free_list(t_list **list)
{
	t_list *kill;
	t_list *buf;

	if (list && *list)
	{
		buf = *list;
		while (buf)
		{
			kill = buf;
			buf = buf->next;
			free(kill);
		}
		*list = NULL;
	}
}
