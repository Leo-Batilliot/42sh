/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** free
*/
#include "my.h"

int free_redir(redirect_t *redirect, int count)
{
    for (int i = 0; i < count; i++)
        if (redirect[i].file)
            my_free(redirect[i].file);
    return my_free(redirect);
}

int free_list(linked_list_t *head)
{
    if (!head)
        return 0;
    for (linked_list_t *next = NULL; head; head = next) {
        next = head->next;
        if (head->key)
            my_free(head->key);
        if (head->value)
            my_free(head->value);
        my_free(head);
    }
    return 0;
}

int free_args_list(list_t *list, int opt)
{
    args_t *next = NULL;

    if (!list)
        return 0;
    for (args_t *tmp = list->head; tmp; tmp = next) {
        next = tmp->next;
        if (tmp->args)
            free_array((void **)tmp->args);
        if (tmp->redir)
            free_redir(tmp->redir, tmp->count_red);
        my_free(tmp);
    }
    list->head = NULL;
    if (opt == 1)
        return my_free(list);
    return 0;
}

int free_shell(shell_t *shell)
{
    int res = shell->last_exit;

    if (shell->env_cpy)
        free_array((void **)shell->env_cpy);
    if (shell->line)
        my_free(shell->line);
    if (shell->list)
        free_args_list(shell->list, 1);
    if (shell->path)
        my_free(shell->path);
    if (shell->save_old)
        my_free(shell->save_old);
    my_free(shell);
    return res;
}
