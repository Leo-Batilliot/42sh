##
## EPITECH PROJECT, 2024
## libmy
## File description:
## Makefile
##

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -W -I../../include -g
AR      = ar rcs
RANLIB  = ranlib
RM      = rm -f

SRC     = 	my_strchr.c 					\
			my_strcmp.c 					\
			my_strdup.c 					\
			my_strlen.c 					\
			my_str_to_word_array_sep.c 		\
			my_strcpy.c 					\
			my_strcat.c 					\
			my_get_nbr.c 					\
			my_putstr.c 					\
			my_put_nbr.c 					\
			my_putchar.c 					\
			mini_printf.c					\
			my_printerr.c					\
			linked_list.c 					\

OBJ     = $(SRC:.c=.o)
NAME    = libmy.a

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Building $(NAME)..."
	@$(AR) $(NAME) $(OBJ)
	@$(RANLIB) $(NAME)

clean:
	@echo -e "Cleaning object files..."
	@$(RM) $(OBJ)

fclean: clean
	@echo -e "Removing $(NAME)..."
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
