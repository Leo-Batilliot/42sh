/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_unsetenv
*/

#include "my.h"
#include <unistd.h>

int free_unset(linked_list_t *tmp)
{
    free(tmp->key);
    free(tmp->value);
    free(tmp);
    return 1;
}

int cmp_in(linked_list_t **head, linked_list_t **tmp,
    int *to_delete, linked_list_t **prev)
{
    linked_list_t *next = (*tmp)->next;

    if ((*prev) == NULL)
        *head = (*tmp)->next;
    else
        (*prev)->next = (*tmp)->next;
    free_unset((*tmp));
    (*tmp) = next;
    *to_delete = 1;
    return 0;
}

int check_key(linked_list_t **prev, linked_list_t **tmp,
    linked_list_t **head, char **array)
{
    int to_delete = 0;

    for (int i = 1; array[i] != NULL; i++) {
        if (my_strcmp(array[i], (*tmp)->key) == 0)
            return cmp_in(head, tmp, &to_delete, prev);
    }
    if (!to_delete) {
        (*prev) = (*tmp);
        (*tmp) = (*tmp)->next;
    } else
        (*tmp) = (*tmp)->next;
    return 0;
}

int inside_unset(linked_list_t *tmp, linked_list_t **head,
    char **array, info_shell_t *shell_i)
{
    int value = 0;
    linked_list_t *prev = NULL;

    if (array[1] == NULL) {
        fprintf(stderr, "unsetenv: Too few arguments\n");
        shell_i->last_exit = 1;
        return 1;
    }
    while (tmp != NULL) {
        value = check_key(&prev, &tmp, head, array);
        if (value == 1)
            return 1;
    }
    return 2;
}

int my_unsetenv(char **array, linked_list_t **head, info_shell_t *shell_i)
{
    linked_list_t *tmp = *head;

    if (my_strcmp(array[0], "unsetenv") == 0)
        return inside_unset(tmp, head, array, shell_i);
    return 0;
}
