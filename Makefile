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
		lib/split_str.c 						\
		lib/my_strcpy.c 						\
		lib/my_strcat.c 						\
		lib/count_word.c 						\
		lib/free.c 								\
		lib/array_to_str.c 						\
		lib/put_spaces.c						\
		lib/array_len.c 						\
		lib/mini_printf.c 						\
		src/commands/my_cd.c 					\
		src/commands/my_env.c 					\
		src/commands/my_exit.c 					\
		src/commands/my_setenv.c 				\
		src/commands/my_unsetenv.c 				\
		src/commands/builtin.c 					\
		src/commands/clean_cmds.c				\
		src/commands/my_history.c				\
		src/commands/alias.c 					\
		src/utils/redirection.c 				\
		src/utils/commands.c 					\
		src/utils/exec.c 						\
		src/utils/my_list_to_array.c 			\
		src/utils/parsing.c 					\
		src/utils/redirection_file.c 			\
		src/utils/init.c 						\
		src/utils/free.c 						\
		src/utils/write_function.c 				\
		src/utils/load_functions.c 				\
		src/utils/utils.c 						\
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
	@echo -e "$(GREEN)$(BOLD)[COMPILING]:\t$(RESET)$(GREEN)$<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

# PRINT AND THEN COMPILE
all: pre-compile $(NAME)

# PRINT INFO
pre-compile:
	@echo -e "$(WHITE)$(BOLD)\t$(WHITE)[COMPILATION...]$(RESET)"
	@mkdir -p $(OBJ_DIR)

# COMPILATION
$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(FLAGS)
	@echo -e "$(WHITE)$(BOLD)\t[COMPILED SUCCESSFULLY]"
	@echo -e "[READY]:$(RESET)$(WHITE)\t$(NAME)$(RESET)"

# CLEAN OBJECT FILES
clean:
	@echo -e "$(WHITE)$(BOLD)\t[CLEANING OBJ...]$(RESET)"
	@if [ -d "$(OBJ_DIR)" ]; then \
		echo "$(RED)$(BOLD)[CLEAN]:\t$(RESET)$(RED)$(OBJ_DIR)$(RESET)"; \
		rm -rf $(OBJ_DIR); \
	fi

# CLEAN EXEC / LIB and call clean
fclean:
	@echo -e "$(WHITE)$(BOLD)\t[CLEANING EXEC/LIB...]"
	@echo -e "$(RED)[CLEAN]:\t$(RESET)$(RED)$(NAME)$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) clean -s

# CLEAN EVERYTHING AND RE-COMPILE
re: fclean all

tests_run:
	@echo -e "$(WHITE)$(BOLD)\t[TESTS...]$(RESET)"
