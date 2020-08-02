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

void	print_path(t_path *path)
{
	t_path *buf;

	buf = path;
	while (buf->next)
	{
		ft_printf("{yellow}%s->", buf->room->name);
		buf = buf->next;
	}
	ft_printf("%s{eoc}", buf->room->name);
	ft_printf("\n");
}

void	print_pathes(t_list *pathes)
{
	t_list	*path;
	int		num;

	path = pathes;
	num = 1;
	while (path)
	{
		if (path->content != NULL)
		{
			ft_printf("Path{green}%02d{eoc}\t"
	"length: {blue}{white_bg}%3d{eoc} {black_bg}|||{eoc}\t",
	num, path->content_size);
			print_path(path->content);
			num++;
		}
		path = path->next;
	}
}
