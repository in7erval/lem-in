#include "lem_in.h"

void	print_room(t_lemin *lemin, t_room *room)
{
	char *status;
	t_list *link;

	if (room == lemin->end)
		status = "END";
	else if (room == lemin->start)
		status = "START";
	else
		status = "COMMON";

	ft_printf("{cyan}{bold}-------- name: {eoc}{green}{black_bg}{underline}{bold}%s{eoc}{cyan}{bold} --------{eoc}\nstatus: {blue}{bold}%s{eoc}\nx: %d y: %d count_links:%d\n", room->name, status, room->x, room->y, room->count_links);
	ft_printf("{red}{bold}  UNION{eoc} with: ");
	link = room->links;
	while (link)
	{
		ft_printf("{yellow}{bold}%s {eoc}", ((t_room *)link->content)->name);
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

