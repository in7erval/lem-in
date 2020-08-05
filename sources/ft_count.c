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

void	count_links(t_lemin *lemin)
{
	t_link	*link;
	t_list	*cur;
	t_room	*room;

	cur = lemin->rooms;
	while (cur)
	{
		room = (t_room *)cur->content;
		room->count_links = 0;
		link = lemin->links;
		while (link)
		{
			if (link->from == room || link->to == room)
				room->count_links++;
			link = link->next;
		}
		cur = cur->next;
	}
}