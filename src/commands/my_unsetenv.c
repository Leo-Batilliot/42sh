/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_unsetenv
*/

#include "my.h"

static int delete_node(linked_list_t **head, linked_list_t **tmp,
    linked_list_t **prev)
{
    linked_list_t *next = (*tmp)->next;

    if (!(*prev))
        *head = (*tmp)->next;
    else
        (*prev)->next = next;
    if ((*tmp)->key)
        my_free((*tmp)->key);
    if ((*tmp)->value)
        my_free((*tmp)->value);
    my_free(*tmp);
    (*tmp) = next;
    return 0;
}

static int check_key(linked_list_t **prev, linked_list_t **tmp,
    linked_list_t **head, char **array)
{
    for (int i = 1; array[i]; i++)
        if (!my_strcmp(array[i], (*tmp)->key))
            return delete_node(head, tmp, prev);
    (*prev) = (*tmp);
    return 0;
}

int my_unsetenv(char **array, linked_list_t **head, shell_t *shell)
{
    linked_list_t *prev = NULL;

    if (!array[1]) {
        fprintf(stderr, "unsetenv: Too few arguments.\n");
        shell->last_exit = 1;
        return 1;
    }
    for (linked_list_t *tmp = *head; tmp; tmp = tmp->next)
        check_key(&prev, &tmp, head, array);
    return 2;
}
