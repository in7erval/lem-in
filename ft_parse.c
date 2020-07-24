#include "lem-in.h"

/*
A room will never start with the character L nor the character #.
The rooms’ coordinates will always be integers.
Any unknown command will be ignored. (##)

*/

static int  ft_links(t_room **head, char *buffer)
{
	char	**parts;

	parts = ft_strsplit(buffer, '-');							//	В buffer прошлая строка
	if (is_in_union(find_room_by_name(*head, parts[0]), find_room_by_name(*head, parts[1])))
	{
		ft_freesplit(parts);
		return (0);
	}
	add_union(*head, ft_strdup(parts[0]), ft_strdup(parts[1]));
	ft_freesplit(parts);
	while (get_next_line(0, &buffer) > 0)
	{
		if (ft_isknowncommand(buffer))
			return (0);
		else if (ft_iscomment(buffer))
			continue;
		else if (ft_islinks(buffer))
		{									// Найдена связь
				parts = ft_strsplit(buffer, '-');
				if (is_in_union(find_room_by_name(*head, parts[0]), find_room_by_name(*head, parts[1])))
				{
					ft_freesplit(parts);
					return (0);
				}
				add_union(*head, ft_strdup(parts[0]), ft_strdup(parts[1]));
				ft_freesplit(parts);
		}
		else
			return (0);
	} 
	return (1);
}

static int  ft_rooms(t_room **head)
{
	char	*buffer;
	char	**parts;
	int		signal;

	signal = 0;
	while (get_next_line(0, &buffer) > 0)
	{
		/*if (signal == 0)
			signal = ft_isknowncommand(buffer); //signal перезаписывался на сл строке после обозначения ##start или #end
		if (signal != 0)
			continue;											*/

		if (ft_isknowncommand(buffer) && !signal)				// 
			signal = ft_isknowncommand(buffer);					//	Этого должно быть достаточно
		else if (ft_isknowncommand(buffer))						//
			return (0);											//
		else if (ft_iscomment(buffer))
			continue;
		else if (ft_isrooms(buffer))	
		{									// Найдена комната
				parts = ft_strsplit(buffer, ' ');
				if (find_room_by_name(*head, parts[0]) || find_room_by_coordinates(*head, ft_atoi(parts[1]), ft_atoi(parts[2])))
				{
					ft_freesplit(parts);
					return (0);
				}
				push_back_room(head, new_room(ft_strdup(parts[0]), ft_atoi(parts[1]), ft_atoi(parts[2])));
				if (signal)
				{
					if (find_room_by_signal(*head, signal))
					{
						ft_freesplit(parts);
						return (0);
					}
					find_room_by_name(*head, parts[0])->status = signal;
				}
				signal = 0;
				ft_freesplit(parts);
		}
		else if (ft_islinks(buffer) && signal)																	//
			return (0);																							//	Можно упростить
		else if (ft_islinks(buffer) && find_room_by_signal(*head, START) && find_room_by_signal(*head, END))	//
			return (ft_links(head, buffer));																	//
		else
			return (0);
	} 
	return (1);
}

static int  ft_ants()
{
	char	*buffer;

	while (get_next_line(0, &buffer) > 0)
	{
		if (ft_isknowncommand(buffer))
			return (0);
		else if (ft_iscomment(buffer))
			continue;
		else if (ft_isants(buffer))
			return (ft_atoi_pos(buffer));		// Найдено число муравьев
		else
			return (0);
	} 
	return (0);
}

int	 		ft_parse(t_room **head)
{
	if (ft_ants() && ft_rooms(head))
		return (1);
	return (0);
}
