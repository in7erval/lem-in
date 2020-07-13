#include "lem-in.h"




t_room	*new_room(char *name, int x, int y)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	room->x = x;
	room->y = y;
	room->name = name;
	room->next = NULL;
	room->prev = NULL;
	room->union_room = NULL;
	room->bfs_level = -1;
	room->status = COMMON;
	room->bfs_status = NOT_USED;
	room->aligned_union_room = NULL;
	room->count_input = 0;
	room->count_output = 0;
	return room;
}

void	push_back_room(t_room **head, t_room *room)
{
	t_room *buf;

	buf = *head;
	if (*head == NULL)
	{
		*head = room;
		return ;
	}
	while (buf->next)
		buf = buf->next;
	buf->next = room;
	room->prev = buf;
}

void	free_rooms_list(t_rooms **list)
{
	t_rooms *kill;
	t_rooms *buf;

	buf = *list;
	while (buf)
	{
		kill = buf;
		buf = buf->next;
		free(kill);
	}
	*list = NULL;
}

void	free_list(t_list **list)
{
	t_list *kill;
	t_list *buf;

	buf = *list;
	while (buf)
	{
		kill = buf;
		buf = buf->next;
		free(kill);
	}
	*list = NULL;
}

void	free_rooms(t_room **rooms)
{
	t_room *kill;
	t_room *buf;

	buf = *rooms;
	while (buf)
	{
		kill = buf;
		free_rooms_list(&(kill->union_room));
		free_rooms_list(&(kill->aligned_union_room));
		buf = buf->next;
		free(kill);
	}
	*rooms = NULL;
}

void	print_list(t_room *list)
{
	t_room *buf;
	t_rooms *u;

	buf = list;
	while (buf)
	{
		ft_printf("{cyan}------ name: {green}%s{cyan} ------{eoc}\nx: %d y: %d level: %d\n{yellow_bg}{red}{bold}  UNION{eoc} with: {yellow}", buf->name, buf->x, buf->y, buf->bfs_level);
		u = buf->union_room;
		while (u)
		{
			ft_printf("%s ", u->room->name);
			u = u->next;
		}
		ft_printf("{eoc}\n");
		ft_printf("{magenta_bg}{white}{bold}ALIGNED{eoc} with: {magenta}");
		u = buf->aligned_union_room;
		while (u)
		{
			ft_printf("%s ", u->room->name);
			u = u->next;
		}
		ft_printf("{eoc}\n");
		ft_printf("input_links: {red}%d{eoc} | output_links: {red}%d{eoc}\n", buf->count_input, buf->count_output);
		buf = buf->next;
	}
}

t_rooms *new_element_rooms(t_room *room)
{
	t_rooms *elem;

	elem = (t_rooms *)malloc(sizeof(t_rooms));
	elem->room = room;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void	add_room_to_rooms_union(t_rooms **union_rooms, t_room *room)
{
	t_rooms *new;

	new = new_element_rooms(room);
	if (!(*union_rooms))
		(*union_rooms) = new;
	else
	{
		new->next = (*union_rooms);
		(*union_rooms)->prev = new;
		*union_rooms = new;
	}
}

void	add_room_to_rooms_union_back(t_rooms **rooms_union, t_room *room)
{
	t_rooms	*tmp;
	t_rooms *new;

	new = new_element_rooms(room);
	tmp = *rooms_union;
	if (tmp == NULL)
		*rooms_union = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
}


t_room *find_room_by_name(t_room *rooms, char *name)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		if (ft_strcmp(buf->name, name) == 0)
			return buf;
		buf = buf->next;
	}
	return NULL;
}


int 	is_in_union(t_room *room, t_room *check_room)
{
	t_rooms *head;

	head = room->union_room;
	while (head)
	{
		if (head->room == check_room)
			return (1);
		head = head->next;
	}
	return (0);
}

void	add_union(t_room *rooms, char *room1_name, char *room2_name)
{
	t_room *room1;
	t_room *room2;

	room1 = find_room_by_name(rooms, room1_name);
	room2 = find_room_by_name(rooms, room2_name);
	if (room1 == NULL || room2 == NULL) // todo: error_management if room doesn't exist
		return ;
	if (!is_in_union(room1, room2))
		add_room_to_rooms_union(&(room1->union_room), room2);
	if (!is_in_union(room2, room1))
		add_room_to_rooms_union(&(room2->union_room), room1);
}

t_room *find_start_room(t_room *rooms)
{
	t_room *room;

	room = rooms;
	while (room)
	{
		if (room->status == START)
			return (room);
		room = room->next;
	}
	return (NULL);
}

void	bfs(t_room *rooms, t_queue *queue)
{
	t_rooms *buf;
	t_queue *q;

	q = poll_elem_queue(&queue);
	if (q == NULL)
		return ;
	q->room->bfs_status = PAINTED;
	if (q->room->status != END)
	{
		buf = q->room->union_room;
		while (buf)
		{
			if (buf->room->bfs_status == NOT_USED)
			{
				buf->room->bfs_status = POINTED;
				buf->room->bfs_level = q->room->bfs_level + 1;
				add_elem_queue(&queue, buf->room);
			}
			buf = buf->next;
		}
	}
	else
		q->room->bfs_level = MAX_INT;
	free(q);
	bfs(rooms, queue);
}

int 	check_one_level(t_room *room, t_rooms *buf)
{
	t_room *r;

	r = buf->room;
	if (r->bfs_level == room->bfs_level || r->bfs_level == -1 || room->bfs_level == -1)
		return (1);
	return (0);
}

int 	check_less_level(t_room *room, t_rooms *buf)
{
	t_room *r;

	r = buf->room;
	if (r->bfs_level < room->bfs_level)
		return (1);
	return (0);
}

int 	check_dead_end(t_room *room, t_rooms *buf)
{
	t_room *r;

	r = buf->room;
	if (r->count_output == 0 && r->status != END && r->status != START)
	{
		//ft_printf("{cyan}DEAD_END IN {red}%s {cyan}FROM {red}%s{eoc}\n", r->name, room->name);
		return (1);
	}
	if (room->count_output <= 0 && room->status != END && room->status != START)
	{
		//ft_printf("{cyan}DEAD_END IN {red}%s {cyan}FROM {red}%s{eoc}\n", room->name, r->name);
		return (1);
	}
	return (0);
}

int	ft_delete_elem(t_rooms **list, t_room *r, int (*f)(t_room *room, t_rooms *buf))
{
	t_rooms *buf;
	t_rooms *kill;
	t_rooms *prev;
	int 	flag;

	flag = 0;
	prev = NULL;
	buf = *list;
	while (buf)
	{
		if (f(r, buf) == 1)
		{
			flag = 1;
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
	return (flag);
}

void	delete_useless_links(t_room* rooms)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		ft_delete_elem(&(buf->union_room), buf, check_one_level);
		buf = buf->next;
	}
}

t_rooms	*copy_links(t_rooms *links)
{
	t_rooms *copy;

	copy = NULL;
	while (links)
	{
		add_room_to_rooms_union_back(&copy, links->room);
		links = links->next;
	}
	return copy;
}

void	align_all_links(t_room *rooms)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		buf->aligned_union_room = copy_links(buf->union_room);
		buf = buf->next;
	}
	buf = rooms;
	while (buf)
	{
		ft_delete_elem(&(buf->aligned_union_room), buf, check_less_level);
		buf = buf->next;
	}
}

int 	list_contains(t_rooms *head, t_rooms *elem)
{
	while (head)
	{
		if (head->room == elem->room)
			return (1);
		head = head->next;
	}
	return (0);
}

int 	count_elems_list(t_rooms *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return i;
}

void	count_input_links(t_room *room)
{
	t_rooms	*all_links;
	t_rooms	*output_links;

	all_links = room->union_room;
	output_links = room->aligned_union_room;
	room->count_input = 0;
	while (all_links)
	{
		if (list_contains(output_links, all_links) == 0)
			room->count_input++;
		all_links = all_links->next;
	}
}

void count_all_input_output_links(t_room *rooms)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		count_input_links(buf);
		buf->count_output = count_elems_list(buf->aligned_union_room);
		buf = buf->next;
	}
}

int		delete_all_dead_ends(t_room *rooms)
{
	t_room *buf;
	int 	flag;

	flag = 0;
	buf = rooms;
	while (buf)
	{
		if  (ft_delete_elem(&(buf->union_room), buf, check_dead_end) == 1)
			flag = 1;
		if  (ft_delete_elem(&(buf->aligned_union_room), buf, check_dead_end) == 1)
			flag = 1;
		buf = buf->next;
	}
	return (flag);
}

t_rooms *get_input_links(t_room *room)
{
	t_rooms *all_links;
	t_rooms *output_links;
	t_rooms *input_links;

	input_links = NULL;
	all_links = room->union_room;
	output_links = room->aligned_union_room;
	while (all_links)
	{
		if (list_contains(output_links, all_links) == 0)
			add_room_to_rooms_union_back(&input_links, all_links->room);
		all_links = all_links->next;
	}
	return input_links;
}

int 	check_output_fork(t_rooms *buf)
{
	t_room *room;
	t_rooms *input_links;
	t_rooms *link;

	room = buf->room;
	if (room->status == START)
		return (0);
	if (room->count_output > 1)
		return (1);
	input_links = get_input_links(room);
	link = input_links;
	while (link)
	{
		if (check_output_fork(link))
		{
			free_rooms_list(&input_links);
			return (1);
		}
		link = link->next;
	}
	free_rooms_list(&input_links);
	return (0);
}

int 	input_fork_delete(t_room *to_room, t_rooms *buf)
{
	if (buf->room == to_room)
		return (1);
	return (0);
}


void	delete_input_forks(t_room *room)
{
	t_rooms *input_links;
	t_rooms *buf;
	t_room *from_room;

	input_links = get_input_links(room);
	buf = input_links;
	while (buf)
	{
		if (room->count_input > 1 && check_output_fork(buf))
		{
			from_room = buf->room;
			ft_delete_elem(&(from_room->aligned_union_room), room, input_fork_delete);
			ft_delete_elem(&(from_room->union_room), room, input_fork_delete);
			ft_delete_elem(&(room->union_room), from_room, input_fork_delete);
			room->count_input--;
		}
		buf = buf->next;
	}
	if (room->count_input > 1) //если все ребра "хорошие", то оставляем только одно
	{
		buf = input_links;
		while (buf)
		{
			if (room->count_input > 1)
			{
				from_room = buf->room;
				ft_delete_elem(&(from_room->aligned_union_room), room, input_fork_delete);
				ft_delete_elem(&(from_room->union_room), room, input_fork_delete);
				ft_delete_elem(&(room->union_room), from_room, input_fork_delete);
				room->count_input--;
			}
			buf = buf->next;
		}
	}
	free_rooms_list(&input_links);
}

t_list	*get_names(t_room *rooms)
{
	t_list *names;
	t_room *buf;

	names = NULL;
	buf = rooms;
	while (buf)
	{
		ft_lstadd_back(&names, ft_lstnew(buf->name, 0));
		buf = buf->next;
	}
	return (names);
}

t_room *get_same_level(t_room *rooms, t_list **names, int level)
{
	t_list *buf;
	t_list *prev;
	t_list *kill;
	t_room *room;

	buf = *names;
	prev = NULL;
	while (buf)
	{
		room = find_room_by_name(rooms, buf->content);
		if (room->bfs_level == level)
		{
			kill = buf;
			if (prev == NULL)
				*names = (*names)->next;
			else
				prev->next = buf->next;
			free(kill);
			return (room);
		}
		else
		{
			prev =  buf;
			buf = buf->next;
		}
	}
	return (NULL);
}

void	delete_all_input_forks(t_room *rooms)
{
	t_room	*buf;
	t_list	*list_names;
	int 	level;

	level = 0;
	list_names = get_names(rooms);
	while (1)
	{
		buf = get_same_level(rooms, &list_names, level);
		buf = (buf == NULL) ? get_same_level(rooms, &list_names, ++level) : buf;
		if (buf == NULL)
			break ;
		if (buf->status != END && buf->status != START && buf->count_input > 1)
		{
			ft_printf("FORK IN {red}%s{eoc}\n", buf->name);
			delete_input_forks(buf);
		}
	}
	free_list(&list_names);
}

int 	get_highest_bfs_level(t_room *rooms)
{
	t_room	*buf;
	int 	level;

	level = 0;
	buf = rooms;
	while (buf)
	{
		if (buf->bfs_level > level && buf->status != END)
			level = buf->bfs_level;
		buf = buf->next;
	}
	return (level);
}

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

int 	not_equal_room(t_room *room, t_rooms *buf)
{
	if (buf->room != room)
		return (1);
	return (0);
}

void	delete_output_forks(t_room *room)
{
	t_list *pathes; //список путей, content-size -- длина пути
	t_path *path;

	pathes = get_pathes(room);
	path = get_min_len_path(pathes);
 	ft_delete_elem(&(room->aligned_union_room), path->next->room, not_equal_room);
	ft_delete_elem(&(room->union_room), path->next->room, not_equal_room);
	free_pathes(&pathes);
}

void	delete_all_output_forks(t_room *rooms)
{
	t_room	*buf;
	t_list	*list_names;
	int 	level;

	level = get_highest_bfs_level(rooms);
	list_names = get_names(rooms);
	while (1)
	{
		buf = get_same_level(rooms, &list_names, level);
		buf = (buf == NULL) ? get_same_level(rooms, &list_names, --level) : buf;
		if (buf == NULL)
			break ;
		if (buf->status != END && buf->status != START && buf->count_output > 1)
		{
			ft_printf("FORK IN {red}%s{eoc}\n", buf->name);
			delete_output_forks(buf);
		}
	}
	free_list(&list_names);
}

t_room *get_start_room(t_room *rooms)
{
	t_room *buf;

	buf = rooms;
	while (buf)
	{
		if (buf->status == START)
			return (buf);
		buf = buf->next;
	}
	return (NULL);
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

void	perform_pathes(t_list *pathes, int ants)
{
	int		step;
	int		p_num;
	t_list	*buf;

	step = 1;

	while (ants)
	{
		ft_printf("{green_bg}\t{eoc}{red}STEP #%d{eoc}\n", step);
		buf = pathes;
		p_num = 1;
		while (buf && ants)
		{
			ft_printf("Path%02d: %d > %d Move? ", p_num, ants, get_expr_pathes(pathes, buf));
			if (ants > (int)get_expr_pathes(pathes, buf))
			{
				ft_printf("YES\n");
				ants--;
			}
			else
				ft_printf("NO\n");
			buf = buf->next;
			p_num++;
		}
		step++;
	}

}

void perform_test(int num, t_room **rooms);

int main()
{
	t_room *rooms;
	t_list	*pathes;

	rooms = NULL;


	perform_test(8 , &rooms);

	t_queue *queue;
	t_room *start_room;

	start_room = find_start_room(rooms);
	queue = NULL;
	add_elem_queue(&queue, start_room);
	start_room->bfs_level = 0;
	bfs(rooms, queue);
	print_list(rooms);

	delete_useless_links(rooms);
	ft_printf("\nAFTER DELETE_USELESS_LINKS:\n");
	ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
	print_list(rooms);

	align_all_links(rooms);
	count_all_input_output_links(rooms);
	ft_printf("\nAFTER ALIGN AND COUNT LINKS:\n");
	ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
	print_list(rooms);

	while (delete_all_dead_ends(rooms) == 1)
		count_all_input_output_links(rooms);
	ft_printf("\nAFTER DELETE_DEAD_ENDS:\n");
	ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
	print_list(rooms);


	delete_all_input_forks(rooms);
	count_all_input_output_links(rooms);
	ft_printf("\nAFTER DELETE_INPUT_FORKS\n");
	ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
	print_list(rooms);

	delete_all_output_forks(rooms);
	count_all_input_output_links(rooms);
	ft_printf("\nAFTER DELETE_OUTPUT_FORKS\n");
	ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
	print_list(rooms);

	ft_printf("\nPATHES FROM START TO END\n");
	ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
	pathes = get_pathes(get_start_room(rooms));
	print_pathes(pathes);

	ft_printf("\nPERFORM PATHES\n");
	ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
	perform_pathes(pathes, 20);
	free_pathes(&pathes);
	free_rooms(&rooms);
	return 0;
}

void	perform_test(int num, t_room **rooms)
{
	if (num == 1)
	{
		push_back_room(rooms, new_room("room_0", 10, 0));
		push_back_room(rooms, new_room("room_1", 10, 0));
		push_back_room(rooms, new_room("room_2", 10, 0));
		push_back_room(rooms, new_room("room_3", 10, 0));
		push_back_room(rooms, new_room("room_4", 10, 0));
		push_back_room(rooms, new_room("room_5", 10, 0));
		find_room_by_name(*rooms, "room_0")->status = START;
		find_room_by_name(*rooms, "room_5")->status = END;
		add_union(*rooms, "room_0", "room_1");
		add_union(*rooms, "room_0", "room_2");
		add_union(*rooms, "room_0", "room_3");
		add_union(*rooms, "room_2", "room_1");
		add_union(*rooms, "room_2", "room_3");
		add_union(*rooms, "room_4", "room_1");
		add_union(*rooms, "room_3", "room_4");
		add_union(*rooms, "room_2", "room_4");
		add_union(*rooms, "room_4", "room_5");
	}
	if (num == 2)
	{
		push_back_room(rooms, new_room("room_0", 10, 0));
		push_back_room(rooms, new_room("room_1", 10, 5));
		push_back_room(rooms, new_room("room_2", 15, 5));
		push_back_room(rooms, new_room("room_3", 5, 10));
		push_back_room(rooms, new_room("room_4", 10, 10));
		push_back_room(rooms, new_room("room_5", 20, 10));
		push_back_room(rooms, new_room("room_6", 0, 15));
		push_back_room(rooms, new_room("room_7", 5, 17));
		push_back_room(rooms, new_room("room_8", 0, 20));
		push_back_room(rooms, new_room("room_9", 10, 25));
		push_back_room(rooms, new_room("room_10", 15, 25));
		find_room_by_name(*rooms, "room_0")->status = START;
		find_room_by_name(*rooms, "room_9")->status = END;
		add_union(*rooms, "room_0", "room_1");
		add_union(*rooms, "room_0", "room_2");
		add_union(*rooms, "room_2", "room_5");
		add_union(*rooms, "room_2", "room_4");
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_1", "room_4");
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_4", "room_3");
		add_union(*rooms, "room_3", "room_6");
		add_union(*rooms, "room_3", "room_7");
		add_union(*rooms, "room_4", "room_9");
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_6", "room_8");
		add_union(*rooms, "room_8", "room_9");
		add_union(*rooms, "room_7", "room_9");
		add_union(*rooms, "room_9", "room_10");
	}
	if (num == 3)
	{
		push_back_room(rooms, new_room("room_1", 10, 5));
		push_back_room(rooms, new_room("room_2", 15, 5));
		push_back_room(rooms, new_room("room_3", 5, 10));
		push_back_room(rooms, new_room("room_4", 10, 10));
		push_back_room(rooms, new_room("room_5", 20, 10));
		push_back_room(rooms, new_room("room_6", 0, 15));
		push_back_room(rooms, new_room("room_7", 5, 17));
		find_room_by_name(*rooms, "room_1")->status = START;
		find_room_by_name(*rooms, "room_7")->status = END;
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_1", "room_6");
		add_union(*rooms, "room_1", "room_4");
		add_union(*rooms, "room_2", "room_3");
		add_union(*rooms, "room_2", "room_4");
		add_union(*rooms, "room_4", "room_6");
		add_union(*rooms, "room_2", "room_5");
		add_union(*rooms, "room_6", "room_5");
		add_union(*rooms, "room_6", "room_7");
	}
	if (num == 4)
	{
		push_back_room(rooms, new_room("room_1", 10, 5));
		push_back_room(rooms, new_room("room_2", 15, 5));
		push_back_room(rooms, new_room("room_3", 5, 10));
		push_back_room(rooms, new_room("room_4", 10, 10));
		push_back_room(rooms, new_room("room_5", 20, 10));
		push_back_room(rooms, new_room("room_6", 0, 15));
		find_room_by_name(*rooms, "room_1")->status = START;
		find_room_by_name(*rooms, "room_6")->status = END;
		add_union(*rooms, "room_1", "room_2");
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_2", "room_3");
		add_union(*rooms, "room_2", "room_4");
		add_union(*rooms, "room_4", "room_5");
		add_union(*rooms, "room_5", "room_6");
	}
	if (num == 5)
	{
		push_back_room(rooms, new_room("room_1", 10, 5));
		push_back_room(rooms, new_room("room_2", 15, 5));
		push_back_room(rooms, new_room("room_3", 5, 10));
		push_back_room(rooms, new_room("room_4", 10, 10));
		push_back_room(rooms, new_room("room_5", 20, 10));
		push_back_room(rooms, new_room("room_6", 0, 15));
		push_back_room(rooms, new_room("room_7", 5, 17));
		push_back_room(rooms, new_room("room_8", 0, 20));
		push_back_room(rooms, new_room("room_9", 10, 25));
		push_back_room(rooms, new_room("room_10", 15, 25));
		push_back_room(rooms, new_room("room_11", 15, 25));
		push_back_room(rooms, new_room("room_12", 15, 25));
		push_back_room(rooms, new_room("room_13", 15, 25));
		find_room_by_name(*rooms, "room_1")->status = START;
		find_room_by_name(*rooms, "room_13")->status = END;
		add_union(*rooms, "room_1", "room_2");
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_2", "room_3");
		add_union(*rooms, "room_2", "room_4");
		add_union(*rooms, "room_3", "room_6");
		add_union(*rooms, "room_4", "room_6");
		add_union(*rooms, "room_1", "room_5");
		add_union(*rooms, "room_4", "room_7");
		add_union(*rooms, "room_6", "room_8");
		add_union(*rooms, "room_7", "room_5");
		add_union(*rooms, "room_5", "room_8");
		add_union(*rooms, "room_5", "room_9");
		add_union(*rooms, "room_9", "room_10");
		add_union(*rooms, "room_9", "room_11");
		add_union(*rooms, "room_10", "room_12");
		add_union(*rooms, "room_11", "room_12");
		add_union(*rooms, "room_12", "room_13");
	}
	if (num == 6)
	{
		push_back_room(rooms, new_room("room_1", 10, 5));
		push_back_room(rooms, new_room("room_2", 15, 5));
		push_back_room(rooms, new_room("room_3", 5, 10));
		push_back_room(rooms, new_room("room_4", 10, 10));
		push_back_room(rooms, new_room("room_5", 20, 10));
		push_back_room(rooms, new_room("room_6", 0, 15));
		push_back_room(rooms, new_room("room_7", 0, 15));
		push_back_room(rooms, new_room("room_8", 0, 15));
		push_back_room(rooms, new_room("room_9", 0, 15));
		find_room_by_name(*rooms, "room_1")->status = START;
		find_room_by_name(*rooms, "room_6")->status = END;
		add_union(*rooms, "room_1", "room_2");
		add_union(*rooms, "room_1", "room_4");
		add_union(*rooms, "room_2", "room_3");
		add_union(*rooms, "room_3", "room_6");
		add_union(*rooms, "room_4", "room_5");
		add_union(*rooms, "room_5", "room_7");
		add_union(*rooms, "room_7", "room_8");
		add_union(*rooms, "room_8", "room_9");
		add_union(*rooms, "room_9", "room_6");
	}
	if (num == 7)
	{
		push_back_room(rooms, new_room("room_0", 10, 5));
		push_back_room(rooms, new_room("room_1", 10, 5));
		push_back_room(rooms, new_room("room_2", 15, 5));
		push_back_room(rooms, new_room("room_3", 5, 10));
		push_back_room(rooms, new_room("room_4", 10, 10));
		push_back_room(rooms, new_room("room_5", 20, 10));
		push_back_room(rooms, new_room("room_6", 0, 15));
		push_back_room(rooms, new_room("room_7", 5, 17));
		find_room_by_name(*rooms, "room_1")->status = START;
		find_room_by_name(*rooms, "room_0")->status = END;
		add_union(*rooms, "room_0", "room_6");
		add_union(*rooms, "room_0", "room_4");
		add_union(*rooms, "room_1", "room_2");
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_2", "room_7");
		add_union(*rooms, "room_2", "room_1");
		add_union(*rooms, "room_2", "room_5");
		add_union(*rooms, "room_3", "room_5");
		add_union(*rooms, "room_3", "room_1");
		add_union(*rooms, "room_4", "room_3");
		add_union(*rooms, "room_4", "room_2");
		add_union(*rooms, "room_5", "room_3");
		add_union(*rooms, "room_5", "room_2");
		add_union(*rooms, "room_5", "room_6");
		add_union(*rooms, "room_6", "room_5");
		add_union(*rooms, "room_6", "room_7");
		add_union(*rooms, "room_7", "room_6");
		add_union(*rooms, "room_7", "room_2");
		add_union(*rooms, "room_7", "room_4");
		add_union(*rooms, "room_7", "room_6");
		add_union(*rooms, "room_7", "room_2");
		add_union(*rooms, "room_7", "room_4");
	}
	if (num == 8)
	{
		push_back_room(rooms, new_room("start", 10, 5));
		push_back_room(rooms, new_room("end", 10, 5));
		push_back_room(rooms, new_room("3", 15, 5));
		push_back_room(rooms, new_room("4", 5, 10));
		push_back_room(rooms, new_room("1", 10, 10));
		push_back_room(rooms, new_room("2", 15, 5));
		push_back_room(rooms, new_room("5", 5, 10));
		push_back_room(rooms, new_room("6", 10, 10));
		find_room_by_name(*rooms, "start")->status = START;
		find_room_by_name(*rooms, "end")->status = END;
		add_union(*rooms, "start", "1");
		add_union(*rooms, "3", "4");
		add_union(*rooms, "2", "4");
		add_union(*rooms, "1", "5");
		add_union(*rooms, "6", "5");
		add_union(*rooms, "end", "6");
		add_union(*rooms, "1", "2");
		add_union(*rooms, "2", "end");
		add_union(*rooms, "3", "start");
	}
	if (num == 9)
	{
		push_back_room(rooms, new_room("room_0", 10, 5));
		push_back_room(rooms, new_room("room_1", 10, 5));
		push_back_room(rooms, new_room("room_2", 15, 5));
		push_back_room(rooms, new_room("room_3", 5, 10));
		push_back_room(rooms, new_room("room_4", 10, 10));
		push_back_room(rooms, new_room("room_5", 20, 10));
		push_back_room(rooms, new_room("room_6", 0, 15));
		find_room_by_name(*rooms, "room_0")->status = START;
		find_room_by_name(*rooms, "room_6")->status = END;
		add_union(*rooms, "room_0", "room_1");
		add_union(*rooms, "room_0", "room_2");
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_2", "room_3");
		add_union(*rooms, "room_3", "room_4");
		add_union(*rooms, "room_3", "room_5");
		add_union(*rooms, "room_4", "room_6");
		add_union(*rooms, "room_5", "room_6");
	}
}