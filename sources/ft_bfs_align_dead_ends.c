#include "lem-in.h"

void	bfs(t_lemin *lemin, t_queue *queue)
{
	t_link *buf;
	t_queue *q;

	q = poll_elem_queue(&queue);
	if (q == NULL)
		return ;
	if (q->room->status != END)
	{
		buf = lemin->links;
		while (buf)
		{
			if (buf->from == q->room)
			{
				if (buf->to->bfs_level == -1)
				{
					buf->to->bfs_level = q->room->bfs_level + 1;
					add_elem_queue(&queue, buf->to);
				}
			}
			else if (buf->to == q->room)
			{
				if (buf->from->bfs_level == -1)
				{
					buf->from->bfs_level = q->room->bfs_level + 1;
					add_elem_queue(&queue, buf->from);
				}
			}
			buf = buf->next;
		}
		lemin->bfs_level = q->room->bfs_level;
	}
	else
		lemin->end->bfs_level = MAX_INT;
	free(q);
	bfs(lemin, queue);
}

void	delete_useless_links(t_lemin* lemin)
{
	int flag;

	flag = 1;
	while (flag)
		flag = ft_delete_links(lemin, check_one_level);
}

void	delete_all_dead_ends(t_lemin *lemin)
{
	int 	flag;

	flag = 1;
	while (flag)
		flag = ft_delete_links(lemin, check_dead_end);
}

/*
t_rooms	*copy_links(t_rooms *links)
{
	t_rooms *copy;

	copy = NULL;
	while (links)
	{
		add_room_to_rooms_union_back(&copy, links->room);
		links = links->next;
	}
	return copy;
}
*/

void	align_all_links(t_lemin *lemin)
{
	t_link *link;
	t_room *buf_room;

	link = lemin->links;
	while (link)
	{
		if (link->from->bfs_level > link->to->bfs_level)
		{
			buf_room = link->from;
			link->from = link->to;
			link->to = buf_room;
		}
		link = link->next;
	}
}
