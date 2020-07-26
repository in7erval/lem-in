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
