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

int	ft_markup_bfs(t_lemin *lemin)
{
	t_queue *queue;

	queue = NULL;
	add_elem_queue(&queue, lemin->start);
	lemin->start->bfs_level = 0;
	bfs(lemin, queue);
	if (lemin->end->status == -1)
		return (1);
	return (0);
}
