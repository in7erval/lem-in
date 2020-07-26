//
// Created by Дмитрий Юдаков on 21.06.2020.
//

#ifndef LEMIN_LEM_IN_H
#define LEMIN_LEM_IN_H

#include "libft.h"
#include "ft_printf.h"

typedef struct s_rooms t_rooms;

typedef struct		s_map
{
	char 			*str;
	struct s_map	*next;
}					t_map;

typedef	struct		s_room
{
	char			*name; // Название комнаты
	int				x; // Координата X комнаты
	int 			y; // Координата Y Комнаты
	struct s_room	*next; // Следующая комната (двусвязный список)
	struct s_room	*prev; // Предыдущая комната (двусвязный список)
	t_rooms			*union_room; // Список комнат, с которыми текущая имеет связь
	int				bfs_level;
	int 			status;
	int 			bfs_status;
	t_rooms 			*aligned_union_room;
	int 			count_input;
	int 			count_output;
}					t_room;

typedef struct		s_rooms
{
	t_room 			*room;
	struct s_rooms	*next;
	struct s_rooms	*prev;
}					t_rooms;

typedef struct		s_queue
{
	t_room 			*room;
	struct s_queue	*next;
	struct s_queue	*prev;
}					t_queue;

typedef struct		s_path
{
	t_room 			*room;
	struct s_path	*next;
}					t_path;

#define START 1
#define END 2
#define COMMON 3

#define MAX_INT 2147483647

#define NOT_USED 0
#define POINTED 1
#define PAINTED 2


/*
 * ft_queue.c
 */
void add_elem_queue(t_queue **queue, t_room *room);
t_queue *new_queue_elem(t_room *room);
t_queue *poll_elem_queue(t_queue **queue);
void print_queue(t_queue *queue);

/*
 * ft_path.c
 */
t_path *new_elem_path(t_room *room);
void add_elem_path(t_path **path, t_room *room);
void add_elem_path_start(t_path **path, t_room *room);
void free_path(t_path **path);
t_path *get_path_to_end(t_room *room);
void	print_path(t_path *path);
void	print_pathes(t_list *pathes);
size_t	get_length_path(t_path *path);


/*
 * ft_map.c
 */
void	ft_map_clean(t_map **head);
void	ft_map_show(t_map *head);
void	ft_map_add(t_map **head, char *str);

/*
 * ft_is.c
 */
int		ft_isknowncommand(char *str);
int		ft_iscomment(const char *str);
int		ft_isants(char *str);
int		ft_isrooms(char *str);
int		ft_islinks(char *str);

/*
 * ft_parse.c
 */
int     ft_validate(t_room **head);
int		ft_parse(t_room **head, int *num_ant);

/*
 * ft_delete_elem.c
 */
int 	check_one_level(t_room *room, t_rooms *buf);
int 	check_less_level(t_room *room, t_rooms *buf);
int 	check_dead_end(t_room *room, t_rooms *buf);
int 	input_fork_delete(t_room *to_room, t_rooms *buf);
int 	not_equal_room(t_room *room, t_rooms *buf);
int		ft_delete_elem(t_rooms **list, t_room *r, int (*f)(t_room *room, t_rooms *buf));

/*
 * ft_room_union.c
 */
int 	is_in_union(t_room *room, t_room *check_room);
int		add_union(t_room *rooms, char *room1_name, char *room2_name);

/*
 * ft_room.c
 */
t_room	*new_room(char *name, int x, int y);
void	push_back_room(t_room **head, t_room *room);
void	free_rooms(t_room **rooms);
t_rooms *new_element_rooms(t_room *room);
void	free_rooms_list(t_rooms **list);
int 	list_contains(t_rooms *head, t_rooms *elem);
void	free_list(t_list **list);

/*
 * ft_room_funcs.c
 */
void	add_room_to_rooms_union(t_rooms **union_rooms, t_room *room);
void	add_room_to_rooms_union_back(t_rooms **rooms_union, t_room *room);
t_room *find_room_by_name(t_room *rooms, char *name);
t_room *find_room_by_signal(t_room *rooms, int signal);
t_room *find_room_by_coordinates(t_room *rooms, int x, int y);

/*
 * ft_count.c
 */
int 	count_elems_list(t_rooms *head);
void	count_input_links(t_room *room);
void count_all_input_output_links(t_room *rooms);

/*
 * ft_delete_forks.c
 */
t_rooms *get_input_links(t_room *room);
int 	check_output_fork(t_rooms *buf);
void	delete_input_forks(t_room *room);
void	delete_all_input_forks(t_room *rooms);
void	delete_output_forks(t_room *room);
void	delete_all_output_forks(t_room *rooms);

/*
 * ft_bfs_align_dead_ends.c
 */
void	bfs(t_room *rooms, t_queue *queue);
void	delete_useless_links(t_room* rooms);
t_rooms	*copy_links(t_rooms *links);
void	align_all_links(t_room *rooms);
int		delete_all_dead_ends(t_room *rooms);

/*
 * ft_get.c
 */
t_list	*get_names(t_room *rooms);
t_room *get_same_level(t_room *rooms, t_list **names, int level);
int 	get_highest_bfs_level(t_room *rooms);
t_room *get_start_room(t_room *rooms);
t_room *find_start_room(t_room *rooms);

/*
 * ft_path_funcs.c
 */
t_list	*get_pathes(t_room *room);
void 	free_pathes(t_list **pathes);
t_path *get_min_len_path(t_list *pathes);
size_t 	get_expr_pathes(t_list *pathes, t_list *path);
void	perform_pathes(t_list *pathes, int ants);

/*
 * ft_print_rooms.c
 */
void	print_list(t_room *list);


#endif //LEMIN_LEM_IN_H
