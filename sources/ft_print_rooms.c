#include "lem-in.h"

void	print_lemin(t_lemin *lemin, char *str)
{
	t_room	*buf;
	t_link	*link;
	char	*status;

	ft_printf("\n%s\n––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n", str);
	buf = lemin->rooms;
	while (buf)
	{
		if (buf == lemin->end)
			status = "END";
		else if (buf == lemin->start)
			status = "START";
		else
			status = "COMMON";

		ft_printf("{cyan}{bold}-------- name: {eoc}{green}{black_bg}{underline}{bold}%s{eoc}{cyan}{bold} --------{eoc}\nstatus: {blue}{bold}%s{eoc}\nx: %d y: %d level: %d\n{red}{bold}  UNION{eoc} with: ", buf->name, status, buf->x, buf->y, buf->bfs_level);
		link = lemin->links;
		while (link)
		{
			if (link->to == buf)
				ft_printf("{yellow}%s {eoc}", link->from->name);
			if (link->from == buf)
				ft_printf("{yellow}{bold}%s {eoc}", link->to->name);
			link = link->next;
		}
		ft_printf("\n");
		ft_printf("input_links: {red}%d{eoc} | output_links: {red}%d{eoc}\n", buf->count_input, buf->count_output);
		ft_printf("{cyan}{bold}---------------------------{eoc}\n\n");
		buf = buf->next;
	}
}
