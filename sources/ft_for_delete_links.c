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

int		check_one_level(t_link *link)
{
	if (link->to->bfs_level == link->from->bfs_level
		|| link->to->bfs_level == -1 || link->from->bfs_level == -1)
		return (1);
	return (0);
}

int		check_dead_end(t_link *link)
{
	if (link->from->status != START &&
		link->from->count_input == 0 && link->from->count_output > 0)
		return (1);
	if (link->to->status != END &&
		link->to->count_output == 0 && link->to->count_input > 0)
		return (1);
	return (0);
}
