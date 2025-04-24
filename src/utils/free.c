/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** free
*/

#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

// name :   free_redir
// args :   redirection struct, nb of files
// use :    S.E
static int free_redir(redirect_t *redirect, int count)
{
    for (int i = 0; i < count; i++) {
        if (redirect[i].file)
            my_free(redirect[i].file);
    }
    return my_free(redirect);
}

// name :   free_list
// args :   list
// use :    S.E
static int free_list(list_t *head)
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

// name :   free_args_list
// args :   args list
// use :    S.E
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

// name :   free_alias
// args :   alias list
// use :    S.E
static void free_alias(alias_t *alias)
{
    for (alias_t *next = NULL; alias; alias = next) {
        next = alias->next;
        free_array((void **)alias->cmd);
        my_free(alias->name);
        my_free(alias);
    }
}

// name :   free_shell_lists
// args :   shell main struct
// use :    S.E
static void free_shell_lists(shell_t *shell)
{
    if (shell->args)
        free_args_list(shell->args);
    if (shell->env)
        free_list(shell->env);
    if (shell->alias)
        free_alias(shell->alias);
    if (shell->history)
        free_history(shell);
}

// name :   free_shell
// args :   shell main struct
// use :    S.E
static int free_shell(shell_t *shell)
{
    int res = shell->last_exit;

    if (shell->line)
        my_free(shell->line);
    if (shell->env_cpy)
        free_array((void **)shell->env_cpy);
    if (shell->path)
        my_free(shell->path);
    if (shell->previous_pwd)
        my_free(shell->previous_pwd);
    if (shell->prompt_color)
        my_free(shell->prompt_color);
    free_shell_lists(shell);
    my_free(shell);
    return res;
}

// name :   free_and_exit
// args :   shell main struct, exit value
// use :    S.E
void free_and_exit(shell_t *shell, int value)
{
    save_file(shell);
    free_shell(shell);
    exit(value);
}
