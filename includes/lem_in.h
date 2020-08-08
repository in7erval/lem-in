/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2020/02/07 13:43:30 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_LEM_IN_H
# define LEMIN_LEM_IN_H

# include "libft.h"
# include "ft_printf.h"

typedef struct		s_options
{
	int				c_bonus;
	int				p_bonus;
	int				r_bonus;
}					t_options;

typedef struct		s_map
{
	char			*str;
	struct s_map	*next;
	struct s_map	*prev;
}					t_map;

typedef	struct		s_room
{
	char			*name;
	int				x;
	int				y;
	struct s_room	*next;
	struct s_room	*prev;
	int				status;
	int				visited;
	int				visited2;
	int				count_links;
	size_t			ants;
	int				ant_number;
	t_list			*links;
}					t_room;

typedef struct		s_tree
{
	t_room			*room;
	struct s_tree	*parent;
	int				child_count;
	int				length;
	t_room			*intersect;
}					t_tree;

typedef struct		s_path
{
	t_list			*rooms;
	int				id;
	int				len;
}					t_path;

typedef	struct		s_group
{
	int				path_count;
	int				total_rounds;
	int				*ants;
	t_path			**paths;
}					t_group;

typedef	struct		s_move
{
	int				ant_number;
	t_room			*dest;
}					t_move;

typedef	struct		s_round
{
	t_list			*moves;
}					t_round;

typedef	struct		s_answer
{
	int				round;
	int				path;
	t_list			*rounds;
}					t_answer;

typedef struct		s_lemin
{
	t_list			*rooms;
	t_room			*start;
	t_room			*end;
	size_t			num_ants;
	t_map			*map;
	int				max_paths;
	t_options		options;
	t_group			*group;
	t_answer		*answer;
}					t_lemin;

# define START 1
# define END 2
# define COMMON 3
# define MAX_INT 2147483647
# define MALLOC_ERROR "MALLOC_ERROR"

/*
** ft_group.c
*/
t_group				*group_build(t_lemin *lemin);
void				print_group(t_group *group, int flag);
void				free_group(t_group *group);

/*
** ft_extend_nodes.c
*/
t_path				*extend_nodes_list(t_lemin *lemin, t_list *nodes,
										t_list **next_nodes);

/*
** ft_bft.c
*/
t_path				*run_bft(t_lemin *lemin);
t_tree				*go_to_start(t_lemin *lemin, t_tree *tree);

/*
** ft_solve.c
*/
int					ft_solve(t_lemin *lemin);

/*
** ft_solve_utils.c
*/
void				reset_visit(t_lemin *lemin);
int					can_traverse(t_tree *node, t_room *to);
int					in_intersect(t_room *room1, t_room *room2);
int					out_intersect(t_room *room1, t_room *room2);
void				visit(t_tree *tree);

/*
** ft_path.c
*/
t_path				*ft_path_new(void);
t_path				*ft_build_path(t_room *from, t_room *to);
void				add_elem_path(t_path *path, t_room *room);
void				free_path(t_path *path);

/*
** ft_path_funcs.c
*/
void				rebuild_paths(t_path *path);

/*
** ft_path_print.c
*/
void				print_path(t_path *path);

/*
** ft_perform_paths.c
*/
void				perform_paths(t_lemin *lemin);

/*
** ft_perform_ants.c
*/
void				perform_ants(t_group *group, int num_ants);

/*
** ft_map.c
*/
void				ft_map_clean(t_map **head);
void				ft_map_show(t_map *head);
void				ft_map_add(t_map **head, char *str);

/*
** ft_is.c
*/
int					ft_isknowncommand(char *str);
int					ft_iscomment(const char *str);
int					ft_isants(char *str);
int					ft_isrooms(char *str);
int					ft_islinks(char *str);

/*
** ft_parse.c
*/
int					ft_parse(t_lemin *lemin);

/*
** ft_parse_links.c
*/
int					ft_links(t_lemin *lemin, char *buffer, int *has_links);

/*
** ft_parse_rooms.c
*/
int					ft_rooms(t_lemin *lemin);

/*
** ft_optimize.c
*/
void				ft_optimize(t_lemin *lemin);

/*
** ft_room_union.c
*/
int					is_in_union(t_room *room, t_room *check_room);
int					add_union(t_room *room1, t_room *room2);

/*
** ft_room.c
*/
t_room				*new_room(char *name, int x, int y);
void				free_list(t_list **list);
void				ft_free_room(t_room *room);
void				free_rooms(t_list **rooms);

/*
** ft_room_funcs.c
*/
t_room				*find_room_by_name(t_list *rooms, char *name);
t_room				*find_room_by_signal(t_list *rooms, int signal);
t_room				*find_room_by_coordinates(t_list *rooms, int x, int y);

/*
** ft_init.c
*/
t_lemin				*init_lemin(t_options options);

/*
** ft_usage.c
*/
int					check_usage(int argc, char **argv, t_options *options);

/*
** ft_tree.c
*/
t_tree				*ft_new_tree(void);
t_path				*ft_tree_to_path(t_tree *tree);
t_tree				*tree_create_child(t_tree *tree, t_room *room);
void				tree_del(t_tree *tree);
void				tree_del_list(t_list **tree);

/*
** ft_array.c
*/
void				sort_array(void **array, size_t size,
					int (*cmp)(void *, void *));

/*
** ft_print.c
*/
void				print_answer(t_lemin *lemin);

/*
** ft_answer.c
*/
t_answer			*ft_init_answer(void);
void				ft_answer_add_round(t_answer *answer);
void				ft_answer_add_move(t_answer *answer, t_room *to);
void				free_answer(t_answer **answer);

/*
** ft_cleaner.c
*/
void				ft_clean_ants(char **str);
void				ft_clean_rooms(char **str);

/*
** utils.c
*/
void				error_exit(char *str);
int					count_of_words(const char *str, char c);
int					ft_free_error(t_lemin *lemin);
void				ft_free_lemin(t_lemin *lemin);
int					ft_min(int a, int b);

void				print_lemin(t_lemin *lemin, char *str);
void				print_room(t_lemin *lemin, t_room *room);

#endif
