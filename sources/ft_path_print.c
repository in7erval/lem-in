/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:19 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_path(t_path *path)
{
	t_room	*buf;
	t_list	*rooms;

	if (((t_room *)(path->rooms->content))->status == END)
		ft_lstrev(&(path->rooms));
	rooms = path->rooms;
	while (rooms->next)
	{
		buf = (t_room *)(rooms->content);
		ft_printf("{yellow}%s->", buf->name);
		rooms = rooms->next;
	}
	buf = (t_room *)(rooms->content);
	ft_printf("%s{eoc}", buf->name);
	ft_printf("\n");
}
