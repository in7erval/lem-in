#include "lem_in.h"

t_tree			*go_to_start(t_lemin *lemin, t_tree *tree)
{
	t_room	*room;
	t_tree	*res;

	room = tree->parent->room;
	while (room->prev->status != START)
		room = room->prev;
	if (tree->intersect == room)
		return (NULL);
	res = tree_create_child(tree, lemin->start);
	res = tree_create_child(res, room);
	res->length++;
	return (res);
}

static t_list	*init_first_level(t_lemin *lemin)
{
	t_list	*res;
	t_tree	*tree;

	res = NULL;
	tree = ft_new_tree();
	tree->room = lemin->start;
	tree->length = 1;
	ft_lstadd(&res, ft_lstnew(tree, sizeof(t_tree)));
	return (res);
}

t_path			*run_bft(t_lemin *lemin)
{
	t_list	*nodes;
	t_list	*next_nodes;
	t_path	*res;

	reset_visit(lemin);
	nodes = init_first_level(lemin);
	next_nodes = NULL;
	while (1)
	{
		res = extend_nodes_list(lemin, nodes, &next_nodes);
		tree_del_list(&nodes);
		if (res)
		{
			tree_del_list(&next_nodes);
			return (res);
		}
		if (next_nodes == NULL)
			return (NULL);
		nodes = next_nodes;
		next_nodes = NULL;
	}
}
