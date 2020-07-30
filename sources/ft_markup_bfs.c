#include "lem-in.h"

int	ft_markup_bfs(t_lemin *lemin)
{
	t_queue *queue;

	queue = NULL;
	add_elem_queue(&queue, lemin->start);
	lemin->start->bfs_level = 0;
	bfs(lemin, queue);
	if (lemin->end->status == -1)
		return (1);
	return (0);
}

