#include "lem-in.h"

void perform_test(int num, t_room **rooms);

int main()
{
	t_room *rooms;
	t_list	*pathes;
	int 	num_ants;

	rooms = NULL;
	num_ants = 0;
	if (ft_parse(&rooms, &num_ants))
		ft_printf("\nTrue\n");
	else
	{
		free_rooms(&rooms);
		ft_printf("\nError\n");
		return (0);
	}
	//free_rooms(&rooms);
	//return (0);
	//perform_test(8 , &rooms);

	t_queue *queue;
	t_room *start_room;

	print_list(rooms);
	start_room = find_start_room(rooms);
	/*if (start_room == NULL) {								//
		ft_printf("%s\n", "start_room doesn't exist!");		//	Проверяется в парсере
		return (0);											//
	}*/
	ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
	queue = NULL;
	add_elem_queue(&queue, start_room);
	start_room->bfs_level = 0;
	bfs(rooms, queue);
	print_list(rooms);
	ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
	delete_useless_links(rooms);
	if (1)
	{
		ft_printf("\nAFTER DELETE_USELESS_LINKS:\n");
		ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
		print_list(rooms);
	}

	align_all_links(rooms);
	count_all_input_output_links(rooms);
	if (1)
	{
		ft_printf("\nAFTER ALIGN AND COUNT LINKS:\n");
		ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
		print_list(rooms);
	}

	while (delete_all_dead_ends(rooms) == 1)
		count_all_input_output_links(rooms);
	if (1)
	{
		ft_printf("\nAFTER DELETE_DEAD_ENDS:\n");
		ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
		print_list(rooms);
	}


	delete_all_input_forks(rooms);
	count_all_input_output_links(rooms);
	while (delete_all_dead_ends(rooms) == 1)
		count_all_input_output_links(rooms);
	if (1)
	{
		ft_printf("\nAFTER DELETE_INPUT_FORKS\n");
		ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
		print_list(rooms);
	}

	delete_all_output_forks(rooms);
	count_all_input_output_links(rooms);
	if (1)
	{
		ft_printf("\nAFTER DELETE_OUTPUT_FORKS\n");
		ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
		print_list(rooms);
	}

	if (1)
	{
		ft_printf("\nPATHES FROM START TO END\n");
		ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
	}
	pathes = get_pathes(get_start_room(rooms));
	if (!pathes)									// No path checking
	{
		ft_printf("\nError\n");
		free_rooms(&rooms);
	return 0;
		
	}
	print_pathes(pathes);

	if (0)
	{
		ft_printf("\nPERFORM PATHES\n");
		ft_printf("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
		perform_pathes(pathes, 20);
	}
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
