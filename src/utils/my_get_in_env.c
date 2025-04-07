/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_get_in_env
*/

#include "my.h"

char *get_env_value(const char *to_find, linked_list_t *head)
{
    linked_list_t *tmp = head;

    while (tmp != NULL) {
        if (my_strcmp(to_find, tmp->key) == 0)
            return tmp->value;
        tmp = tmp->next;
    }
    return NULL;
}
