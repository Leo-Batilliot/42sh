/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** free_list
*/
#include "my.h"

int free_node(node_t *node)
{
    if (!node)
        return 84;
    if (node->name)
        free(node->name);
    if (node->value)
        free(node->value);
    free(node);
    return 0;
}

void free_list(list_t *list)
{
    node_t *current;
    node_t *next;

    if (!list)
        return;
    current = list->head;
    while (current) {
        next = current->next;
        free_node(current);
        current = next;
    }
    if (list->oldpwd)
        free(list->oldpwd);
    if (list->home)
        free(list->home);
    free(list);
}
