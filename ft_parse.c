#include "lem-in.h"

/*
A room will never start with the character L nor the character #.
The rooms’ coordinates will always be integers.
Any unknown command will be ignored. (##)

*/

static int  ft_links(char **map, t_room **head, char *buffer)		// Могут ли повторяться линки?
{
	char	**parts;

	parts = ft_strsplit(buffer, '-');
	/*if (is_in_union(find_room_by_name(*head, parts[0]), find_room_by_name(*head, parts[1])))
	{
		ft_freesplit(parts);
		return (0);
	}*/
	add_union(*head, ft_strdup(parts[0]), ft_strdup(parts[1]));
	ft_freesplit(parts);
	while (get_next_line(0, &buffer) > 0)
	{
		if (ft_isknowncommand(buffer))
			return (0);
		else if (ft_iscomment(buffer))
			continue;
		else if (ft_islinks(buffer))
		{
				*map = ft_stradd(*map, ft_strcat(buffer, "\n"));
				parts = ft_strsplit(buffer, '-');
				/*if (is_in_union(find_room_by_name(*head, parts[0]), find_room_by_name(*head, parts[1])))
				{
					ft_freesplit(parts);
					return (0);
				}*/
				add_union(*head, ft_strdup(parts[0]), ft_strdup(parts[1]));
				ft_freesplit(parts);
		}
		else
			return (0);
	} 
	return (1);
}

static int	ft_rooms_extension(char **map, t_room **head, char *buffer, int signal)
{
	char	**parts;

	*map = ft_stradd(*map, ft_strcat(buffer, "\n"));
	parts = ft_strsplit(buffer, ' ');
	if (find_room_by_name(*head, parts[0]) || find_room_by_coordinates(*head, ft_atoi(parts[1]), ft_atoi(parts[2])))
	{
		ft_freesplit(parts);
		return (1);
	}
	push_back_room(head, new_room(ft_strdup(parts[0]), ft_atoi(parts[1]), ft_atoi(parts[2])));
	if (signal)
	{
		if (find_room_by_signal(*head, signal))
		{
			ft_freesplit(parts);
			return (1);
		}
		find_room_by_name(*head, parts[0])->status = signal;
	}
	signal = 0;
	ft_freesplit(parts);
	return (0);
}

static int  ft_rooms(char **map, t_room **head)
{
	char	*buffer;
	char	**parts;
	int		signal;

	signal = 0;
	while (get_next_line(0, &buffer) > 0)
	{
		if (ft_isknowncommand(buffer) && !signal && (signal = ft_isknowncommand(buffer)))
			*map = ft_stradd(*map, ft_strcat(buffer, "\n"));
		else if (ft_isknowncommand(buffer))						
			return (0);										
		else if (ft_iscomment(buffer))
			continue;
		else if (ft_isrooms(buffer))	
		{
			if ((signal = ft_rooms_extension(map, head, buffer, signal)))
				return (0);
		}																		
		else if (ft_islinks(buffer) && !signal && find_room_by_signal(*head, START) && find_room_by_signal(*head, END))	
			return (ft_links(map, head, buffer));																	
		else
			return (0);
	} 
	return (1);
}

static int  ft_ants(char **map)
{
	char	*buffer;

	while (get_next_line(0, &buffer) > 0)
	{
		if (ft_isknowncommand(buffer))
			return (0);
		else if (ft_iscomment(buffer))
			continue;
		else if (ft_isants(buffer))
		{
			*map = ft_stradd(*map, ft_strcat(buffer, "\n"));
			return (ft_atoi_pos(buffer));
		}
		else
			return (0);
	} 
	return (0);
}

int	 		ft_parse(t_room **head)
{
	char	*map;

	map = (char*)malloc(sizeof(char));
	if (ft_ants(&map) && ft_rooms(&map, head) && ft_validate(head))
	{
		ft_printf("%s\n", map);
		free(map);
		return (1);
	}
	free(map);
	return (0);
}
