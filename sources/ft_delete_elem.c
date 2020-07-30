#include "lem-in.h"

int 	check_one_level(t_link *link)
{
	if (link->to->bfs_level == link->from->bfs_level
		|| link->to->bfs_level == -1 || link->from->bfs_level == -1)
		return (1);
	return (0);
}

int 	check_dead_end(t_link *link)
{
	if (link->from->status != START &&
		link->from->count_input == 0 && link->from->count_output > 0)
		return (1);
	if (link->to->status != END &&
		link->to->count_output == 0 && link->to->count_input > 0)
		return (1);
	return (0);
}

int		ft_delete_links(t_lemin *lemin, int (*f)(t_link *link))
{
	t_link *buf;
	t_link *prev;

	prev = NULL;
	buf = lemin->links;
	while (buf && f(buf) != 1)
	{
		prev = buf;
		buf = buf->next;
	}
	if (buf)
	{
		if (prev == NULL)
			lemin->links = lemin->links->next;
		else
			prev->next = buf->next;
		if (buf->from->count_output > 0)
			buf->from->count_output--;
		if (buf->to->count_input > 0)
			buf->to->count_input--;
		free(buf);
		return (1);
	}
	return (0);
}

void	ft_delete_link(t_lemin *lemin, t_link *link)
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
	if (buf)
	{
		if (prev == NULL)
			lemin->links = lemin->links->next;
		else
			prev->next = buf->next;
		if (buf->from->count_output > 0)
			buf->from->count_output--;
		if (buf->to->count_input > 0)
			buf->to->count_input--;
		free(buf);
	}
}

void	ft_delete_input_except(t_lemin *lemin, t_link *link)
{
	t_link	*buf;
	t_link	*del;

	buf = lemin->links;
	while (buf)
	{
		del = buf;
		buf = buf->next;
		if (del->to == link->to && del != link)
			ft_delete_link(lemin, del);
	}
}

void	ft_delete_links_from_path(t_lemin *lemin, t_path *path)
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
