#include "lem-in.h"

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
			ft_printf("INPUT FORK IN {red}%s{eoc}\n", buf->name);
			delete_input_forks(buf);
		}
	}
	free_list(&list_names);
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
			ft_printf("OUTPUT FORK IN {red}%s{eoc}\n", buf->name);
			delete_output_forks(buf);
		}
	}
	free_list(&list_names);
}