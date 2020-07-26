#include "lem-in.h"

int 	is_in_union(t_room *room, t_room *check_room)
{
	t_rooms *head;

	if (room == NULL || check_room == NULL || room == check_room)
		return (0);
	head = room->union_room;
	while (head)
	{
		if (head->room == check_room)
			return (1);
		head = head->next;
	}
	return (0);
}

int	add_union(t_room *rooms, char *room1_name, char *room2_name)
{
	t_room *room1;
	t_room *room2;

	room1 = find_room_by_name(rooms, room1_name);
	room2 = find_room_by_name(rooms, room2_name);
	if (room1 == NULL || room2 == NULL || (room1 == room2))
		return (1);
	if (!is_in_union(room1, room2))
		add_room_to_rooms_union(&(room1->union_room), room2);
	if (!is_in_union(room2, room1))
		add_room_to_rooms_union(&(room2->union_room), room1);
	return (0);
}

