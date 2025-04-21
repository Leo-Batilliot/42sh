/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_exit
*/

#include "my.h"

int my_exit(char **array, linked_list_t **head, shell_t *shell)
{
    int status_exit = 0;

    (void)head;
    if (array[1])
        status_exit = atoi(array[1]);
    save_file(shell);
    exit(status_exit);
}
