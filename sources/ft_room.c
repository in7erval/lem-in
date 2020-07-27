#include "lem-in.h"

t_room	*new_room(char *name, int x, int y)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	room->x = x;
	room->y = y;
	room->name = name;
	room->next = NULL;
	room->prev = NULL;
	room->union_room = NULL;
	room->bfs_level = -1;
	room->status = COMMON;
	room->bfs_status = NOT_USED;
	room->aligned_union_room = NULL;
	room->count_input = 0;
	room->count_output = 0;
	return (room);
}

void	push_back_room(t_room **head, t_room *room)
{
	t_room *buf;

	buf = *head;
	if (*head == NULL)
	{
		*head = room;
		return ;
	}
	while (buf->next)
		buf = buf->next;
	buf->next = room;
	room->prev = buf;
}

void	free_rooms(t_room **rooms)
{
	t_room *kill;
	t_room *buf;

	if (rooms && *rooms)
	{
		buf = *rooms;
		while (buf)
		{
			kill = buf;
			free_rooms_list(&(kill->union_room));
			free_rooms_list(&(kill->aligned_union_room));
			//free(kill->name); //todo: UNCOMMENT IT!
			buf = buf->next;
			free(kill);
		}
		*rooms = NULL;
	}
}

t_rooms *new_element_rooms(t_room *room)
{
	t_rooms *elem;

	elem = (t_rooms *)malloc(sizeof(t_rooms));
	elem->room = room;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void	free_rooms_list(t_rooms **list)
{
	t_rooms *kill;
	t_rooms *buf;

	if (list && *list)
	{
		buf = *list;
		while (buf)
		{
			kill = buf;
			buf = buf->next;
			free(kill);
		}
		*list = NULL;
	}
}

int 	list_contains(t_rooms *head, t_rooms *elem)
{
	while (head)
	{
		if (head->room == elem->room)
			return (1);
		head = head->next;
	}
	return (0);
}

void	free_list(t_list **list)
{
	t_list *kill;
	t_list *buf;

	if (list && *list)
	{
		buf = *list;
		while (buf)
		{
			kill = buf;
			buf = buf->next;
			free(kill);
		}
		*list = NULL;
	}
}

