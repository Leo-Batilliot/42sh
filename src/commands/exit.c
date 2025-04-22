/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_exit
*/

#include "my.h"

int my_exit(char **array, shell_t *shell)
{
    int status_exit = 0;

    if (array[1])
        status_exit = atoi(array[1]);
    free_and_exit(shell, status_exit);
    return 0;
}
