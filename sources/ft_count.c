/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:07 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
void	count_input_output_links(t_lemin *lemin, t_room *room)
{
	t_link	*link;

	room->count_input = 0;
	room->count_output = 0;
	link = lemin->links;
	while (link)
	{
		if (link->to == room)
			room->count_input++;
		if (link->from == room)
			room->count_output++;
		link = link->next;
	}
}

void	count_all_input_output_links(t_lemin *lemin)
{
	t_room *room;

	room = lemin->rooms;
	while (room)
	{
		count_input_output_links(lemin, room);
		room = room->next;
	}
}
*/

static void	count_links(t_lemin *lemin, t_room *room)
{
	t_link *link;

	room->count_links = 0;
	link = lemin->links;
	while (link)
	{
		if (link->to == room || link->from == room)
			room->count_links++;
		link = link->next;
	}
}

void		count_all_links(t_lemin *lemin)
{
	t_list	*buf;
	t_room	*room;

	buf = lemin->rooms;
	while (buf)
	{
		room = (t_room *)(buf->content);
		count_links(lemin, room);
		buf = buf->next;
	}
}