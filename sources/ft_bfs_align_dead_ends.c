#include "lem-in.h"

void	bfs(t_room *rooms, t_queue *queue)
{
	t_rooms *buf;
	t_queue *q;

	q = poll_elem_queue(&queue);
	if (q == NULL)
		return ;
	q->room->bfs_status = PAINTED;
	if (q->room->status != END)
	{
		buf = q->room->union_room;
		while (buf)
		{
			if (buf->room->bfs_status == NOT_USED)
			{
				buf->room->bfs_status = POINTED;
				buf->room->bfs_level = q->room->bfs_level + 1;
				add_elem_queue(&queue, buf->room);
			}
			buf = buf->next;
		}
	}
	else
		q->room->bfs_level = MAX_INT;
	free(q);
	bfs(rooms, queue);
}

void	delete_useless_links(t_room* rooms)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		ft_delete_elem(&(buf->union_room), buf, check_one_level);
		buf = buf->next;
	}
}

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

void	align_all_links(t_room *rooms)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		buf->aligned_union_room = copy_links(buf->union_room);
		buf = buf->next;
	}
	buf = rooms;
	while (buf)
	{
		ft_delete_elem(&(buf->aligned_union_room), buf, check_less_level);
		buf = buf->next;
	}
}

int		delete_all_dead_ends(t_room *rooms)
{
	t_room *buf;
	int 	flag;

	flag = 0;
	buf = rooms;
	while (buf)
	{
		if  (ft_delete_elem(&(buf->union_room), buf, check_dead_end) == 1)
			flag = 1;
		if  (ft_delete_elem(&(buf->aligned_union_room), buf, check_dead_end) == 1)
			flag = 1;
		buf = buf->next;
	}
	return (flag);
}


