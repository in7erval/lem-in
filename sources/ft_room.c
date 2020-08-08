/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_room.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:22 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*new_room(char *name, int x, int y)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	room->x = x;
	room->y = y;
	room->name = name;
	room->next = NULL;
	room->prev = NULL;
	room->status = COMMON;
	room->visited = 0;
	room->visited2 = 0;
	room->ants = 0;
	room->ant_number = 0;
	room->count_links = 0;
	room->links = NULL;
	return (room);
}

void	ft_free_room(t_room *room)
{
	free(room->name);
	free_list(&room->links);
	free(room);
}

void	free_rooms(t_list **rooms)
{
	t_list *kill;
	t_list *buf;

	if (rooms && *rooms)
	{
		buf = *rooms;
		while (buf)
		{
			kill = buf;
			ft_free_room((t_room *)kill->content);
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
