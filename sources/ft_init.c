#include "lem-in.h"

t_lemin *init_lemin(void)
{
	t_lemin *lemin;

	if (!(lemin = (t_lemin *)malloc(sizeof(t_lemin))))
		error_exit(MALLOC_ERROR);
	lemin->rooms = NULL;
	lemin->links = NULL;
	lemin->start = NULL;
	lemin->end = NULL;
	lemin->num_ants = 0;
	lemin->map = NULL;
	lemin->bfs_level = 0;
	lemin->pathes = NULL;
	return (lemin);
}

