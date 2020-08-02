.PHONY: all clean fclean re

NAME = lem-in
# NAME_CHECKER_VISUAL = checker_visual
CC = gcc
FLAGS = -Wall -Werror -Wextra -O3 -g
LIBRARIES = -lft -L$(LIBFT_DIRECTORY)
# LIBRARIES_X = -lmlx -L$(MINILIBX_DIRECTORY) -framework OpenGL -framework AppKit

INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) # -I$(MINILIBX_HEADERS)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

# MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
# MINILIBX_DIRECTORY = ./minilibx_macos/
# MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

HEADERS_LIST = lem_in.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))



SOURCES_DIRECTORY = ./sources/

SOURCES_LEMIN_LIST = main.c ft_queue.c ft_path.c ft_is.c ft_parse.c ft_parse_links.c ft_map.c \
					ft_bfs_align_dead_ends.c ft_count.c ft_delete_links.c ft_for_delete_links.c ft_delete_forks.c \
					ft_path_funcs.c ft_room.c ft_room_funcs.c \
					ft_room_union.c ft_ant.c ft_cleaner.c utils.c ft_link.c ft_init.c ft_markup_bfs.c \
					ft_perform_pathes.c ft_sort_pathes.c ft_parse_rooms.c ft_path_print.c
# SOURCES_CHECKER_LIST = checker.c
# SOURCES_CHECKER_VISUAL_LIST = checker_visual.c drawing.c drawing_help.c drawing_help_2.c drawing_put_color.c
# SOURCES_LIST = help.c solve.c operations.c checker_helper.c help_2.c help_init.c help_stack.c help_stack_2.c \
# 				solve_indexes.c solve_markup.c solve_opers.c solve_help.c

SOURCES_LEMIN = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LEMIN_LIST))
# SOURCES_CHECKER = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_CHECKER_LIST))
# SOURCES_CHECKER_VISUAL = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_CHECKER_VISUAL_LIST))
# SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))


OBJECTS_DIRECTORY = objects/
OBJECTS_LEMIN_LIST = $(patsubst %.c, %.o, $(SOURCES_LEMIN_LIST))
OBJECTS_LEMIN	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LEMIN_LIST))
# OBJECTS_CHECKER_LIST = $(patsubst %.c, %.o, $(SOURCES_CHECKER_LIST))
# OBJECTS_CHECKER	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_CHECKER_LIST))
# OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
# OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))
# OBJECTS_CHECKER_VISUAL_LIST = $(patsubst %.c, %.o, $(SOURCES_CHECKER_VISUAL_LIST))
# OBJECTS_CHECKER_VISUAL	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_CHECKER_VISUAL_LIST))

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

# visual: $(NAME_CHECKER_VISUAL) $(NAME)
# 	@echo "$(BOLD_RED) Visual ready! $(RESET)"

$(NAME): $(LIBFT) $(OBJECTS_DIRECTORY) $(CREATE_HEADERS_DIRECTORY) $(OBJECTS) $(OBJECTS_LEMIN)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS_LEMIN) -o $(NAME)
	@echo "$(BOLD_CYAN)$(NAME) $(GREEN)is compiled$(RESET)"

# $(NAME_CHECKER): $(LIBFT) $(OBJECTS_DIRECTORY) $(CREATE_HEADERS_DIRECTORY) $(OBJECTS) $(OBJECTS_CHECKER)
# 	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) $(OBJECTS_CHECKER) -o $(NAME_CHECKER)
# 	@echo "$(BOLD_CYAN)checker $(GREEN)is compiled$(RESET)"

# $(NAME_CHECKER_VISUAL): $(MINILIBX) $(LIBFT) $(OBJECTS_DIRECTORY) $(OBJECTS) $(OBJECTS_CHECKER_VISUAL)
# 	@$(CC) $(FLAGS) $(LIBRARIES) $(LIBRARIES_X) $(INCLUDES) $(OBJECTS) $(OBJECTS_CHECKER_VISUAL) -o $(NAME_CHECKER_VISUAL)
# 	@echo "$(BOLD_CYAN)checker_visual $(GREEN)is compiled$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@echo "$(MAGENTA)Creating object file $(CYAN)$<$(RESET) $(MAGENTA)in $(OBJECTS_DIRECTORY)$(RESET)"
	@$(CC) $(FLAGS) -c $(INCLUDES)  $< -o $@

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)

$(LIBFT):
	@cd $(LIBFT_DIRECTORY) && $(MAKE) -s

# $(MINILIBX):
# 	@echo "$(BOLD_YELLOW)Creating $(MINILIBX)...$(RESET)"
#	@$(MAKE) -sC $(MINILIBX_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
#	@$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(GREEN)object files $(RED)deleted$(RESET)"
	@echo "$(GREEN)$(OBJECTS_DIRECTORY) $(RED)deleted$(RESET)"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(GREEN)$(LIBFT) $(RED)deleted$(RESET)"
#	@rm -f $(MINILIBX)
#	@echo "$(GREEN)$(MINILIBX) $(RED)deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(NAME) $(RED)deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
