#include "lem-in.h"

int 	check_one_level(t_room *room, t_rooms *buf)
{
	t_room *r;

	r = buf->room;
	if (r->bfs_level == room->bfs_level || r->bfs_level == -1 || room->bfs_level == -1)
		return (1);
	return (0);
}

int 	check_less_level(t_room *room, t_rooms *buf)
{
	t_room *r;

	r = buf->room;
	if (r->bfs_level < room->bfs_level)
		return (1);
	return (0);
}

int 	input_fork_delete(t_room *to_room, t_rooms *buf)
{
	if (buf->room == to_room)
		return (1);
	return (0);
}

int 	not_equal_room(t_room *room, t_rooms *buf)
{
	if (buf->room != room)
		return (1);
	return (0);
}

int 	check_dead_end(t_room *room, t_rooms *buf)
{
	t_room *r;

	r = buf->room;
	if (r->count_output == 0 && r->status != END && r->status != START)
	{
		//ft_printf("{cyan}DEAD_END IN {red}%s {cyan}FROM {red}%s{eoc}\n", r->name, room->name);
		return (1);
	}
	if (room->count_output <= 0 && room->status != END && room->status != START)
	{
		//ft_printf("{cyan}DEAD_END IN {red}%s {cyan}FROM {red}%s{eoc}\n", room->name, r->name);
		return (1);
	}
	return (0);
}

int	ft_delete_elem(t_rooms **list, t_room *r, int (*f)(t_room *room, t_rooms *buf))
{
	t_rooms *buf;
	t_rooms *kill;
	t_rooms *prev;
	int 	flag;

	flag = 0;
	prev = NULL;
	buf = *list;
	while (buf)
	{
		if (f(r, buf) == 1)
		{
			flag = 1;
			kill = buf;
			if (prev == NULL)
				*list = (*list)->next;
			else
			{
				prev->next = buf->next;
				if (buf->next != NULL)
					buf->next->prev = prev;
			}
			buf = buf->next;
			free(kill);
		}
		else
		{
			prev = buf;
			buf = buf->next;
		}
	}
	return (flag);
}