/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:11 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lemin		*init_lemin(void)
{
	t_lemin *lemin;

	if (!(lemin = (t_lemin *)malloc(sizeof(t_lemin))))
		error_exit(MALLOC_ERROR);
	lemin->rooms = NULL;
	lemin->start = NULL;
	lemin->end = NULL;
	lemin->num_ants = 0;
	lemin->map = NULL;
	lemin->c_bonus = 0;
	lemin->p_bonus = 0;
	lemin->max_paths = 0;
	lemin->group = NULL;
	return (lemin);
}
