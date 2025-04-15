/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_env
*/

#include "my.h"
#include <unistd.h>

void print_env(linked_list_t *tmp)
{
    while (tmp != NULL) {
        printf("%s=", tmp->key);
        if (tmp->value != NULL)
            printf("%s", tmp->value);
        printf("\n");
        tmp = tmp->next;
    }
}

int commands_env(char **array, linked_list_t *head, info_shell_t *shell_i)
{
    linked_list_t *tmp = head;
    int value = 0;

    value = my_print_env(array, shell_i, tmp);
    if (value != 0)
        return (value == 2) ? 2 : 1;
    value = set_env(&head, array, shell_i);
    if (value != 0)
        return (value == 2) ? 2 : 1;
    value = my_unsetenv(array, &head, shell_i);
    if (value != 0)
        return (value == 2) ? 2 : 1;
    value = my_cd(array, head, shell_i);
    if (value != 0)
        return (value == 2) ? 2 : 1;
    my_exit(array);
    return 0;
}
