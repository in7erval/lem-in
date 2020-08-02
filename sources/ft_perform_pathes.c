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

static int		get_number_ants_in_path(t_path *path)
{
	t_ant	*ant;
	int		count;

	ant = path->ants;
	count = 0;
	while (ant)
	{
		count++;
		ant = ant->next;
	}
	return (count);
}

static int		get_max_room_number(t_path *path)
{
	int		num;
	t_ant	*ant;

	ant = path->ants;
	num = 0;
	while (ant)
	{
		if (ant->room_number > num)
			num = ant->room_number;
		ant = ant->next;
	}
	return (num);
}

static void		markup_ants(t_lemin *lemin)
{
	t_list	*bp;
	t_list	*bnp;
	size_t	i;

	null_all_ants(lemin->pathes);
	bp = lemin->pathes;
	push_back_ant(&(((t_path *)(bp->content))->ants), new_ant(1));
	i = 1;
	while (i < lemin->num_ants)
	{
		bnp = bp->next;
		if (bnp == NULL)
			bnp = lemin->pathes;
		if (get_number_ants_in_path(bp->content) + bp->content_size >
			get_number_ants_in_path(bnp->content) + bnp->content_size)
			push_back_ant(&(((t_path *)(bnp->content))->ants),
					new_ant(i + 1));
		else
			push_back_ant(&(((t_path *)(bp->content))->ants),
					new_ant(i + 1));
		bp = bnp;
		i++;
	}
}

static int		perform_and_print(t_list *buf, int *first,
								size_t *count_finish_ants, size_t num_ants)
{
	t_path	*buf_p;
	int		room_number;
	t_ant	*ant;
	t_room	*room;

	buf_p = (t_path *)(buf->content);
	room_number = get_max_room_number(buf_p);
	while (room_number >= 0)
	{
		ant = get_ant_by_room_number(buf_p, room_number);
		room = get_room_by_roomnumber(buf_p, room_number + 1);
		if (!ant)
			break ;
		*first = (*first == 0) ? ft_printf(" ") * 0 : 0;
		ft_printf("L%lu-%s", ant->number, room->name);
		ant->room_number = (room->status == END) ? -1 : ant->room_number + 1;
		if (room->status == END)
			(*count_finish_ants)++;
		if (*count_finish_ants == num_ants)
			return (1);
		room_number--;
	}
	return (0);
}

void			perform_pathes(t_lemin *lemin)
{
	t_list	*buf;
	size_t	count_finish_ants;
	int		first;

	markup_ants(lemin);
	count_finish_ants = 0;
	while (count_finish_ants < lemin->num_ants)
	{
		buf = lemin->pathes;
		first = 1;
		while (buf)
		{
			if (perform_and_print(buf, &first,
					&count_finish_ants, lemin->num_ants) == 1)
				break ;
			buf = buf->next;
		}
		ft_printf("\n");
	}
}
