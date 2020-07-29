#include "lem-in.h"

void perform_test(int num, t_room **rooms);

int ft_clean_error(t_room **rooms, t_map **map)
{
	ft_map_clean(map);
	free_rooms(rooms);
	ft_putstr_fd("Error\n", 2);
	return (1);
}

int ft_markup_rooms(t_room *rooms)
{
	t_queue *queue;
	t_room *start_room;

	start_room = find_room_by_signal(rooms, START);
	queue = NULL;
	add_elem_queue(&queue, start_room);
	start_room->bfs_level = 0;
	bfs(rooms, queue);
	if (find_room_by_signal(rooms, END)->status == -1) //no path
		return (1);
	return (0);
}

void ft_beautify_rooms(t_room *rooms)
{
	delete_useless_links(rooms);
	//print_list(rooms, "AFTER DELETE_USELESS_LINKS:");
	align_all_links(rooms);
	count_all_input_output_links(rooms);
	//print_list(rooms, "AFTER ALIGN AND COUNT LINKS:");
	delete_all_dead_ends(rooms);
	//print_list(rooms, "AFTER DELETE_DEAD_ENDS:");
	delete_all_input_forks(rooms);
	count_all_input_output_links(rooms);
	delete_all_dead_ends(rooms);
	//print_list(rooms, "AFTER DELETE_INPUT_FORKS");
	delete_all_output_forks(rooms);
	count_all_input_output_links(rooms);
	//print_list(rooms, "AFTER DELETE_OUTPUT_FORKS");
}

int main()
{
	t_room	*rooms;
	t_list	*pathes;
	int 	num_ants;
	t_map	*map;

	map = NULL;
	rooms = NULL;
	num_ants = 0;
	if (!ft_parse(&rooms, &num_ants, &map))
		return (ft_clean_error(&rooms, &map));

	//perform_test(8 , &rooms);
	//print_list(rooms, "BEGINNING");
	if (ft_markup_rooms(rooms))
		return (ft_clean_error(&rooms, &map));
	//print_list(rooms, "AFTER MARKUP:");
	ft_beautify_rooms(rooms);
	pathes = sort_pathes(get_pathes(find_room_by_signal(rooms, START)));
	if (!pathes)									// No path checking
		return (ft_clean_error(&rooms, &map));
	ft_map_show(map);
	//print_pathes(pathes);
	ft_printf("\n");
	perform_pathes(pathes, num_ants);
	free_pathes(&pathes);
	free_rooms(&rooms);
	return 0;
}

void	perform_test(int num, t_room **rooms)
{
	if (num == 1)
	{
		push_back_room(rooms, new_room("room_0", 10, 0));
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
