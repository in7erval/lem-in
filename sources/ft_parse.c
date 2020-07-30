#include "lem-in.h"

static int 	ft_links_extension(t_lemin *lemin, char *buffer)
{
	char	**parts;
	t_room	*room1;
	t_room	*room2;

	ft_map_add(&(lemin->map), ft_strdup(buffer));
	parts = ft_strsplit(buffer, '-');
	free(buffer);
	room1 = find_room_by_name(lemin->rooms, parts[0]);
	room2 = find_room_by_name(lemin->rooms, parts[1]);
	if (!room1 || !room2 || is_in_union(lemin, room1, room2))
	{
		ft_freesplit(parts);
		return (1);
	}
	add_union(lemin, parts[0], parts[1]);
	ft_freesplit(parts);
	return (0);
}

static int  ft_links(t_lemin *lemin, char *buffer)
{
	if (ft_links_extension(lemin, buffer))
		return (0);
	while (get_next_line(0, &buffer) > 0)
		if (ft_iscomment(buffer))
		{
			ft_map_add(&(lemin->map), ft_strdup(buffer));
			free(buffer);
			continue;
		}
		else if (ft_islinks(buffer))
		{
			if (ft_links_extension(lemin, buffer))
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

static int	ft_rooms_extension(t_lemin *lemin, char *buffer, int signal)
{
	char	**parts;
	t_room	*room;

	ft_clean_rooms(&buffer);
	ft_map_add(&(lemin->map), ft_strdup(buffer));
	parts = ft_strsplit(buffer, ' ');
	free(buffer);
	if (find_room_by_name(lemin->rooms, parts[0]) || find_room_by_coordinates(lemin->rooms, ft_atoi(parts[1]), ft_atoi(parts[2])))
	{
		ft_freesplit(parts);
		return (1);
	}
	room = new_room(ft_strdup(parts[0]), ft_atoi(parts[1]), ft_atoi(parts[2]));
	push_back_room(&(lemin->rooms), room);
	if (signal)
	{
		if (find_room_by_signal(lemin->rooms, signal))
		{
			ft_freesplit(parts);
			return (1);
		}
		room->status = signal;
		if (signal == START)
			lemin->start = room;
		if (signal == END)
			lemin->end = room;
	}
	ft_freesplit(parts);
	return (0);
}

static int  ft_rooms(t_lemin *lemin)
{
	char	*buffer;
	int		signal;

	signal = 0;
	while (get_next_line(0, &buffer) > 0)
		if (ft_isknowncommand(buffer) && !signal && (signal = ft_isknowncommand(buffer)))
		{
			ft_map_add(&(lemin->map), ft_strdup(buffer));
			free(buffer);
		}
		else if (ft_iscomment(buffer))
		{
			ft_map_add(&(lemin->map), ft_strdup(buffer));
			free(buffer);
			continue;
		}
		else if (ft_isrooms(buffer))
		{
			if (ft_rooms_extension(lemin, buffer, signal))
				return (0);
			signal = 0;
		}
		else if (ft_islinks(buffer) && !signal && lemin->start && lemin->end)
			return (ft_links(lemin, buffer));
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
			ft_map_add(map, ft_strdup(buffer));
			free(buffer);
			continue;
		}
		else if (ft_isants(buffer))
		{
			ft_clean_ants(&buffer);
			ft_map_add(map, ft_strdup(buffer));
			num_ants = ft_atoi(buffer);
			free(buffer);
			return (num_ants);
		}
		else
		{
			free(buffer);
			return (0);
		}
	free(buffer);
	ft_printf("12\n");
	return (0);
}

int	 		ft_parse(t_lemin *lemin)
{
	lemin->num_ants = ft_ants(&(lemin->map));
	if (lemin->num_ants && ft_rooms(lemin))
		return (1);
	return (0);
}
