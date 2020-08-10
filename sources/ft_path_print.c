/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/10 15:23:33 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_path(t_path *path)
{
	t_room	*buf;
	t_list	*rooms;
	int		flag;

	flag = 0;
	if (((t_room *)(path->rooms->content))->status == END)
		flag = 1;
	if (flag)
		ft_lstrev(&(path->rooms));
	rooms = path->rooms;
	while (rooms->next)
	{
		buf = (t_room *)(rooms->content);
		ft_printf("{yellow}%s{magenta}->{eoc}", buf->name);
		rooms = rooms->next;
	}
	buf = (t_room *)(rooms->content);
	ft_printf("{yellow}%s{eoc}", buf->name);
	ft_printf("\n");
	if (flag)
		ft_lstrev(&(path->rooms));
}
