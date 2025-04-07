##
## EPITECH PROJECT, 2024
## makefile
## File description:
## task 01
##

# DIRECTORIES
OBJ_DIR = obj

# FILES
SRC = 	lib/my_strchr.c 					    \
		lib/my_strcmp.c 						\
		lib/my_strdup.c 						\
		lib/my_strlen.c 						\
		lib/my_str_to_word_array_sep.c 			\
		lib/my_strcpy.c 						\
		lib/my_strcat.c 						\
		lib/my_get_nbr.c 						\
		lib/my_putstr.c 						\
		lib/my_put_nbr.c 						\
		lib/my_putchar.c 						\
		lib/mini_printf.c						\
		lib/my_printerr.c						\
		lib/linked_list.c 						\
		src/commands/my_cd.c 					\
		src/commands/my_env.c 					\
		src/commands/my_exit.c 					\
		src/commands/my_print_env.c 			\
		src/commands/my_print_prompt.c 			\
		src/commands/my_set_env.c 				\
		src/commands/my_unsetenv.c 				\
		src/utils/handle_heredoc.c 				\
		src/utils/handle_red.c 					\
		src/utils/my_envcpy.c 					\
		src/utils/my_gest_commands.c 			\
		src/utils/my_gest_exec.c 				\
		src/utils/my_get_curpath.c 				\
		src/utils/my_get_in_env.c 				\
		src/utils/my_list_to_array.c 			\
		src/utils/my_parse_env.c 				\
		src/utils/parse.c 						\
		src/utils/redirect.c 					\
		src/utils/update_pipe.c 				\
		src/main.c

# COLORS
RED=\033[31m
GREEN=\033[32m
WHITE=\033[37m
BOLD=\033[1m
RESET=\033[0m

# VARIABLES
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
FLAGS = -Wextra -Wall -W -Werror -I include
CC = gcc
NAME = 42sh

# PRINT COMPILATION
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)$(BOLD)[COMPILING]:\t$(RESET)$(GREEN)$<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

# PRINT AND THEN COMPILE
all: pre-compile $(NAME)

# PRINT INFO
pre-compile:
	@echo "$(WHITE)$(BOLD)\t$(WHITE)[COMPILATION...]$(RESET)"
	@mkdir -p $(OBJ_DIR)

# COMPILATION
$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(FLAGS)
	@echo "$(WHITE)$(BOLD)\t[COMPILED SUCCESSFULLY]"
	@echo "[READY]:$(RESET)$(WHITE)\t$(NAME)$(RESET)"

# CLEAN OBJECT FILES
clean:
	@echo "$(WHITE)$(BOLD)\t[CLEANING OBJ...]$(RESET)"
	@if [ -d "$(OBJ_DIR)" ]; then \
		echo "$(RED)$(BOLD)[CLEAN]:\t$(RESET)$(RED)$(OBJ_DIR)$(RESET)"; \
		rm -rf $(OBJ_DIR); \
	fi

# CLEAN EXEC / LIB and call clean
fclean:
	@echo "$(WHITE)$(BOLD)\t[CLEANING EXEC/LIB...]"
	@echo "$(RED)[CLEAN]:\t$(RESET)$(RED)$(NAME)$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) clean -s

# CLEAN EVERYTHING AND RE-COMPILE
re: fclean all

tests_run:
	@echo "$(WHITE)$(BOLD)\t[TESTS...]$(RESET)"
