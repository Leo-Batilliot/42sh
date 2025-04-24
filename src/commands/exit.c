/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_exit
*/

#include "shell.h"

// name :   my_exit
// args :   array, shell main struct
// use :    exit with given status (or 0) and free the main struct
int my_exit(char **array, shell_t *shell)
{
    int status_exit = 0;

    if (array[1]) {
        if (!str_is_digits(array[1]))
            return 1;
        status_exit = my_atoi(array[1]);
    }
    free_and_exit(shell, status_exit);
    return 0;
}
