#include "lem-in.h"

void	count_input_output_links(t_lemin *lemin, t_room *room)
{
	t_link	*link;

	room->count_input = 0;
	room->count_output = 0;
	link = lemin->links;
	while (link)
	{
		if (link->to == room)
			room->count_input++;
		if (link->from == room)
			room->count_output++;
		link = link->next;
	}
}

void count_all_input_output_links(t_lemin *lemin)
{
	t_room *room;

	room = lemin->rooms;
	while (room)
	{
		count_input_output_links(lemin, room);
		room = room->next;
	}
}
