.PHONY: all clean fclean re

NAME = lem-in
CC = gcc
FLAGS = -Wall -Werror -Wextra -O3 -g
LIBRARIES = -lft -L$(LIBFT_DIRECTORY)

INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

HEADERS_LIST = lem_in.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))



SOURCES_DIRECTORY = ./sources/

SOURCES_LEMIN_LIST = main.c  ft_path.c ft_path_funcs.c \
					ft_is.c ft_parse.c ft_parse_links.c \
					ft_map.c ft_usage.c ft_bft.c \
					ft_room.c ft_room_funcs.c ft_extend_nodes.c \
					ft_room_union.c ft_cleaner.c \
					utils.c ft_init.c ft_solve.c \
					ft_sort_pathes.c ft_parse_rooms.c ft_path_print.c \
					ft_print_lemin.c ft_tree.c ft_group.c \
					ft_perform_ants.c ft_solve_utils.c ft_array.c \
					ft_perform_paths.c ft_answer.c ft_optimize.c \


SOURCES_LEMIN = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LEMIN_LIST))


OBJECTS_DIRECTORY = objects/
OBJECTS_LEMIN_LIST = $(patsubst %.c, %.o, $(SOURCES_LEMIN_LIST))
OBJECTS_LEMIN	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LEMIN_LIST))

# COLORS
GREEN = \033[0;32m
BOLD_GREEN = \033[1;32m
RED = \033[0;31m
BOLD_RED = \033[1;31m
YELLOW = \033[0;33m
BOLD_YELLOW = \033[1;33m
BLUE = \033[0;34m
BOLD_BLUE = \033[1;34m
MAGENTA = \033[0;35m
BOLD_MAGENTA = \033[1;35m
CYAN = \033[0;36m
BOLD_CYAN = \033[1;36m
RESET = \033[0m


all: $(NAME)
	@echo "$(BOLD_RED) Ready! $(RESET)"

$(NAME): $(LIBFT) $(OBJECTS_DIRECTORY) $(CREATE_HEADERS_DIRECTORY) $(OBJECTS) $(OBJECTS_LEMIN)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS_LEMIN) -o $(NAME)
	@echo "$(BOLD_CYAN)$(NAME) $(GREEN)is compiled$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@echo "$(MAGENTA)Creating object file $(CYAN)$<$(RESET) $(MAGENTA)in $(OBJECTS_DIRECTORY)$(RESET)"
	@$(CC) $(FLAGS) -c $(INCLUDES)  $< -o $@

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)

$(LIBFT):
	@cd $(LIBFT_DIRECTORY) && $(MAKE) -s

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(GREEN)object files $(RED)deleted$(RESET)"
	@echo "$(GREEN)$(OBJECTS_DIRECTORY) $(RED)deleted$(RESET)"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(GREEN)$(LIBFT) $(RED)deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(NAME) $(RED)deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
