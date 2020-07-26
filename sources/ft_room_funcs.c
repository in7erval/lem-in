#include "lem-in.h"

void	add_room_to_rooms_union(t_rooms **union_rooms, t_room *room)
{
	t_rooms *new;

	new = new_element_rooms(room);
	if (!(*union_rooms))
		(*union_rooms) = new;
	else
	{
		new->next = (*union_rooms);
		(*union_rooms)->prev = new;
		*union_rooms = new;
	}
}

void	add_room_to_rooms_union_back(t_rooms **rooms_union, t_room *room)
{
	t_rooms	*tmp;
	t_rooms *new;

	new = new_element_rooms(room);
	tmp = *rooms_union;
	if (tmp == NULL)
		*rooms_union = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
}

t_room *find_room_by_name(t_room *rooms, char *name)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		if (ft_strcmp(buf->name, name) == 0)
			return buf;
		buf = buf->next;
	}
	return (NULL);
}

t_room *find_room_by_signal(t_room *rooms, int signal)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		if (buf->status == signal)
			return buf;
		buf = buf->next;
	}
	return (NULL);
}

t_room *find_room_by_coordinates(t_room *rooms, int x, int y)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		if (buf->x == x && buf->y == y)
			return buf;
		buf = buf->next;
	}
	return (NULL);
}

