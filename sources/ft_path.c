
#include "lem-in.h"

t_path *new_elem_path(t_room *room)
{
	t_path *path;

	path = (t_path *)malloc(sizeof(t_path));
	path->room = room;
	path->next = NULL;
	path->ants = NULL;
	return (path);
}

void add_elem_path(t_path **path, t_room *room)
{
	t_path *elem;
	t_path *buf;

	elem = new_elem_path(room);
	if (*path == NULL)
		*path = elem;
	else
	{
		buf = *path;
		while (buf->next)
			buf = buf->next;
		buf->next = elem;
	}
}

void add_elem_path_start(t_path **path, t_room *room)
{
	t_path *elem;

	elem = new_elem_path(room);
	elem->next = (*path);
	(*path) = elem;
}

void free_path(t_path **path)
{
	t_path *buf;
	t_path *kill;

	if (path && *path)
	{
		buf = *path;
		while (buf)
		{
			kill = buf;
			buf = buf->next;
			free_ants(&(kill->ants));
			free(kill);
		}
		*path = NULL;
	}
}

t_path *get_path_to_end(t_room *room)
{
	t_path *path;
	t_room *buf;

	path = NULL;
	buf = room;
	while (buf)
	{
		add_elem_path(&path, buf);
		if (buf->status == END)
			break ;
		if (buf->aligned_union_room == NULL)
		{
			free_path(&path);
			return (NULL);
		}
		buf = buf->aligned_union_room->room;
	}
	return (path);
}

void	print_path(t_path *path)
{
	t_path *buf;

	buf = path;
	while (buf->next)
	{
		ft_printf("{yellow}%s->", buf->room->name);
		buf = buf->next;
	}
	ft_printf("%s{eoc}", buf->room->name);
	ft_printf("\n");
}

void	print_pathes(t_list *pathes)
{
	t_list	*path;
	int		num;

	path = pathes;
	num = 1;
	while (path)
	{
		if (path->content != NULL)
		{
			ft_printf("Path{green}%02d{eoc} length: {blue}%3d{eoc} {black_bg}|||{eoc}\t", num, path->content_size);
			print_path(path->content);
			num++;
		}
		path = path->next;
	}
}


size_t	get_length_path(t_path *path)
{
	t_path	*buf;
	size_t	i;

	i = 0;
	buf = path;
	while (buf)
	{
		i++;
		buf = buf->next;
	}
	return (i);
}
