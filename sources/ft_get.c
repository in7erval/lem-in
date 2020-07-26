#include "lem-in.h"

t_list	*get_names(t_room *rooms)
{
	t_list *names;
	t_room *buf;

	names = NULL;
	buf = rooms;
	while (buf)
	{
		ft_lstadd_back(&names, ft_lstnew(buf->name, 0));
		buf = buf->next;
	}
	return (names);
}

t_room *get_same_level(t_room *rooms, t_list **names, int level)
{
	t_list *buf;
	t_list *prev;
	t_list *kill;
	t_room *room;

	buf = *names;
	prev = NULL;
	while (buf)
	{
		room = find_room_by_name(rooms, buf->content);
		if (room->bfs_level == level)
		{
			kill = buf;
			if (prev == NULL)
				*names = (*names)->next;
			else
				prev->next = buf->next;
			free(kill);
			return (room);
		}
		else
		{
			prev =  buf;
			buf = buf->next;
		}
	}
	return (NULL);
}

int 	get_highest_bfs_level(t_room *rooms)
{
	t_room	*buf;
	int 	level;

	level = 0;
	buf = rooms;
	while (buf)
	{
		if (buf->bfs_level > level && buf->status != END)
			level = buf->bfs_level;
		buf = buf->next;
	}
	return (level);
}

t_room *get_start_room(t_room *rooms)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		if (buf->status == START)
			return (buf);
		buf = buf->next;
	}
	return (NULL);
}


t_room *find_start_room(t_room *rooms)
{
	t_room *room;

	room = rooms;
	while (room)
	{
		if (room->status == START)
			return (room);
		room = room->next;
	}
	return (NULL);
}