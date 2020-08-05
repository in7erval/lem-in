#include "lem_in.h"

t_tree	*ft_new_tree(void)
{
	t_tree *tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	tree->room = NULL;
	tree->child_count = 0;
	tree->intersect = NULL;
	tree->parent = NULL;
	tree->length = 0;
	return (tree);
}

t_path	*ft_tree_to_path(t_tree *tree)
{
	t_tree	*cur;
	t_path	*path;

	path = ft_path_new();
	cur = tree;
	while (cur)
	{
		add_elem_path(path, cur->room);
		cur = cur->parent;
	}
	return (path);
}

t_tree	*tree_create_child(t_tree *tree, t_room *room)
{
	t_tree *res;

	res = ft_new_tree();
	res->parent = tree;
	res->intersect = tree->intersect;
	res->length = tree->length;
	res->room = room;
	if (tree)
		tree->child_count++;
	return (res);
}

void	tree_del(t_tree *tree)
{
	t_tree	*del;
	t_tree	*cur;

	cur = tree;
	while (cur && cur->child_count == 0)
	{
		del = cur;
		if (cur->parent)
			cur->parent->child_count--;
		cur = cur->parent;
		free(del);
	}
}