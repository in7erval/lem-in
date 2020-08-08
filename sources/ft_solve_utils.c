#include "lem_in.h"

void	reset_visit(t_lemin *lemin)
{
	t_list *buf;
	t_room *room;

	buf = lemin->rooms;
	while (buf)
	{
		room = (t_room *)(buf->content);
		room->visited = 0;
		room->visited2 = 0;
		buf = buf->next;
	}
}

int		can_traverse(t_tree *node, t_room *to)
{
	if (node->length > 0 && to->visited)
		return (0);
	if (node->length == 0 && to->visited2)
		return (0);
	if (node->room->prev != NULL && node->room->prev == to)
		return (0);
	if (node->intersect == to)
		return (0);
	if (node->intersect != NULL && node->room == node->intersect
		&& to != node->room->next)
		return (0);
	if (node->room->status == START && to->prev == node->room)
		return (0);
	if (to->status == START)
		return (0);
	return (1);
}

int		in_intersect(t_room *room1, t_room *room2)
{
	if (room1->next && room1->next == room2)
		return (0);
	if (room2->prev == NULL)
		return (0);
	if (room2->prev == room1)
		return (0);
	return (1);
}

int		out_intersect(t_room *room1, t_room *room2)
{
	return (room1->next && room1->next != room2);
}

void	visit(t_tree *tree)
{
	if (tree->room->status == COMMON && tree->room->next == NULL)
	{
		if (tree->length > 0)
			tree->room->visited = 1;
		else
			tree->room->visited2 = 1;
	}
}
