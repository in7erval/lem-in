/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_room_union.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:23 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_in_union(t_room *room, t_room *check_room)
{
	t_list	*cur;
	t_room	*buf_room;

	if (room == NULL || check_room == NULL || room == check_room)
		return (0);
	cur = room->links;
	while (cur)
	{
		buf_room = (t_room *)cur->content;
		if (buf_room == check_room)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int		add_union(t_room *room1, t_room *room2)
{
	if (room1 == NULL || room2 == NULL || (room1 == room2))
		return (1);
	if (!is_in_union(room1, room2))
	{
		ft_lstadd(&room1->links, ft_lstnew(room2, sizeof(t_room)));
		ft_lstadd(&room2->links, ft_lstnew(room1, sizeof(t_room)));
		room1->count_links++;
		room2->count_links++;
	}
	return (0);
}
