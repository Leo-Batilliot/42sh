/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_get_in_env
*/

#include "my.h"

char *get_env_value(const char *to_find, linked_list_t *head)
{
    for (linked_list_t *tmp = head; tmp; tmp = tmp->next)
        if (!strcmp(to_find, tmp->key))
            return tmp->value;
    return NULL;
}
