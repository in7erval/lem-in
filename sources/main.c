/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/02/07 13:43:30 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int argc, char **argv)
{
	t_lemin		*lemin;

	if (check_usage(argc, argv))
		return (1);
	lemin = init_lemin();
	ft_bonus(argc, argv, lemin);
	if (!ft_parse(lemin))
		return (ft_free_error(lemin));
	if (ft_markup_bfs(lemin) == 1)
		return (ft_free_error(lemin));
	ft_beautify_rooms(lemin);
	lemin->pathes = sort_pathes(get_pathes(lemin, lemin->start));
	if (!(lemin->pathes))
		return (ft_free_error(lemin));
	ft_map_show(lemin->map);
	ft_printf("\n");
	if (lemin->p_bonus)
		print_pathes(lemin->pathes);
	perform_pathes(lemin);
	ft_free_lemin(lemin);
	return (0);
}
