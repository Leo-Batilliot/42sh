/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_parse_env
*/

#include "my.h"

linked_list_t *add_node(char *ope, char **env, int i)
{
    linked_list_t *new_alloc = malloc(sizeof(linked_list_t));

    if (!new_alloc)
        return NULL;
    new_alloc->key = my_strdup(env[i]);
    new_alloc->value = my_strdup(ope + 1);
    if (!new_alloc->key || !new_alloc->value) {
        free(new_alloc->value);
        free(new_alloc->key);
        free(new_alloc);
        return NULL;
    }
    new_alloc->next = NULL;
    return new_alloc;
}

linked_list_t *add_to_list(linked_list_t *head, linked_list_t *new_alloc)
{
    linked_list_t *cur = NULL;

    if (!head) {
        head = new_alloc;
    } else {
        cur = head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = new_alloc;
    }
    return head;
}

linked_list_t *my_parse_env(char **env)
{
    char *ope = NULL;
    linked_list_t *head = NULL;
    linked_list_t *new_alloc = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        ope = my_strchr(env[i], '=');
        if (!ope)
            return NULL;
        *ope = '\0';
        new_alloc = add_node(ope, env, i);
        if (!new_alloc)
            return NULL;
        *ope = '=';
        head = add_to_list(head, new_alloc);
    }
    return head;
}
