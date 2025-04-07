##
## EPITECH PROJECT, 2024
## lib-include
## File description:
## Makefile
##

CC      = gcc
CFLAGS  = -Wextra -Wall -Werror -W -g -I./include

SRC     =	main.c 							\
			src/utils/my_get_in_env.c 		\
			src/utils/my_parse_env.c 		\
			src/utils/my_gest_exec.c 		\
			src/utils/my_list_to_array.c 	\
			src/utils/my_envcpy.c 			\
			src/utils/my_get_curpath.c 		\
			src/utils/my_gest_commands.c 	\
			src/utils/parse.c 				\
			src/utils/handle_red.c 			\
			src/utils/handle_heredoc.c 		\
			src/commands/my_set_env.c 		\
			src/commands/my_unsetenv.c 		\
			src/commands/my_env.c 			\
			src/commands/my_print_prompt.c 	\
			src/commands/my_exit.c 			\
			src/commands/my_cd.c 			\
			src/commands/my_print_env.c 	\
			src/utils/update_pipe.c 		\
			src/utils/redirect.c 			\

OBJ     = $(SRC:.c=.o)

NAME    = 42sh

LIBMY   = lib/my/libmy.a

RM      = rm -f

# Couleurs pour les messages
DEFAULT := \e[0m
BOLD    := \e[1m
RED     := \e[91m
GREEN   := \e[92m
YELLOW  := \e[93m
BLUE    := \e[94m

all: force_rebuild_lib $(NAME)

force_rebuild_lib:
	@echo -e "$(YELLOW)Forcing rebuild of libmy...$(DEFAULT)"
	@$(MAKE) -C lib/my/ fclean
	@$(MAKE) -C lib/my/

$(LIBMY):
	@echo -e "$(YELLOW)Rebuilding libmy...$(DEFAULT)"
	@$(MAKE) -C lib/my/ fclean
	@$(MAKE) -C lib/my/

$(NAME): $(OBJ) $(LIBMY)
	@echo -e "$(GREEN)Building $(NAME)...$(DEFAULT)"
	@$(CC) -o $(NAME) $(OBJ) $(LIBMY) $(CFLAGS)

%.o: %.c
	@echo -e "$(BLUE)Compiling: $<$(DEFAULT)"
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@echo -e "$(RED)Cleaning object files...$(DEFAULT)"
	@$(RM) $(OBJ)

fclean: clean
	@$(MAKE) -C lib/my/ fclean
	@echo -e "$(RED)Removing $(NAME)...$(DEFAULT)"
	@$(RM) $(NAME)

re: fclean all

tests_run:
	@echo -e "$(RED)TEST $(NAME)...$(DEFAULT)"

.PHONY: all clean fclean re
