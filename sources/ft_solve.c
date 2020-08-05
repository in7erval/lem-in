/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_markup_bfs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/08/03 12:49:14 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "../libft/includes/libft.h"
#include "../includes/lem_in.h"

int 	ft_count_links(t_lemin *lemin, t_room *room)
{
	t_link	*link;
	int		count;

	count = 0;
	link = lemin->links;
	while (link)
	{
		if (link->from == room || link->to == room)
			count++;
		link = link->next;
	}
	return (count);
}

int 	max_paths(t_lemin *lemin)
{
	int start_links;
	int end_links;

	start_links = ft_count_links(lemin, lemin->start);
	end_links = ft_count_links(lemin, lemin->end);
	return (ft_min(ft_min(start_links, end_links), lemin->num_ants));
}

t_list	*init_first_level(t_lemin *lemin)
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

t_path	*try_finalize_traverse(t_tree *tree)
{
	if (tree->length > 0)
		return (ft_tree_to_path(tree));
	return (NULL);
}

t_tree	*go_to_start(t_lemin *lemin, t_tree *tree)
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

t_tree	*traverse_end(t_lemin *lemin, t_tree *node)
{
	if (node->parent->room->next != NULL)
		return (go_to_start(lemin, node));
	return (NULL);
}

t_tree	*traverse(t_tree *node, t_room *to)
{
	t_tree	*res;
	int 	len;
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

t_path	*extend_node(t_lemin *lemin, t_tree *node, t_list **next_nodes)
{
	t_tree	*new_node;
	t_path	*path;
	t_link	*link;

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
	link = lemin->links;
	while (link)
	{
		if (link->from == node->room || link->to == node->room)
		{
			if (link->from == node->room)
				new_node = traverse(node, link->to);
			else if (link->to == node->room)
				new_node = traverse(node, link->from);
			if (new_node)
				ft_lstadd(next_nodes, ft_lstnew(new_node, sizeof(t_tree)));
		}
		link = link->next;
	}
	return (NULL);
}

t_path 	*extend_nodes_list(t_lemin *lemin, t_list *nodes, t_list **next_nodes)
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

void	tree_del_list(t_list **tree)
{
	while ((*tree))
	{
		tree_del((t_tree *)((*tree)->content));
		ft_lstdelone(tree, NULL);
	}
}

t_path	*run_bft(t_lemin *lemin)
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

int 	has_path(t_room *room)
{
	return (room->next != NULL && room->prev != NULL);
}

t_room	*path_start(t_room *room)
{
	t_room *start;

	start = room;
	while (start->prev && start->prev->status != START)
		start = start->prev;
	return (start);
}

void	break_path(t_room *room)
{
	t_room 	*cur;
	t_room	*next;

	cur = path_start(room);
	while (cur && cur->status == COMMON)
	{
		next = cur->next;
		cur->prev = NULL;
		cur->next = NULL;
		cur = next;
	}
}

void	connect(t_room *prev, t_room *next)
{
	if (prev != NULL && prev->status != COMMON && next->status != COMMON)
		return ;
	if (prev != NULL && prev->status == COMMON)
		prev->next = next;
	if (next->status == COMMON)
		next->prev = prev;
}

void	rebuild_paths(t_path *path)
{
	t_list	*cur;
	t_room	*prev;

	cur = path->rooms;
	while (cur)
	{
		if (has_path((t_room *)(cur->content)))
			break_path((t_room *)(cur->content));
		cur = cur->next;
	}
	cur = path->rooms;
	prev = NULL;
	while (cur)
	{
		connect(prev, (t_room *)(cur->content));
		prev = (t_room *)(cur->content);
		cur = cur->next;
	}

}

t_group	*create_group(t_lemin *lemin)
{
	t_group	*best;
	t_group	*cur;
	int 	count;
	t_path	*traverse;

	count = 0;
	best = NULL;
	while (count < lemin->max_paths)
	{
		traverse = run_bft(lemin);
		if (traverse == NULL)
			break;
		rebuild_paths(traverse);
		cur = group_build(lemin);
		print_group(cur);
		free_path(traverse);
		if (!best)
			best = cur;
		else if (best->total_rounds > cur->total_rounds)
		{
			free_group(best);
			best = cur;
		}
		else
			free_group(cur);
		count++;
	}
	return (NULL);
}

void	solve(t_lemin *lemin)
{
	t_group	*paths;

	lemin->max_paths = max_paths(lemin);
	ft_printf("Max_paths: %d\n", lemin->max_paths);
	paths = create_group(lemin);
}

void	ft_bonus(int argc, char **argv, t_lemin *lemin)
{
	if (argc == 2 && !ft_strcmp(argv[1], "-c"))
		lemin->c_bonus = 1;
	else if (argc == 2 && !ft_strcmp(argv[1], "-p"))
		lemin->p_bonus = 1;
	else if ((argc == 2 && (!ft_strcmp(argv[1], "-cp") ||
			!ft_strcmp(argv[1], "-pc"))) || (argc == 3 &&
			((!ft_strcmp(argv[1], "-c") && !ft_strcmp(argv[2], "-p")) ||
			(!ft_strcmp(argv[1], "-p") && !ft_strcmp(argv[2], "-c")))))
	{
		lemin->c_bonus = 1;
		lemin->p_bonus = 1;
	}
}

int		check_usage(int argc, char **argv)
{
	if (argc > 3 || (argc == 2 && (ft_strcmp(argv[1], "-c") &&
		ft_strcmp(argv[1], "-p") && ft_strcmp(argv[1], "-pc") &&
		ft_strcmp(argv[1], "-cp"))) || (argc == 3 &&
		!((!ft_strcmp(argv[1], "-c") || !ft_strcmp(argv[2], "-p"))
		|| (!ft_strcmp(argv[1], "-p") && !ft_strcmp(argv[2], "-c")))))
	{
		ft_printf("{white}{bold}Usage:{eoc} ./lemin [-{red}c{eoc}{yellow}"
			"p{eoc}] < file_with_map\n{white}{bold}Options:{eoc}\n\t{red}-c\t"
	"Print cleaned map{eoc}\n\t{yellow}-p\tPrint paths{eoc}\n");
		return (1);
	}
	return (0);
}
