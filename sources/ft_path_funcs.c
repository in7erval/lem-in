/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:18 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
t_list	*get_pathes(t_lemin *lemin, t_room *room)
{
	t_list	*pathes;
	t_path	*path;
	t_link	*link;

	pathes = NULL;
	link = lemin->links;
	while (link)
	{
		if (link->from == room)
		{
			path = get_path_to_end(lemin, link->to);
			if (path != NULL)
			{
				add_elem_path_start(&path, room);
				ft_lstadd_back(&pathes, ft_lstnew(path, get_length_path(path)));
			}
		}
		link = link->next;
	}
	return (pathes);
}
*/
/*
void	free_pathes(t_list **pathes)
{
	t_list *buf;

	buf = *pathes;
	while (buf)
	{
		free_path((t_path **)&(buf->content));
		buf = buf->next;
	}
	free_list(pathes);
}

t_path	*get_min_len_path(t_list *pathes)
{
	size_t	min_len;
	t_list	*buf;
	t_path	*min_path;

	if (pathes == NULL)
		return (0);
	min_len = pathes->content_size;
	min_path = pathes->content;
	buf = pathes->next;
	while (buf)
	{
		if (buf->content_size < min_len)
		{
			min_len = buf->content_size;
			min_path = buf->content;
		}
		buf = buf->next;
	}
	return (min_path);
}

t_room	*get_room_by_roomnumber(t_path *path, int room_number)
{
	int i;

	i = 0;
	while (i < room_number)
	{
		i++;
		if (path == NULL)
			return (NULL);
		path = path->next;
	}
	return (path->room);
}
 */
/*
t_path	*get_path_to_end(t_lemin *lemin, t_room *room)
{
	t_path	*path;
	t_room	*buf;

	path = NULL;
	buf = room;
	while (buf)
	{
		add_elem_path(&path, buf);
		if (buf->status == END)
			break ;
		if (buf->count_output == 0)
		{
			free_path(&path);
			return (NULL);
		}
		buf = get_room_link_from(lemin->links, buf);
	}
	return (path);
}
*/