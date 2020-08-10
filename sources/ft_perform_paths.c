/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perform_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:23:42 by htrent            #+#    #+#             */
/*   Updated: 2020/08/10 15:23:43 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				ant_can_move(t_room *room)
{
	if ((room->ants == 0 && room->status == COMMON)
		|| room->status == END)
		return (1);
	return (0);
}

void			try_move_ant(t_lemin *lemin, t_room *room_from,
							t_room *room_to, int *ants)
{
	while (room_from->ants > 0 && ant_can_move(room_to))
	{
		if (room_from->status == START)
		{
			if (*ants <= 0)
				return ;
			(*ants)--;
			room_from->ant_number++;
		}
		room_from->ants--;
		room_to->ants++;
		room_to->ant_number = room_from->ant_number;
		ft_answer_add_move(lemin->answer, room_to);
	}
}

void			do_path(t_lemin *lemin, t_path *path, int *ants)
{
	t_list	*cur;
	t_room	*room1;
	t_room	*room2;

	cur = path->rooms;
	while (((t_room *)(cur->content)) != lemin->start)
	{
		room1 = ((t_room *)(cur->content));
		room2 = ((t_room *)(cur->next->content));
		try_move_ant(lemin, room2, room1, ants);
		cur = cur->next;
	}
}

void			do_round(t_lemin *lemin)
{
	int i;

	i = 0;
	ft_answer_add_round(lemin->answer);
	while (i < lemin->group->path_count)
	{
		lemin->answer->path = i;
		do_path(lemin, lemin->group->paths[i], &(lemin->group->ants[i]));
		i++;
	}
}

void			perform_paths(t_lemin *lemin)
{
	lemin->answer = ft_init_answer();
	lemin->start->ants = lemin->num_ants;
	while (lemin->start->ants >= 0 && lemin->end->ants != lemin->num_ants)
		do_round(lemin);
	print_answer(lemin);
}
