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

int		is_in_union(t_lemin *lemin, t_room *room, t_room *check_room)
{
	t_link *head;

	if (room == NULL || check_room == NULL || room == check_room)
		return (0);
	head = lemin->links;
	while (head)
	{
		if ((head->from == room && head->to == check_room)
			|| (head->from == check_room && head->to == room))
			return (1);
		head = head->next;
	}
	return (0);
}

int		add_union(t_lemin *lemin, char *room1_name, char *room2_name)
{
	t_room *room1;
	t_room *room2;

	room1 = find_room_by_name(lemin->rooms, room1_name);
	room2 = find_room_by_name(lemin->rooms, room2_name);
	if (room1 == NULL || room2 == NULL || (room1 == room2))
		return (1);
	if (!is_in_union(lemin, room1, room2))
		ft_pb_link(&(lemin->links), ft_create_link(room1, room2));
	return (0);
}
