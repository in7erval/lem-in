//
// Created by Дмитрий Юдаков on 21.06.2020.
//

#ifndef LEMIN_LEM_IN_H
#define LEMIN_LEM_IN_H

#include "libft.h"
#include "ft_printf.h"

typedef struct s_rooms t_rooms;

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


t_room *get_start_room(t_room *rooms);
t_list	*get_pathes(t_room *room);

void add_elem_queue(t_queue **queue, t_room *room);
t_queue *new_queue_elem(t_room *room);
t_queue *poll_elem_queue(t_queue **queue);
void print_queue(t_queue *queue);

t_path *new_elem_path(t_room *room);
void add_elem_path(t_path **path, t_room *room);
void add_elem_path_start(t_path **path, t_room *room);
void free_path(t_path **path);
t_path *get_path_to_end(t_room *room);
void	print_path(t_path *path);
void	print_pathes(t_list *pathes);
size_t	get_length_path(t_path *path);



#endif //LEMIN_LEM_IN_H
