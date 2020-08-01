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

static void	check_and_add(t_queue **queue, t_link *buf, t_room *room)
{
	if (buf->from == room && buf->to->bfs_level == -1)
	{
		buf->to->bfs_level = room->bfs_level + 1;
		add_elem_queue(queue, buf->to);
	}
	else if (buf->to == room && buf->from->bfs_level == -1)
	{
		buf->from->bfs_level = room->bfs_level + 1;
		add_elem_queue(queue, buf->from);
	}
}

void		bfs(t_lemin *lemin, t_queue *queue)
{
	t_link	*buf;
	t_queue	*q;

	q = poll_elem_queue(&queue);
	if (q == NULL)
		return ;
	if (q->room->status != END)
	{
		buf = lemin->links;
		while (buf)
		{
			check_and_add(&queue, buf, q->room);
			buf = buf->next;
		}
		lemin->bfs_level = q->room->bfs_level;
	}
	else
		lemin->end->bfs_level = MAX_INT;
	free(q);
	bfs(lemin, queue);
}

void		delete_useless_links(t_lemin *lemin)
{
	int flag;

	flag = 1;
	while (flag)
		flag = ft_delete_links(lemin, check_one_level);
}

void		delete_all_dead_ends(t_lemin *lemin)
{
	int	flag;

	flag = 1;
	while (flag)
		flag = ft_delete_links(lemin, check_dead_end);
}

void		align_all_links(t_lemin *lemin)
{
	t_link *link;
	t_room *buf_room;

	link = lemin->links;
	while (link)
	{
		if (link->from->bfs_level > link->to->bfs_level)
		{
			buf_room = link->from;
			link->from = link->to;
			link->to = buf_room;
		}
		link = link->next;
	}
}
