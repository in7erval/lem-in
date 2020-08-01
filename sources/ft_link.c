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

t_link		*ft_create_link(t_room *room1, t_room *room2)
{
	t_link *link;

	if (!(link = (t_link *)malloc(sizeof(t_link))))
		error_exit(MALLOC_ERROR);
	link->from = room1;
	link->to = room2;
	link->next = NULL;
	return (link);
}

void		ft_pb_link(t_link **links, t_link *link)
{
	t_link *buf;

	if (*links)
	{
		buf = (*links);
		while (buf->next)
			buf = buf->next;
		buf->next = link;
	}
	else
		*links = link;
}

void		free_links(t_link **links)
{
	t_link	*link;

	if (links && *links)
	{
		while (*links)
		{
			link = *links;
			*links = link->next;
			free(link);
		}
	}
}

t_room		*get_room_link_from(t_link *links, t_room *from)
{
	while (links)
	{
		if (links->from == from)
			return (links->to);
		links = links->next;
	}
	return (NULL);
}

void		print_links(t_link *links)
{
	while (links)
	{
		ft_printf("{yellow}{bold}%s{eoc}-{yellow}{bold}%s{eoc}\n",
				links->from->name, links->to->name);
		links = links->next;
	}
}
