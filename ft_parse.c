#include "lem-in.h"

static int  ft_links(t_map **map, t_room **head, char *buffer)		// Могут ли повторяться линки? - Походу не могут
{																	// Map must have no duplicates of links. There are no links that connect the same points.
	char	**parts;

	ft_map_add(map, ft_strdup(buffer));
	parts = ft_strsplit(buffer, '-');
	if (!find_room_by_name(*head, parts[0]) || !find_room_by_name(*head, parts[1]) || is_in_union(find_room_by_name(*head, parts[0]), find_room_by_name(*head, parts[1])))
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
		{
				ft_map_add(map, ft_strdup(buffer));
				parts = ft_strsplit(buffer, '-');
				if (!find_room_by_name(*head, parts[0]) || !find_room_by_name(*head, parts[1]) || is_in_union(find_room_by_name(*head, parts[0]), find_room_by_name(*head, parts[1])))
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

static int	ft_rooms_extension(t_map **map, t_room **head, char *buffer, int signal)
{
	char	**parts;

	ft_map_add(map, ft_strdup(buffer));
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

static int  ft_rooms(t_map **map, t_room **head)
{
	char	*buffer;
	char	**parts;
	int		signal;

	signal = 0;
	while (get_next_line(0, &buffer) > 0)
	{
		if (ft_isknowncommand(buffer) && !signal && (signal = ft_isknowncommand(buffer)))
			ft_map_add(map, ft_strdup(buffer));
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

static int  ft_ants(t_map **map)
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
			ft_map_add(map, ft_strdup(buffer));
			return (ft_atoi_pos(buffer));
		}
		else
			return (0);
	} 
	return (0);
}

int	 		ft_parse(t_room **head)
{
	t_map	*map;

	map = NULL;
	if (ft_ants(&map) && ft_rooms(&map, head) && ft_validate(head))
	{
		ft_map_show(map);
		free(map);
		return (1);
	}
	free(map);
	return (0);
}
