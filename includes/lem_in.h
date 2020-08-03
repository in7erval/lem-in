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

typedef struct		s_map
{
	char			*str;
	struct s_map	*next;
}					t_map;

typedef	struct		s_room
{
	char			*name;
	int				x;
	int				y;
	struct s_room	*next;
	struct s_room	*prev;
	int				bfs_level;
	int				status;
	int				count_input;
	int				count_output;
}					t_room;

typedef struct		s_link
{
	t_room			*from;
	t_room			*to;
	struct s_link	*next;
}					t_link;
typedef struct		s_queue
{
	t_room			*room;
	struct s_queue	*next;
	struct s_queue	*prev;
}					t_queue;

typedef struct		s_ant
{
	size_t			number;
	int				room_number;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_path
{
	t_room			*room;
	t_ant			*ants;
	struct s_path	*next;
}					t_path;

typedef struct		s_lemin
{
	t_room			*rooms;
	t_link			*links;
	t_room			*start;
	t_list			*pathes;
	t_room			*end;
	size_t			num_ants;
	t_map			*map;
	int				bfs_level;
	int				c_bonus;
	int				p_bonus;
}					t_lemin;

# define START 1
# define END 2
# define COMMON 3
# define MAX_INT 2147483647
# define MALLOC_ERROR "MALLOC_ERROR"

/*
** ft_cleaner/c
*/
void				ft_clean_ants(char **str);
void				ft_clean_rooms(char **str);

/*
** ft_queue.c
*/
void				add_elem_queue(t_queue **queue, t_room *room);
t_queue				*new_queue_elem(t_room *room);
t_queue				*poll_elem_queue(t_queue **queue);
void				print_queue(t_queue *queue);

/*
** ft_path.c
*/
t_path				*new_elem_path(t_room *room);
void				add_elem_path(t_path **path, t_room *room);
void				add_elem_path_start(t_path **path, t_room *room);
void				free_path(t_path **path);
size_t				get_length_path(t_path *path);

/*
** ft_path_print.c
*/
void				print_path(t_path *path);
void				print_pathes(t_list *pathes);

/*
** ft_path_funcs.c
*/
t_path				*get_path_to_end(t_lemin *lemin, t_room *room);
t_list				*get_pathes(t_lemin *lemin, t_room *room);
void				free_pathes(t_list **pathes);
t_path				*get_min_len_path(t_list *pathes);
t_room				*get_room_by_roomnumber(t_path *path, int room_number);

/*
** ft_sort_pathes.c
*/
t_list				*sort_pathes(t_list *pathes);

/*
** ft_perform_pathes.c
*/
void				perform_pathes(t_lemin *lemin);

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
** ft_delete_links.c
*/
int					ft_delete_links(t_lemin *lemin, int (*f)(t_link *link));
void				ft_delete_link(t_lemin *lemin, t_link *link);
int					ft_delete_input_except(t_lemin *lemin, t_link *link);
void				ft_delete_links_from_path(t_lemin *lemin, t_path *path);

/*
** ft_for_delete_links.c
*/
int					check_one_level(t_link *link);
int					check_dead_end(t_link *link);

/*
** ft_room_union.c
*/
int					is_in_union(t_lemin *lemin, t_room *room,
					t_room *check_room);
int					add_union(t_lemin *lemin, char *room1_name,
					char *room2_name);

/*
** ft_room.c
*/
t_room				*new_room(char *name, int x, int y);
void				push_back_room(t_room **head, t_room *room);
void				free_rooms(t_room **rooms);
void				free_list(t_list **list);

/*
** ft_room_funcs.c
*/
t_room				*find_room_by_name(t_room *rooms, char *name);
t_room				*find_room_by_signal(t_room *rooms, int signal);
t_room				*find_room_by_coordinates(t_room *rooms, int x, int y);

/*
** ft_count.c
*/
void				count_input_output_links(t_lemin *lemin, t_room *room);
void				count_all_input_output_links(t_lemin *lemin);

/*
** ft_delete_forks.c
*/
int					check_output_fork(t_lemin *lemin, t_room *room);
void				delete_input_forks(t_lemin *lemin, t_room *room);
void				delete_all_input_forks(t_lemin *lemin);
void				delete_output_forks(t_lemin *lemin, t_room *room);
void				delete_all_output_forks(t_lemin *lemin);

/*
** ft_bfs_align_dead_ends.c
*/
void				bfs(t_lemin *lemin, t_queue *queue);
void				delete_useless_links(t_lemin *lemin);
void				align_all_links(t_lemin *lemin);
void				delete_all_dead_ends(t_lemin *lemin);

/*
** ft_ant.c
*/
t_ant				*new_ant(size_t number);
void				push_back_ant(t_ant **ants, t_ant *ant);
t_ant				*get_ant_by_room_number(t_path *path, int number);
void				null_all_ants(t_list *list);
void				free_ants(t_ant **ants);

/*
** utils.c
*/
void				error_exit(char *str);
int					count_of_words(const char *str, char c);
int					ft_free_error(t_lemin *lemin);
void				ft_free_lemin(t_lemin *lemin);

/*
** ft_init.c
*/
t_lemin				*init_lemin(void);

/*
** ft_link.c
*/
t_link				*ft_create_link(t_room *room1, t_room *room2);
void				ft_pb_link(t_link **links, t_link *link);
void				free_links(t_link **links);
t_room				*get_room_link_from(t_link *links, t_room *from);
void				print_links(t_link *links);

/*
** ft_markup_bfs.c
*/
int					ft_markup_bfs(t_lemin *lemin);
void				ft_beautify_rooms(t_lemin *lemin);
void				ft_bonus(int argc, char **argv, t_lemin *lemin);
int					check_usage(int argc, char **argv);

#endif