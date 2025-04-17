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
        mini_printf("%s=", tmp->key);
        if (tmp->value != NULL)
            mini_printf("%s", tmp->value);
        mini_printf("\n");
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
    value = my_history(array[0]);
    if (value != 0)
        return (value == 2) ? 2 : 1;
    my_exit(array);
    return 0;
}
