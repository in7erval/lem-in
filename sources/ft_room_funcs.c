#include "lem-in.h"

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


