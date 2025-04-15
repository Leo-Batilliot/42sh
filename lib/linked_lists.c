/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** linked_lists
*/
#include "my.h"

list_t *create_list(void)
{
    list_t *list = malloc(sizeof(list_t));

    if (!list)
        return NULL;
    list->head = NULL;
    list->value = 0;
    return list;
}

void add_node(const char *name, const char *value, list_t *list)
{
    node_t *node;
    node_t *current;

    node = malloc(sizeof(node_t));
    if (!node)
        return;
    node->name = my_strdup(name);
    node->value = my_strdup(value);
    node->next = NULL;
    if (!list->head) {
        list->head = node;
        return;
    }
    current = list->head;
    for (; current->next; current = current->next);
    current->next = node;
}

int delete_node(list_t *list, const char *name)
{
    node_t *current;
    node_t *previous;
    node_t *next;

    current = list->head;
    if (!my_strcmp(current->name, name)) {
        list->head = current->next;
        return free_node(current);
    }
    for (; current; current = next) {
        next = current->next;
        if (!my_strcmp(current->name, name)) {
            previous->next = next;
            return free_node(current);
        }
        previous = current;
    }
    return 84;
}

int print_list(list_t *list)
{
    node_t *current;

    if (!list || !list->head)
        return -1;
    current = list->head;
    for (; current; current = current->next)
        printf(1, "%s=%s\n", current->name, current->value);
    return 0;
}
