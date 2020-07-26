#include "lem-in.h"

static int		ft_commands(t_room **head)
{
	if (!find_room_by_signal(*head, START) || !find_room_by_signal(*head, END))
		return (0);
	return (1);
}

int				ft_validate(t_room **head)
{
	return (ft_commands(head));
}
