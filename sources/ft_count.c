#include "lem-in.h"

int 	count_elems_list(t_rooms *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return i;
}

void	count_input_links(t_room *room)
{
	t_rooms	*all_links;
	t_rooms	*output_links;

	all_links = room->union_room;
	output_links = room->aligned_union_room;
	room->count_input = 0;
	while (all_links)
	{
		if (list_contains(output_links, all_links) == 0)
			room->count_input++;
		all_links = all_links->next;
	}
}

void count_all_input_output_links(t_room *rooms)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		count_input_links(buf);
		buf->count_output = count_elems_list(buf->aligned_union_room);
		buf = buf->next;
	}
}


