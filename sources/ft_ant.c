/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ant.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:02 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
t_ant	*new_ant(size_t number)
{
	t_ant	*ant;

	ant = (t_ant *)malloc(sizeof(t_ant));
	if (ant)
	{
		ant->number = number;
		ant->next = NULL;
		ant->room_number = 0;
	}
	return (ant);
}

void	push_back_ant(t_ant **ants, t_ant *ant)
{
	t_ant *buf;

	if (*ants == NULL)
		*ants = ant;
	else
	{
		buf = *ants;
		while (buf->next)
			buf = buf->next;
		buf->next = ant;
	}
}

t_ant	*get_ant_by_room_number(t_path *path, int number)
{
	t_ant *ants;

	ants = path->ants;
	while (ants)
	{
		if (ants->room_number == number)
			return (ants);
		ants = ants->next;
	}
	return (NULL);
}

void	null_all_ants(t_list *list)
{
	t_path *p;

	while (list)
	{
		p = (t_path *)(list->content);
		p->ants = NULL;
		list = list->next;
	}
}

void	free_ants(t_ant **ants)
{
	t_ant *buf;
	t_ant *kill;

	if (ants && *ants)
	{
		buf = *ants;
		while (buf)
		{
			kill = buf;
			buf = buf->next;
			free(kill);
		}
		*ants = NULL;
	}
}
*/