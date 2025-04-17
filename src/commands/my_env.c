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
        printf("%s=", tmp->key);
        if (tmp->value)
            printf("%s", tmp->value);
        printf("\n");
    }
}

int my_env(char **array, shell_t *shell, linked_list_t **head)
{
    if (array[1]) {
        shell->last_exit = 127;
        fprintf(stderr, "env: '%s': No such file or directory\n", array[1]);
        return 1;
    }
    print_env(head);
    return 2;
}
