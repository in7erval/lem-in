#include "lem-in.h"

void perform_test(int num, t_room **rooms);

void ft_free_lemin(t_lemin *lemin)
{
	if (lemin)
	{
		if (lemin->map)
			ft_map_clean(&(lemin->map));
		if (lemin->rooms)
			free_rooms(&(lemin->rooms));
		if (lemin->pathes)
			free_pathes(&(lemin->pathes));
		if (lemin->links)
			free_links(&(lemin->links));
		free(lemin);
	}
}

int ft_free_error(t_lemin *lemin)
{
	ft_free_lemin(lemin);
	ft_putstr_fd("Error\n", 2);
	return (1);
}

void ft_beautify_rooms(t_lemin *lemin)
{
	delete_useless_links(lemin);
	//print_lemin(lemin, "AFTER DELETE_USELESS_LINKS:");

	align_all_links(lemin);
	count_all_input_output_links(lemin);
	//print_lemin(lemin, "AFTER ALIGN AND COUNT LINKS:");

	delete_all_dead_ends(lemin);
	//print_lemin(lemin, "AFTER DELETE_DEAD_ENDS:");

	delete_all_input_forks(lemin);
	//print_lemin(lemin, "AFTER DELETE_INPUT_FORKS");
	delete_all_output_forks(lemin);
	//print_lemin(lemin, "AFTER DELETE_OUTPUT_FORKS");

}

void	ft_bonus(int argc, char **argv, int *c_bonus, int *p_bonus)
{
	if (argc == 2 && !ft_strcmp(argv[1], "-c"))
		*c_bonus = 1;
	else if (argc == 2 && !ft_strcmp(argv[1], "-p"))
		*p_bonus = 1;
	else if ((argc == 2 && (!ft_strcmp(argv[1], "-cp") || !ft_strcmp(argv[1], "-pc"))) ||
		(argc == 3 && ((!ft_strcmp(argv[1], "-c") && !ft_strcmp(argv[2], "-p"))
		|| (!ft_strcmp(argv[1], "-p") && !ft_strcmp(argv[2], "-c")))))
	{
		*c_bonus = 1;
		*p_bonus = 1;
	}
}

int main(int argc, char **argv)
{
	t_lemin		*lemin;
	int			c_bonus;
	int 		p_bonus;

	lemin = init_lemin();
	c_bonus = 0;
	p_bonus = 0;
	ft_bonus(argc, argv, &c_bonus, &p_bonus);
	if (!ft_parse(lemin, c_bonus))
		return (ft_free_error(lemin));
	if (ft_markup_bfs(lemin))
		return (ft_free_error(lemin));
	ft_beautify_rooms(lemin);
	lemin->pathes = sort_pathes(get_pathes(lemin, lemin->start));
	if (!(lemin->pathes))
		return (ft_free_error(lemin));
	ft_map_show(lemin->map);
	ft_printf("\n");
	if (p_bonus)
		print_pathes(lemin->pathes);
	perform_pathes(lemin);
	ft_free_lemin(lemin);
	return (0);
}
/*
void	perform_test(int num, t_lemin *lemin)
{
	if (num == 1)
	{
		push_back_room(lemin->rooms, new_room("room_0", 10, 0));
		push_back_room(rooms, new_room("room_1", 10, 0));
		push_back_room(rooms, new_room("room_2", 10, 0));
		push_back_room(rooms, new_room("room_3", 10, 0));
		push_back_room(rooms, new_room("room_4", 10, 0));
		push_back_room(rooms, new_room("room_5", 10, 0));
		find_room_by_name(*rooms, "room_0")->status = START;
		find_room_by_name(*rooms, "room_5")->status = END;
		add_union(*rooms, "room_0", "room_1");
		add_union(*rooms, "room_0", "room_2");
		add_union(*rooms, "room_0", "room_3");
		add_union(*rooms, "room_2", "room_1");
		add_union(*rooms, "room_2", "room_3");
		add_union(*rooms, "room_4", "room_1");
		add_union(*rooms, "room_3", "room_4");
		add_union(*rooms, "room_2", "room_4");
		add_union(*rooms, "room_4", "room_5");
	}
	if (num == 2)
	{
		push_back_room(rooms, new_room("room_0", 10, 0));
		push_back_room(rooms, new_room("room_1", 10, 5));
		push_back_room(rooms, new_room("room_2", 15, 5));
		push_back_room(rooms, new_room("room_3", 5, 10));
		push_back_room(rooms, new_room("room_4", 10, 10));
		push_back_room(rooms, new_room("room_5", 20, 10));
		push_back_room(rooms, new_room("room_6", 0, 15));
		push_back_room(rooms, new_room("room_7", 5, 17));
		push_back_room(rooms, new_room("room_8", 0, 20));
		push_back_room(rooms, new_room("room_9", 10, 25));
		push_back_room(rooms, new_room("room_10", 15, 25));
		find_room_by_name(*rooms, "room_0")->status = START;
		find_room_by_name(*rooms, "room_9")->status = END;
		add_union(*rooms, "room_0", "room_1");
		add_union(*rooms, "room_0", "room_2");
		add_union(*rooms, "room_2", "room_5");
		add_union(*rooms, "room_2", "room_4");
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_1", "room_4");
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_4", "room_3");
		add_union(*rooms, "room_3", "room_6");
		add_union(*rooms, "room_3", "room_7");
		add_union(*rooms, "room_4", "room_9");
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_6", "room_8");
		add_union(*rooms, "room_8", "room_9");
		add_union(*rooms, "room_7", "room_9");
		add_union(*rooms, "room_9", "room_10");
	}
	if (num == 3)
	{
		push_back_room(rooms, new_room("room_1", 10, 5));
		push_back_room(rooms, new_room("room_2", 15, 5));
		push_back_room(rooms, new_room("room_3", 5, 10));
		push_back_room(rooms, new_room("room_4", 10, 10));
		push_back_room(rooms, new_room("room_5", 20, 10));
		push_back_room(rooms, new_room("room_6", 0, 15));
		push_back_room(rooms, new_room("room_7", 5, 17));
		find_room_by_name(*rooms, "room_1")->status = START;
		find_room_by_name(*rooms, "room_7")->status = END;
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_1", "room_6");
		add_union(*rooms, "room_1", "room_4");
		add_union(*rooms, "room_2", "room_3");
		add_union(*rooms, "room_2", "room_4");
		add_union(*rooms, "room_4", "room_6");
		add_union(*rooms, "room_2", "room_5");
		add_union(*rooms, "room_6", "room_5");
		add_union(*rooms, "room_6", "room_7");
	}
	if (num == 4)
	{
		push_back_room(rooms, new_room("room_1", 10, 5));
		push_back_room(rooms, new_room("room_2", 15, 5));
		push_back_room(rooms, new_room("room_3", 5, 10));
		push_back_room(rooms, new_room("room_4", 10, 10));
		push_back_room(rooms, new_room("room_5", 20, 10));
		push_back_room(rooms, new_room("room_6", 0, 15));
		find_room_by_name(*rooms, "room_1")->status = START;
		find_room_by_name(*rooms, "room_6")->status = END;
		add_union(*rooms, "room_1", "room_2");
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_2", "room_3");
		add_union(*rooms, "room_2", "room_4");
		add_union(*rooms, "room_4", "room_5");
		add_union(*rooms, "room_5", "room_6");
	}
	if (num == 5)
	{
		push_back_room(rooms, new_room("room_1", 10, 5));
		push_back_room(rooms, new_room("room_2", 15, 5));
		push_back_room(rooms, new_room("room_3", 5, 10));
		push_back_room(rooms, new_room("room_4", 10, 10));
		push_back_room(rooms, new_room("room_5", 20, 10));
		push_back_room(rooms, new_room("room_6", 0, 15));
		push_back_room(rooms, new_room("room_7", 5, 17));
		push_back_room(rooms, new_room("room_8", 0, 20));
		push_back_room(rooms, new_room("room_9", 10, 25));
		push_back_room(rooms, new_room("room_10", 15, 25));
		push_back_room(rooms, new_room("room_11", 15, 25));
		push_back_room(rooms, new_room("room_12", 15, 25));
		push_back_room(rooms, new_room("room_13", 15, 25));
		find_room_by_name(*rooms, "room_1")->status = START;
		find_room_by_name(*rooms, "room_13")->status = END;
		add_union(*rooms, "room_1", "room_2");
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_2", "room_3");
		add_union(*rooms, "room_2", "room_4");
		add_union(*rooms, "room_3", "room_6");
		add_union(*rooms, "room_4", "room_6");
		add_union(*rooms, "room_1", "room_5");
		add_union(*rooms, "room_4", "room_7");
		add_union(*rooms, "room_6", "room_8");
		add_union(*rooms, "room_7", "room_5");
		add_union(*rooms, "room_5", "room_8");
		add_union(*rooms, "room_5", "room_9");
		add_union(*rooms, "room_9", "room_10");
		add_union(*rooms, "room_9", "room_11");
		add_union(*rooms, "room_10", "room_12");
		add_union(*rooms, "room_11", "room_12");
		add_union(*rooms, "room_12", "room_13");
	}
	if (num == 6)
	{
		push_back_room(rooms, new_room("room_1", 10, 5));
		push_back_room(rooms, new_room("room_2", 15, 5));
		push_back_room(rooms, new_room("room_3", 5, 10));
		push_back_room(rooms, new_room("room_4", 10, 10));
		push_back_room(rooms, new_room("room_5", 20, 10));
		push_back_room(rooms, new_room("room_6", 0, 15));
		push_back_room(rooms, new_room("room_7", 0, 15));
		push_back_room(rooms, new_room("room_8", 0, 15));
		push_back_room(rooms, new_room("room_9", 0, 15));
		find_room_by_name(*rooms, "room_1")->status = START;
		find_room_by_name(*rooms, "room_6")->status = END;
		add_union(*rooms, "room_1", "room_2");
		add_union(*rooms, "room_1", "room_4");
		add_union(*rooms, "room_2", "room_3");
		add_union(*rooms, "room_3", "room_6");
		add_union(*rooms, "room_4", "room_5");
		add_union(*rooms, "room_5", "room_7");
		add_union(*rooms, "room_7", "room_8");
		add_union(*rooms, "room_8", "room_9");
		add_union(*rooms, "room_9", "room_6");
	}
	if (num == 7)
	{
		push_back_room(rooms, new_room("room_0", 10, 5));
		push_back_room(rooms, new_room("room_1", 10, 5));
		push_back_room(rooms, new_room("room_2", 15, 5));
		push_back_room(rooms, new_room("room_3", 5, 10));
		push_back_room(rooms, new_room("room_4", 10, 10));
		push_back_room(rooms, new_room("room_5", 20, 10));
		push_back_room(rooms, new_room("room_6", 0, 15));
		push_back_room(rooms, new_room("room_7", 5, 17));
		find_room_by_name(*rooms, "room_1")->status = START;
		find_room_by_name(*rooms, "room_0")->status = END;
		add_union(*rooms, "room_0", "room_6");
		add_union(*rooms, "room_0", "room_4");
		add_union(*rooms, "room_1", "room_2");
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_2", "room_7");
		add_union(*rooms, "room_2", "room_1");
		add_union(*rooms, "room_2", "room_5");
		add_union(*rooms, "room_3", "room_5");
		add_union(*rooms, "room_3", "room_1");
		add_union(*rooms, "room_4", "room_3");
		add_union(*rooms, "room_4", "room_2");
		add_union(*rooms, "room_5", "room_3");
		add_union(*rooms, "room_5", "room_2");
		add_union(*rooms, "room_5", "room_6");
		add_union(*rooms, "room_6", "room_5");
		add_union(*rooms, "room_6", "room_7");
		add_union(*rooms, "room_7", "room_6");
		add_union(*rooms, "room_7", "room_2");
		add_union(*rooms, "room_7", "room_4");
		add_union(*rooms, "room_7", "room_6");
		add_union(*rooms, "room_7", "room_2");
		add_union(*rooms, "room_7", "room_4");
	}
	if (num == 8)
	{
		push_back_room(rooms, new_room("start", 10, 5));
		push_back_room(rooms, new_room("end", 10, 5));
		push_back_room(rooms, new_room("3", 15, 5));
		push_back_room(rooms, new_room("4", 5, 10));
		push_back_room(rooms, new_room("1", 10, 10));
		push_back_room(rooms, new_room("2", 15, 5));
		push_back_room(rooms, new_room("5", 5, 10));
		push_back_room(rooms, new_room("6", 10, 10));
		find_room_by_name(*rooms, "start")->status = START;
		find_room_by_name(*rooms, "end")->status = END;
		add_union(*rooms, "start", "1");
		add_union(*rooms, "3", "4");
		add_union(*rooms, "2", "4");
		add_union(*rooms, "1", "5");
		add_union(*rooms, "6", "5");
		add_union(*rooms, "end", "6");
		add_union(*rooms, "1", "2");
		add_union(*rooms, "2", "end");
		add_union(*rooms, "3", "start");
	}
	if (num == 9)
	{
		push_back_room(rooms, new_room("room_0", 10, 5));
		push_back_room(rooms, new_room("room_1", 10, 5));
		push_back_room(rooms, new_room("room_2", 15, 5));
		push_back_room(rooms, new_room("room_3", 5, 10));
		push_back_room(rooms, new_room("room_4", 10, 10));
		push_back_room(rooms, new_room("room_5", 20, 10));
		push_back_room(rooms, new_room("room_6", 0, 15));
		find_room_by_name(*rooms, "room_0")->status = START;
		find_room_by_name(*rooms, "room_6")->status = END;
		add_union(*rooms, "room_0", "room_1");
		add_union(*rooms, "room_0", "room_2");
		add_union(*rooms, "room_1", "room_3");
		add_union(*rooms, "room_2", "room_3");
		add_union(*rooms, "room_3", "room_4");
		add_union(*rooms, "room_3", "room_5");
		add_union(*rooms, "room_4", "room_6");
		add_union(*rooms, "room_5", "room_6");
	}
}
*/