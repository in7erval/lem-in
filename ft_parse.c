#include "lem-in.h"

/*
A room will never start with the character L nor the character #.
The rooms’ coordinates will always be integers.
Any unknown command will be ignored. (##)

*/

static int  ft_links(t_room **head)
{
	char	*buffer;
	char	**parts;

	while (get_next_line(0, &buffer) > 0)
	{
		if (ft_isknowncommand(buffer))
			return (0);
		else if (ft_iscomment(buffer))
			continue;
		else if (ft_islinks(buffer))
		{									// Найдена связь
				parts = ft_strsplit(buffer, '-');
				add_union(*head, ft_strdup(parts[0]), ft_strdup(parts[1]));
				ft_freesplit(parts);
		}
		else
			return (0);
	} 
	return (1);
}

static int  ft_rooms(t_room **head) //added ft_strdup for room name to free parts
{
	char	*buffer;
	char	**parts;
	int		signal;

	signal = 0;
	while (get_next_line(0, &buffer) > 0)
	{
		if (signal == 0)
			signal = ft_isknowncommand(buffer); //signal перезаписывался на сл строке после обозначения ##start или #end
		if (signal != 0)
			continue;							// Найден вход/выход
		else if (ft_iscomment(buffer))
			continue;
		else if (ft_isrooms(buffer))	
		{									// Найдена комната
				parts = ft_strsplit(buffer, ' ');
				push_back_room(head, new_room(ft_strdup(parts[0]), ft_atoi(parts[1]), ft_atoi(parts[2])));
				if (signal)
				{
					find_room_by_name(*head, parts[0])->status = signal;
					signal = 0;
				}
				ft_freesplit(parts);
		}
		else if (ft_islinks(buffer))
			return (1);
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
	if (ft_ants() && ft_rooms(head) && ft_links(head))
		return (1);
	return (0);
}
