#include "lem_in.h"

static void		ft_delete_link(t_room *room, t_room *delete_room)
{
	t_list	*prev;
	t_list	*buf;

	prev = NULL;
	buf = room->links;
	while (buf)
	{
		if ((t_room *)buf->content == delete_room)
			break ;
		prev = buf;
		buf = buf->next;
	}
	if (buf)
	{
		room->count_links--;
		if (prev == NULL)
			room->links = room->links->next;
		else
			prev->next = buf->next;
		free(buf);
	}
}

static void		ft_delete_room(t_lemin *lemin, t_room *room)
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
		ft_free_room((t_room *)(buf->content));
		free(buf);
	}
}

void			delete_dead_ends(t_lemin *lemin, t_room *dead_end)
{
	t_room	*next;
	t_room	*cur;

	cur = dead_end;
	while (cur && cur->status == COMMON && cur->count_links <= 1)
	{
		next = NULL;
		if (cur->status == COMMON && cur->count_links == 1)
		{
			next = (t_room *)cur->links->content;
			ft_delete_link(next, cur);
		}
		ft_delete_room(lemin, cur);
		cur = next;
	}
}

void			ft_optimize(t_lemin *lemin)
{
	t_list	*cur;
	t_room	*room;

	cur = lemin->rooms;
	while (cur && (t_room *)cur->content)
	{
		room = (t_room *)cur->content;
		if (room->count_links <= 1 && room->status == COMMON)
		{
			delete_dead_ends(lemin, room);
			cur = lemin->rooms;
		}
		else
			cur = cur->next;
	}
}
