#include "lem_in.h"

void	print_room(t_lemin *lemin, t_room *room)
{
	char *status;
	t_link *link;

	if (room == lemin->end)
		status = "END";
	else if (room == lemin->start)
		status = "START";
	else
		status = "COMMON";

	ft_printf("{cyan}{bold}-------- name: {eoc}{green}{black_bg}{underline}{bold}%s{eoc}{cyan}{bold} --------{eoc}\nstatus: {blue}{bold}%s{eoc}\nx: %d y: %d\n", room->name, status, room->x, room->y);
	ft_printf("next: {red}%s{eoc}\t prev: {red}%s{eoc}\n", room->next ? room->next->name : "null", room->prev ? room->prev->name : "null");
	ft_printf("{red}{bold}  UNION{eoc} with: ");
	link = lemin->links;
	while (link)
	{
		if (link->to == room)
			ft_printf("{yellow}%s {eoc}", link->from->name);
		if (link->from == room)
			ft_printf("{yellow}{bold}%s {eoc}", link->to->name);
		link = link->next;
	}
	ft_printf("\n");
	ft_printf("{cyan}{bold}---------------------------{eoc}\n\n");
}

void	print_lemin(t_lemin *lemin, char *str)
{
	t_list	*buf;

	ft_printf("\n%s\n––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n", str);
	buf = lemin->rooms;
	while (buf)
	{
		print_room(lemin, (t_room *)(buf->content));
		buf = buf->next;
	}
}

