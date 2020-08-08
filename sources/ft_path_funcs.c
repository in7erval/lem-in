#include "lem_in.h"

static int		has_path(t_room *room)
{
	return (room->next != NULL && room->prev != NULL);
}

static t_room	*path_start(t_room *room)
{
	t_room *start;

	start = room;
	while (start->prev && start->prev->status != START)
		start = start->prev;
	return (start);
}

static void		break_path(t_room *room)
{
	t_room	*cur;
	t_room	*next;

	cur = path_start(room);
	while (cur && cur->status == COMMON)
	{
		next = cur->next;
		cur->prev = NULL;
		cur->next = NULL;
		cur = next;
	}
}

static void		connect(t_room *prev, t_room *next)
{
	if (prev != NULL && prev->status != COMMON && next->status != COMMON)
		return ;
	if (prev != NULL && prev->status == COMMON)
		prev->next = next;
	if (next->status == COMMON)
		next->prev = prev;
}

void			rebuild_paths(t_path *path)
{
	t_list	*cur;
	t_room	*prev;

	cur = path->rooms;
	while (cur)
	{
		if (has_path((t_room *)(cur->content)))
			break_path((t_room *)(cur->content));
		cur = cur->next;
	}
	cur = path->rooms;
	prev = NULL;
	while (cur)
	{
		connect(prev, (t_room *)(cur->content));
		prev = (t_room *)(cur->content);
		cur = cur->next;
	}
}
