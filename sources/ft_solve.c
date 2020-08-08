/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_markup_bfs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:14 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "../libft/includes/libft.h"
#include "../includes/lem_in.h"

int		max_paths(t_lemin *lemin)
{
	int start_links;
	int end_links;

	start_links = lemin->start->count_links;
	end_links = lemin->end->count_links;
	return (ft_min(ft_min(start_links, end_links), lemin->num_ants));
}

t_group	*create_group(t_lemin *lemin)
{
	t_group	*best;
	t_group	*cur;
	int		count;
	t_path	*traverse;

	count = 0;
	best = NULL;
	while (count < lemin->max_paths && (traverse = run_bft(lemin)))
	{
		rebuild_paths(traverse);
		cur = group_build(lemin);
		free_path(traverse);
		if (!best)
			best = cur;
		else if (best->total_rounds > cur->total_rounds)
		{
			free_group(best);
			best = cur;
		}
		else
			free_group(cur);
		count++;
	}
	return (best);
}

int		ft_solve(t_lemin *lemin)
{
	t_group	*group;

	lemin->max_paths = max_paths(lemin);
	group = create_group(lemin);
	if (group == NULL || group->paths == NULL)
		return (0);
	lemin->group = group;
	return (1);
}
