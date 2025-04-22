/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** free
*/
#include "my.h"

static int free_redir(redirect_t *redirect, int count)
{
    for (int i = 0; i < count; i++) {
        if (redirect[i].file)
            my_free(redirect[i].file);
    }
    return my_free(redirect);
}

int free_list(list_t *head)
{
    if (!head)
        return 0;
    for (list_t *next = NULL; head; head = next) {
        next = head->next;
        if (head->key)
            my_free(head->key);
        if (head->value)
            my_free(head->value);
        my_free(head);
    }
    return 0;
}

int free_args_list(args_t *list)
{
    args_t *next = NULL;

    if (!list)
        return 0;
    for (args_t *tmp = list; tmp; tmp = next) {
        next = tmp->next;
        if (tmp->args)
            free_array((void **)tmp->args);
        if (tmp->redir)
            free_redir(tmp->redir, tmp->count_red);
        my_free(tmp);
    }
    return 0;
}

static void free_alias(alias_t *alias)
{
    for (alias_t *next = NULL; alias; alias = next) {
        next = alias->next;
        free(alias->cmd);
        free(alias->name);
        free(alias);
    }
}

static void free_history(history_t *history)
{
    for (history_t *next = NULL; history; history = next) {
        next = history->next;
        free(history->cmd);
        free(history->time);
        free(history);
    }
}

static int free_shell(shell_t *shell)
{
    int res = shell->last_exit;

    if (shell->env_cpy)
        free_array((void **)shell->env_cpy);
    if (shell->args)
        free_args_list(shell->args);
    if (shell->path)
        my_free(shell->path);
    if (shell->previous_pwd)
        my_free(shell->previous_pwd);
    if (shell->env)
        free_list(shell->env);
    if (shell->alias)
        free_alias(shell->alias);
    if (shell->history)
        free_history(shell->history);
    if (shell->prompt_color)
        my_free(shell->prompt_color);
    my_free(shell);
    return res;
}

void free_and_exit(shell_t *shell, int value)
{
    save_file(shell);
    free_shell(shell);
    exit(value);
}
