/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_print_env
*/

#include "my.h"

int my_print_env(char **array, info_shell_t *shell_i, linked_list_t *tmp)
{
    if (my_strcmp(array[0], "env") == 0) {
        if (array[1] != NULL) {
            shell_i->last_exit = 127;
            fprintf(stderr, "env: '%s': No such file or directory\n",
            array[1]);
            return 1;
        }
        print_env(tmp);
        return 2;
    }
    return 0;
}
