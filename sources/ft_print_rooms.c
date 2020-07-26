#include "lem-in.h"

void	print_list(t_room *list)
{
	t_room *buf;
	t_rooms *u;

	buf = list;
	while (buf)
	{
		ft_printf("{cyan}{bold}-------- name: {eoc}{green}{black_bg}{underline}{bold}%s{eoc}{cyan}{bold} --------{eoc}\nstatus: %d\nx: %d y: %d level: %d\n{red}{bold}  UNION{eoc} with: {yellow}", buf->name, buf->status, buf->x, buf->y, buf->bfs_level);
		u = buf->union_room;
		while (u)
		{
			ft_printf("%s ", u->room->name);
			u = u->next;
		}
		ft_printf("{eoc}\n");
		ft_printf("{white}{bold}ALIGNED{eoc} with: {magenta}");
		u = buf->aligned_union_room;
		while (u)
		{
			ft_printf("%s ", u->room->name);
			u = u->next;
		}
		ft_printf("{eoc}\n");
		ft_printf("input_links: {red}%d{eoc} | output_links: {red}%d{eoc}\n", buf->count_input, buf->count_output);
		ft_printf("{cyan}{bold}---------------------------{eoc}\n\n");
		buf = buf->next;
	}
}
