#include "lem_in.h"

static int		room_link(t_link *link, t_room *room)
{
	if (link->from == room || link->to == room)
		return (1);
	return (0);
}

static int		ft_delete_links(t_lemin *lemin, t_room *room, int (*f)(t_link *link, t_room *room))
{
	t_link *buf;
	t_link *prev;

	prev = NULL;
	buf = lemin->links;
	while (buf)
	{
		if (f(buf, room) == 1)
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
		free(buf);
		return (1);
	}
	return (0);
}

static void	ft_delete_room(t_lemin *lemin, t_room *room)
{
	t_list *buf;
	t_list *prev;

	prev = NULL;
	buf = lemin->rooms;
	while (buf)
	{
		if ((t_room *)buf->content == room)
			break ;
		prev = buf;
		buf = buf->next;
	}
	if (buf)
	{
		if (prev == NULL)
			lemin->rooms = lemin->rooms->next;
		else
			prev->next = buf->next;
		free(buf);
	}
}

void	ft_optimize(t_lemin *lemin)
{
	t_list	*cur;
	t_room	*room;

	cur = lemin->rooms;
	while (cur && (t_room *)cur->content)
	{
		room = (t_room *)cur->content;
		if (room->count_links <= 1 && room->status == COMMON)
		{
			ft_delete_links(lemin, room, room_link);
			ft_delete_room(lemin, room);
			cur = lemin->rooms;
		}
		else
			cur = cur->next;
	}
}
