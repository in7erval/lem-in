#include "lem_in.h"

static int	rounds_for_route(t_group *group, int index)
{
	int	ants;

	ants = group->ants[index] + 1;
	return (group->paths[index]->len + ants - 1);
}

static void	distribute_one(t_group *group)
{
	int	i;
	int rounds1;
	int rounds2;

	i = 0;
	while (i < group->path_count - 1)
	{
		rounds1 = rounds_for_route(group, i);
		rounds2 = rounds_for_route(group, i + 1);
		if (rounds1 < rounds2)
			break ;
		i++;
	}
	group->ants[i]++;
}

void		perform_ants(t_group *group, int total_ants)
{
	int	left_ants;

	left_ants = total_ants;
	while (left_ants > 0)
	{
		distribute_one(group);
		left_ants--;
	}
}

