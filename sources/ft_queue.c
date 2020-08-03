/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:21 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue	*new_queue_elem(t_room *room)
{
	t_queue *queue;

	queue = (t_queue *)malloc(sizeof(t_queue));
	queue->room = room;
	queue->next = NULL;
	queue->prev = NULL;
	return (queue);
}

void	add_elem_queue(t_queue **queue, t_room *room)
{
	t_queue *buf;
	t_queue *elem;

	elem = new_queue_elem(room);
	if (*queue == NULL)
		*queue = elem;
	else
	{
		buf = *queue;
		while (buf->next)
			buf = buf->next;
		buf->next = elem;
		elem->prev = buf;
	}
}

t_queue	*poll_elem_queue(t_queue **queue)
{
	t_queue *elem;

	if (*queue == NULL)
		return (NULL);
	elem = *queue;
	*queue = (*queue)->next;
	return (elem);
}

void	print_queue(t_queue *queue)
{
	t_queue *x;

	x = queue;
	ft_printf("queue: ");
	while (x)
	{
		ft_printf("%s ", x->room->name);
		x = x->next;
	}
	ft_printf("\n");
}
