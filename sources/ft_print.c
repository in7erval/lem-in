/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:23:51 by htrent            #+#    #+#             */
/*   Updated: 2020/08/10 15:23:52 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_round(t_round *round)
{
	t_list	*cur;
	t_move	*move;

	cur = round->moves;
	while (cur->next)
		cur = cur->next;
	while (cur)
	{
		move = (t_move *)cur->content;
		ft_printf("L%d-%s", move->ant_number, move->dest->name);
		cur = cur->prev;
		if (cur != NULL)
			ft_putchar(' ');
	}
	ft_printf("\n");
}

void			print_answer(t_lemin *lemin)
{
	t_list		*cur;

	cur = lemin->answer->rounds;
	while (cur->next)
		cur = cur->next;
	while (cur)
	{
		print_round((t_round *)cur->content);
		cur = cur->prev;
	}
}
