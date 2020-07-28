#include "lem-in.h"

static int 	ft_links_extension(t_map **map, t_room **head, char *buffer)
{
	char **parts;

	ft_map_add(map, ft_strdup(buffer));
	parts = ft_strsplit(buffer, '-');
	free(buffer);
	if (!find_room_by_name(*head, parts[0]) || !find_room_by_name(*head, parts[1])
	|| is_in_union(find_room_by_name(*head, parts[0]), find_room_by_name(*head, parts[1])))
	{
		ft_freesplit(parts);
		return (1);
	}
	add_union(*head, parts[0], parts[1]);
	ft_freesplit(parts);
	return (0);
}

static int  ft_links(t_map **map, t_room **head, char *buffer)
{
	if (ft_links_extension(map, head, buffer))
		return (0);
	while (get_next_line(0, &buffer) > 0)
		if (ft_iscomment(buffer))
		{
			free(buffer);
			continue;
		}
		else if (ft_islinks(buffer))
		{
			if (ft_links_extension(map, head, buffer))
				return (0);
		}
		else
		{
			free(buffer);
			return (0);
		}
	free(buffer);
	return (1);
}

static int	ft_rooms_extension(t_map **map, t_room **head, char *buffer, int signal)
{
	char	**parts;

	ft_map_add(map, ft_strdup(buffer));
	parts = ft_strsplit(buffer, ' ');
	free(buffer);
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
	ft_freesplit(parts);
	return (0);
}

static int  ft_rooms(t_map **map, t_room **head)
{
	char	*buffer;
	int		signal;

	signal = 0;
	while (get_next_line(0, &buffer) > 0)
		if (ft_isknowncommand(buffer) && !signal && (signal = ft_isknowncommand(buffer)))
		{
			ft_map_add(map, ft_strdup(buffer));
			free(buffer);
		}
		else if (ft_iscomment(buffer))
		{
			free(buffer);
			continue;
		}
		else if (ft_isrooms(buffer))
		{
			if (ft_rooms_extension(map, head, buffer, signal))
				return (0);
			signal = 0;
		}
		else if (ft_islinks(buffer) && !signal && find_room_by_signal(*head, START) && find_room_by_signal(*head, END))
			return (ft_links(map, head, buffer));																	
		else
		{
			free(buffer);
			return (0);
		}
	free(buffer);
	return (1);
}

static int  ft_ants(t_map **map)
{
	char	*buffer;
	int 	num_ants;

	while (get_next_line(0, &buffer) > 0)
		if (ft_iscomment(buffer))
		{
			free(buffer);
			continue;
		}
		else if (ft_isants(buffer))
		{
			ft_map_add(map, ft_strdup(buffer));
			num_ants = ft_atoi_pos(buffer);
			free(buffer);
			return (num_ants);
		}
		else
		{
			free(buffer);
			return (0);
		}
	free(buffer);
	return (0);
}

int	 		ft_parse(t_room **head, int *num_ants, t_map **map)
{
	*num_ants = ft_ants(map);
	if (*num_ants && ft_rooms(map, head)) // There is no reason for validation function anymore
		return (1);
	return (0);
}
