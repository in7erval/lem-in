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

int		ft_markup_bfs(t_lemin *lemin)
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

void	ft_beautify_rooms(t_lemin *lemin)
{
	delete_useless_links(lemin);
	align_all_links(lemin);
	count_all_input_output_links(lemin);
	delete_all_dead_ends(lemin);
	delete_all_input_forks(lemin);
	delete_all_output_forks(lemin);
}

void	ft_bonus(int argc, char **argv, t_lemin *lemin)
{
	if (argc == 2 && !ft_strcmp(argv[1], "-c"))
		lemin->c_bonus = 1;
	else if (argc == 2 && !ft_strcmp(argv[1], "-p"))
		lemin->p_bonus = 1;
	else if ((argc == 2 && (!ft_strcmp(argv[1], "-cp") ||
			!ft_strcmp(argv[1], "-pc"))) || (argc == 3 &&
			((!ft_strcmp(argv[1], "-c") && !ft_strcmp(argv[2], "-p")) ||
			(!ft_strcmp(argv[1], "-p") && !ft_strcmp(argv[2], "-c")))))
	{
		lemin->c_bonus = 1;
		lemin->p_bonus = 1;
	}
}

int		check_usage(int argc, char **argv)
{
	if (argc > 3 || (argc == 2 && (ft_strcmp(argv[1], "-c") &&
		ft_strcmp(argv[1], "-p") && ft_strcmp(argv[1], "-pc") &&
		ft_strcmp(argv[1], "-cp"))) || (argc == 3 &&
		!((!ft_strcmp(argv[1], "-c") || !ft_strcmp(argv[2], "-p"))
		|| (!ft_strcmp(argv[1], "-p") && !ft_strcmp(argv[2], "-c")))))
	{
		ft_printf("{white}{bold}Usage:{eoc} ./lemin [-{red}c{eoc}{yellow}"
			"p{eoc}] < file_with_map\n{white}{bold}Options:{eoc}\n\t{red}-c\t"
	"Print cleaned map{eoc}\n\t{yellow}-p\tPrint paths{eoc}\n");
		return (1);
	}
	return (0);
}
