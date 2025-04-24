/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_env
*/

#include "shell.h"
#include <unistd.h>

// name :   print_env
// args :   env list
// use :    S.E
void print_env(list_t *head)
{
    for (list_t *tmp = head; tmp; tmp = tmp->next) {
        write(1, tmp->key, my_strlen(tmp->key));
        write(1, "=", 1);
        if (tmp->value)
            write(1, tmp->value, my_strlen(tmp->value));
        write(1, "\n", 1);
    }
}

// name :   my_env
// args :   array, shell main struct
// use :    builtin: handle errors and print the env
int my_env(char **array, shell_t *shell)
{
    if (array[1]) {
        shell->last_exit = 127;
        mini_printf(2, "env: '%s': No such file or directory\n", array[1]);
        return 1;
    }
    print_env(shell->env);
    return 2;
}
