/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:13 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_map_clean(t_map **head)
{
	t_map	*current;

	if (head && *head)
	{
		while (*head)
		{
			current = *head;
			*head = current->next;
			free(current->str);
			free(current);
		}
	}
}

void			ft_map_show(t_map *head)
{
	t_map	*current;

	current = head;
	while (current->next)
		current = current->next;
	while (current)
	{
		ft_printf("%s\n", current->str);
		current = current->prev;
	}
}

static t_map	*ft_map_create(char *str)
{
	t_map	*current;

	current = malloc(sizeof(t_map));
	if (current)
	{
		current->str = str;
		current->next = NULL;
		current->prev = NULL;
	}
	return (current);
}

void			ft_map_add(t_map **head, char *str)
{
	t_map	*new;

	new = ft_map_create(str);
	if (!(*head))
		*head = new;
	else
	{
		new->next = (*head);
		(*head)->prev = new;
		*head = new;
	}
}
