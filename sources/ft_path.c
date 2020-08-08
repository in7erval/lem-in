/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:17 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*ft_path_new(void)
{
	t_path		*path;
	static int	id;

	path = (t_path *)malloc(sizeof(t_path));
	path->id = id;
	path->len = -1;
	path->rooms = NULL;
	id++;
	return (path);
}

t_path	*ft_build_path(t_room *from, t_room *to)
{
	t_path	*path;
	t_room	*cur;

	path = ft_path_new();
	add_elem_path(path, from);
	cur = to;
	while (cur)
	{
		add_elem_path(path, cur);
		cur = cur->next;
	}
	return (path);
}

void	add_elem_path(t_path *path, t_room *room)
{
	ft_lstadd(&path->rooms, ft_lstnew(room, sizeof(t_room)));
	path->len++;
}

void	free_path(t_path *path)
{
	ft_lstdel(&path->rooms, NULL);
	free(path);
}
