#include "lem_in.h"

static int paths_count(t_lemin *lemin)
{
	int 	count;
	t_link	*cur;

	count = 0;
	cur = lemin->links;
	while (cur)
	{
		if (cur->from == lemin->start)
			if (cur->to->next || cur->to->status == END)
				count++;
		cur = cur->next;
	}
	return (count);
}

static void	create_paths(t_lemin *lemin, t_group *group)
{
	t_link	*cur;
	t_path	*path;
	int 	i;

	i = 0;
	cur = lemin->links;
	while (cur)
	{
		if (cur->from == lemin->start)
			if (cur->to->next || cur->to->status == END)
			{
				path = ft_build_path(lemin->start, cur->to);
				group->paths[i] = path;
				i++;
			}
		cur = cur->next;
	}
}

static int cmp_path_len(void *a, void *b)
{
	return (((t_path *)a)->len - ((t_path *)b)->len);
}

static int group_rounds(t_group *group)
{
	int ret;
	int i;
	int buf;

	ret = 0;
	i = 0;
	while (i < group->path_count)
	{
		if (group->ants[i] > 0)
		{
			buf = group->ants[i] + group->paths[i]->len - 1;
			if (buf > ret)
				ret = buf;
		}
		i++;
	}
	return (ret);
}

void	check_and_rev(t_group *group)
{
	int		i;
	t_path	*path;

	i = 0;
	while (i < group->path_count)
	{
		path = group->paths[i];
		if (((t_room *)(path->rooms->content))->status == END)
			ft_lstrev(&(path->rooms));
		i++;
	}
}

t_group	*group_build(t_lemin *lemin)
{
	t_group *group;

	group = (t_group *)malloc(sizeof(t_group));
	group->path_count = paths_count(lemin);
	group->paths = (t_path **)malloc(sizeof(t_path *) * group->path_count);
	group->ants = ft_memalloc(sizeof(int) * group->path_count);
	create_paths(lemin, group);
	sort_array((void **)group->paths, group->path_count, cmp_path_len);
	perform_ants(group, lemin->num_ants);
	group->total_rounds = group_rounds(group);
	return (group);
}

void	print_group(t_group *group)
{
	int	i;

	i = 0;
	ft_printf("\tGroup\n");
	ft_printf("Path_count: %d\tTotal_rounds: %d\n", group->path_count, group->total_rounds);
	while (i < group->path_count)
	{
		print_path(group->paths[i]);
		i++;
	}
	ft_printf("\n");
}

void	free_group(t_group *group)
{
	int i;

	i = 0;
	while (i < group->path_count)
		free_path(group->paths[i++]);
	free(group->paths);
	free(group->ants);
	free(group);
}