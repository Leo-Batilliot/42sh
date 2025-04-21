/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_env
*/

#include "my.h"

void print_env(linked_list_t **head)
{
    for (linked_list_t *tmp = *head; tmp; tmp = tmp->next) {
        write(1, tmp->key, strlen(tmp->key));
        write(1, "=", 1);
        if (tmp->value)
            write(1, tmp->value, strlen(tmp->value));
        write(1, "\n", 1);
    }
}

int my_env(char **array, linked_list_t **head, shell_t *shell)
{
    if (array[1]) {
        shell->last_exit = 127;
        mini_printf(2, "env: '%s': No such file or directory\n", array[1]);
        return 1;
    }
    print_env(head);
    return 2;
}
