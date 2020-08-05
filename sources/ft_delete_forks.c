/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:07 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
int		check_output_fork(t_lemin *lemin, t_room *room)
{
	t_link *link;

	if (room->status == START)
		return (0);
	if (room->count_output > 1)
		return (1);
	link = lemin->links;
	while (link)
	{
		if (link->to == room)
		{
			if (check_output_fork(lemin, link->from))
				return (1);
		}
		link = link->next;
	}
	return (0);
}

void	delete_input_forks(t_lemin *lemin, t_room *room)
{
	t_link	*check_link;
	t_link	*cur;
	int		flag;
	t_link	*best_links;


	cur = lemin->links;
	best_links = ;
	flag = 1;
	while (cur)
	{
		check_link = cur;
		cur = cur->next;
		if (check_link->to == room)
		{
			if (check_output_fork(lemin, check_link->from))
				ft_delete_link(lemin, check_link);
			else
				ft_pb_link(&best_links)
		}
	}
}

void	delete_all_input_forks(t_lemin *lemin)
{
	t_room	*room;
	int		level;

	level = 1;
	while (level <= lemin->bfs_level)
	{
		room = lemin->rooms;
		while (room)
		{
			if (room->bfs_level == level && room->count_input > 1)
				delete_input_forks(lemin, room);
			room = room->next;
		}
		level++;
	}
}

void	delete_output_forks(t_lemin *lemin, t_room *room)
{
	t_list *pathes;
	t_path *path;
	t_list *buf_path;

	pathes = get_pathes(lemin, room);
	path = get_min_len_path(pathes);
	buf_path = pathes;
	while (buf_path)
	{
		if (buf_path->content != path)
			ft_delete_links_from_path(lemin, buf_path->content);
		buf_path = buf_path->next;
	}
	free_pathes(&pathes);
}

void	delete_all_output_forks(t_lemin *lemin)
{
	t_room	*room;
	int		level;

	level = lemin->bfs_level;
	while (level > 0)
	{
		room = lemin->rooms;
		while (room)
		{
			if (room->bfs_level == level && room->count_output > 1)
				delete_output_forks(lemin, room);
			room = room->next;
		}
		level--;
	}
}
*/