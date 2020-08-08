/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:26 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int argc, char **argv)
{
	t_lemin		*lemin;
	t_options	options;

	if (check_usage(argc, argv, &options))
		return (1);
	lemin = init_lemin(options);
	if (!ft_parse(lemin))
		return (ft_free_error(lemin));
	ft_optimize(lemin);
	if (!ft_solve(lemin))
		return (ft_free_error(lemin));
	ft_map_show(lemin->map);
	ft_printf("\n");
	perform_paths(lemin);
	if (lemin->options.r_bonus)
		print_lemin(lemin, "(After deleting dead ends)");
	if (lemin->options.p_bonus)
		print_group(lemin->group);
	ft_free_lemin(lemin);
	return (0);
}
