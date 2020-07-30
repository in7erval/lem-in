#include "lem-in.h"

static int 	get_number_ants_in_path(t_path *path)
{
	t_ant	*ant;
	int count;

	ant = path->ants;
	count = 0;
	while (ant)
	{
		count++;
		ant = ant->next;
	}
	return (count);
}

static int		get_max_room_number(t_path *path)
{
	int		num;
	t_ant	*ant;

	ant = path->ants;
	num = 0;
	while (ant)
	{
		if (ant->room_number > num)
			num = ant->room_number;
		ant = ant->next;
	}
	return (num);
}

static void	markup_ants(t_lemin *lemin)
{
	t_list	*buf_path;
	t_list 	*buf_next_path;
	int 	i;

	null_all_ants(lemin->pathes);
	buf_path = lemin->pathes;
	push_back_ant(&(((t_path *)(buf_path->content))->ants), new_ant(1));
	i = 1;
	while (i < lemin->num_ants)
	{
		buf_next_path = buf_path->next;
		if (buf_next_path == NULL)
			buf_next_path = lemin->pathes;
		if (get_number_ants_in_path(buf_path->content) + buf_path->content_size >
			get_number_ants_in_path(buf_next_path->content) + buf_next_path->content_size)
			push_back_ant(&(((t_path *)(buf_next_path->content))->ants), new_ant(i + 1));
		else
			push_back_ant(&(((t_path *)(buf_path->content))->ants), new_ant(i + 1));
		buf_path = buf_next_path;
		i++;
	}
}

static int		perform_and_print(t_list *buf, int *first, int *count_finish_ants, int num_ants)
{
	t_path *buf_p;
	int room_number;
	t_ant *ant;
	t_room *room;

	buf_p = (t_path *)(buf->content);
	room_number = get_max_room_number(buf_p);
	while (room_number >= 0)
	{
		ant = get_ant_by_room_number(buf_p, room_number);
		room = get_room_by_roomnumber(buf_p, room_number + 1);
		if (!ant)
			break;
		if (*first == 0)
			ft_printf(" ");
		else
			*first = 0;
		ft_printf("L%d-%s", ant->number, room->name);
		ant->room_number = (room->status == END) ? -1 : ant->room_number + 1;
		if (room->status == END)
			(*count_finish_ants)++;
		if (*count_finish_ants == num_ants)
			return (1);
		room_number--;
	}
	return (0);
}

void	perform_pathes(t_lemin *lemin) //todo: free ants!!!!!
{
	t_list	*buf;
	int 	count_finish_ants;
	int 	first;

	markup_ants(lemin);
	count_finish_ants = 0;
	buf = lemin->pathes;
	while (count_finish_ants < lemin->num_ants)
	{
		buf = lemin->pathes;
		first = 1;
		while (buf)
		{
			if (perform_and_print(buf, &first, &count_finish_ants, lemin->num_ants) == 1)
				break;
			buf = buf->next;
		}
		ft_printf("\n");
	}
}