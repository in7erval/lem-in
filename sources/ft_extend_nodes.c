/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extend_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:22:14 by htrent            #+#    #+#             */
/*   Updated: 2020/08/10 15:22:16 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_tree	*traverse(t_tree *node, t_room *to)
{
	t_tree	*res;
	int		len;
	t_room	*intersect;

	if (!can_traverse(node, to))
		return (NULL);
	len = node->length;
	if (in_intersect(node->room, to))
	{
		len--;
		if (len < 0)
			return (NULL);
		intersect = to;
	}
	else if (out_intersect(node->room, to))
		intersect = NULL;
	else
		intersect = node->intersect;
	res = tree_create_child(node, to);
	res->length = len;
	res->intersect = intersect;
	return (res);
}

static t_path	*try_finalize_traverse(t_tree *tree)
{
	if (tree->length > 0)
		return (ft_tree_to_path(tree));
	return (NULL);
}

static t_tree	*traverse_end(t_lemin *lemin, t_tree *node)
{
	if (node->parent->room->next != NULL)
		return (go_to_start(lemin, node));
	return (NULL);
}

static t_path	*extend_node(t_lemin *lemin, t_tree *node, t_list **next_nodes)
{
	t_tree	*new_node;
	t_path	*path;
	t_list	*cur;

	visit(node);
	new_node = NULL;
	if (node && node->room->status == END)
	{
		path = try_finalize_traverse(node);
		if (path)
			return (path);
		new_node = traverse_end(lemin, node);
		if (new_node)
			ft_lstadd(next_nodes, ft_lstnew(new_node, sizeof(t_tree)));
		return (NULL);
	}
	cur = node->room->links;
	while (cur)
	{
		new_node = traverse(node, (t_room *)cur->content);
		if (new_node)
			ft_lstadd(next_nodes, ft_lstnew(new_node, sizeof(t_tree)));
		cur = cur->next;
	}
	return (NULL);
}

t_path			*extend_nodes_list(t_lemin *lemin, t_list *nodes,
							t_list **next_nodes)
{
	t_list	*cur;
	t_path	*path;

	cur = nodes;
	while (cur)
	{
		path = extend_node(lemin, (t_tree *)(cur->content), next_nodes);
		if (path)
			return (path);
		cur = cur->next;
	}
	return (NULL);
}
