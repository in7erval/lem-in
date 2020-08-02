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

static void	ft_delete_links_extention(t_link *buf)
{
	if (buf->from->count_output > 0)
		buf->from->count_output--;
	if (buf->to->count_input > 0)
		buf->to->count_input--;
}

int			ft_delete_links(t_lemin *lemin, int (*f)(t_link *link))
{
	t_link *buf;
	t_link *prev;

	prev = NULL;
	buf = lemin->links;
	while (buf)
	{
		if (f(buf) == 1)
			break ;
		prev = buf;
		buf = buf->next;
	}
	if (buf)
	{
		if (prev == NULL)
			lemin->links = lemin->links->next;
		else
			prev->next = buf->next;
		ft_delete_links_extention(buf);
		free(buf);
		return (1);
	}
	return (0);
}

void		ft_delete_link(t_lemin *lemin, t_link *link)
{
	t_link *buf;
	t_link *prev;

	prev = NULL;
	buf = lemin->links;
	while (buf && buf != link)
	{
		prev = buf;
		buf = buf->next;
	}
	if (buf && prev == NULL)
		lemin->links = lemin->links->next;
	else if (buf)
		prev->next = buf->next;
	if (link->from->count_output > 0)
		link->from->count_output--;
	if (link->to->count_input > 0)
		link->to->count_input--;
	free(link);
}

int			ft_delete_input_except(t_lemin *lemin, t_link *link)
{
	t_link	*buf;
	t_link	*del;
	int		flag;

	flag = 0;
	buf = lemin->links;
	while (buf)
	{
		del = buf;
		buf = buf->next;
		if (del->to == link->to && del != link)
		{
			flag = 1;
			ft_delete_link(lemin, del);
		}
	}
	return (flag);
}

void		ft_delete_links_from_path(t_lemin *lemin, t_path *path)
{
	t_link	*buf;
	t_link	*del;
	t_path	*p;

	p = path;
	while (p)
	{
		buf = lemin->links;
		while (buf)
		{
			del = buf;
			buf = buf->next;
			if (p->next && del->from == p->room
				&& del->to == p->next->room)
				ft_delete_link(lemin, del);
		}
		p = p->next;
	}
}
