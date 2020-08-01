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

#include "lem-in.h"

static t_list	*get_min_len_path_list(t_list *pathes)
{
	size_t	min_len;
	t_list	*buf;
	t_list	*min_path;

	if (pathes == NULL)
		return (0);
	min_len = pathes->content_size;
	min_path = pathes;
	buf = pathes->next;
	while (buf)
	{
		if (buf->content_size < min_len)
		{
			min_len = buf->content_size;
			min_path = buf;
		}
		buf = buf->next;
	}
	return (min_path);
}

static int		ft_equals_list(t_list *list1, t_list *list2)
{
	if (list1 == list2)
		return (1);
	return (0);
}

static void		ft_del_lst_elem(t_list **list, t_list *list1,
						int (*f)(t_list *list1, t_list *list2))
{
	t_list *buf;
	t_list *prev;

	prev = NULL;
	buf = *list;
	while (buf && f(list1, buf) != 1)
	{
		prev = buf;
		buf = buf->next;
	}
	if (buf)
	{
		if (prev == NULL)
			*list = (*list)->next;
		else
			prev->next = buf->next;
		free(buf);
	}
}

t_list			*sort_pathes(t_list *pathes)
{
	t_list *sorted_path;
	t_list *min_len;

	sorted_path = NULL;
	while (pathes != NULL)
	{
		min_len = get_min_len_path_list(pathes);
		ft_lstadd_back(&sorted_path, ft_lstnew(min_len->content,
				min_len->content_size));
		ft_del_lst_elem(&pathes, min_len, ft_equals_list);
	}
	return (sorted_path);
}
