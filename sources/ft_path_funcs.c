#include "lem-in.h"

t_list	*get_pathes(t_room *room)
{
	t_list *pathes;
	t_rooms *buf;
	t_path *path;

	pathes = NULL;
	buf = room->aligned_union_room;
	while (buf)
	{
		path = get_path_to_end(buf->room);
		if (path != NULL)
		{
			add_elem_path_start(&path, room);
			ft_lstadd_back(&pathes, ft_lstnew(path, get_length_path(path)));
		}
		buf = buf->next;
	}
	return (pathes);
}

void 	free_pathes(t_list **pathes)
{
	t_list *buf;

	buf = *pathes;
	while (buf)
	{
		free_path((t_path **)&(buf->content));
		buf = buf->next;
	}
	free_list(pathes);
}

t_path *get_min_len_path(t_list *pathes)
{
	size_t	min_len;
	t_list	*buf;
	t_path	*min_path;

	if (pathes == NULL)
		return (0);
	min_len = pathes->content_size;
	min_path = pathes->content;
	buf = pathes->next;
	while (buf)
	{
		if (buf->content_size < min_len)
		{
			min_len = buf->content_size;
			min_path = buf->content;
		}
		buf = buf->next;
	}
	return (min_path);
}

size_t 	get_expr_pathes(t_list *pathes, t_list *path)
{
	t_list *buf;
	size_t sum;

	sum = 0;
	buf = pathes;
	while (buf)
	{
		if (buf != path && buf->content_size < path->content_size)
			sum += path->content_size - buf->content_size;
		buf = buf->next;
	}
	return (sum);
}

t_list *get_min_len_path_list(t_list *pathes)
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

t_list	*get_next_length_path(t_list *pathes, t_list *cur_path)
{
	t_list *buf;
	int		min_len;
	t_list	*path;

	buf = pathes;
	min_len = 0;
	path = NULL;
	while (buf)
	{
		if (buf->content_size > cur_path->content_size)
		{
			min_len = buf->content_size;
			path = buf;
			break;
		}
		buf = buf->next;
	}
	buf = pathes;
	while (buf)
	{
		if (buf->content_size > cur_path->content_size && (int)buf->content_size <= min_len)
		{
			min_len = buf->content_size;
			path = buf;
		}
		buf = buf->next;
	}
	return (path);
}

int 	ft_equals_list(t_list *list1, t_list *list2)
{
	if (list1 == list2)
		return (1);
	return(0);
}

void	ft_del_lst_elem(t_list **list, t_list *list1, int (*f)(t_list *list1, t_list *list2))
{
	t_list *buf;
	t_list *kill;
	t_list *prev;

	prev = NULL;
	buf = *list;
	while (buf)
	{
		if (f(list1, buf) == 1)
		{
			kill = buf;
			if (prev == NULL)
				*list = (*list)->next;
			else
			{
				prev->next = buf->next;
				if (buf->next != NULL)
					buf->next->prev = prev;
			}
			buf = buf->next;
			free(kill);
		}
		else
		{
			prev = buf;
			buf = buf->next;
		}
	}
}

t_list 	*sort_pathes(t_list *pathes)
{
	t_list *sorted_path;
	t_list *min_len;

	sorted_path = NULL;
	while (pathes != NULL)
	{
		min_len = get_min_len_path_list(pathes);
		ft_lstadd_back(&sorted_path, ft_lstnew(min_len->content, min_len->content_size));
		ft_del_lst_elem(&pathes, min_len, ft_equals_list);
	}
	return (sorted_path);
}


int 	get_number_ants_in_path(t_path *path)
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


t_room *get_room_by_roomnumber(t_path *path, int room_number)
{
	int i;

	i = 0;
	while (i < room_number)
	{
		i++;
		if (path == NULL)
			return (NULL);
		path = path->next;
	}
	return (path->room);
}

int		get_max_room_number(t_path *path)
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

void	markup_ants(t_list *pathes, int num_ants)
{
	t_list	*buf_path;
	t_list 	*buf_next_path;
	int 	i;

	null_all_ants(pathes);
	buf_path = pathes;
	push_back_ant(&(((t_path *)(buf_path->content))->ants), new_ant(1));
	i = 1;
	while (i < num_ants)
	{
		buf_next_path = buf_path->next;
		if (buf_next_path == NULL)
			buf_next_path = pathes;
		if (get_number_ants_in_path(buf_path->content) + buf_path->content_size >
			get_number_ants_in_path(buf_next_path->content) + buf_next_path->content_size)
			push_back_ant(&(((t_path *)(buf_next_path->content))->ants), new_ant(i + 1));
		else
			push_back_ant(&(((t_path *)(buf_path->content))->ants), new_ant(i + 1));
		buf_path = buf_next_path;
		i++;
	}
}

int		perform_and_print(t_list *buf, int *first, int *count_finish_ants, int num_ants)
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

void	print_ants(t_list *pathes)
{
	t_path *buf;
	t_ant	*ant;

	while (pathes)
	{

		buf = (t_path *)pathes->content;
		ft_printf("{red}%s {eoc}", buf->next->room->name);
		ant = buf->ants;
		while (ant)
		{
			ft_printf("{bold}{yellow}%d {eoc}", ant->number);
			ant = ant->next;
		}
		ft_printf("\n");
		pathes = pathes->next;
	}
}

void	perform_pathes(t_list *pathes, int num_ants) //todo: free ants!!!!!
{
	t_list	*buf;
	int 	count_finish_ants;
	int 	first;

	markup_ants(pathes, num_ants);
	//print_ants(pathes);
	count_finish_ants = 0;
	buf = pathes;
	while (count_finish_ants < num_ants)
	{
		buf = pathes;
		first = 1;
		while (buf)
		{
			if (perform_and_print(buf, &first, &count_finish_ants, num_ants) == 1)
				break;
			buf = buf->next;
		}
		ft_printf("\n");
	}
}
