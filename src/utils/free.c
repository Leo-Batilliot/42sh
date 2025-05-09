/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** free
*/

#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

// name :   free_list
// args :   list
// use :    S.E
int free_list(list_t *head)
{
    if (!head)
        return 0;
    for (list_t *next = NULL; head; head = next) {
        next = head->next;
        my_free(head->key);
        my_free(head->value);
        my_free(head);
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
    if (shell->env)
        free_list(shell->env);
    if (shell->alias)
        free_alias(shell->alias);
    if (shell->history)
        free_history(shell);
    if (shell->local_vars)
        free_list(shell->local_vars);
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

void free_local_vars(list_t *vars)
{
    list_t *tmp;

    while (vars) {
        tmp = vars;
        vars = vars->next;
        my_free(tmp->key);
        my_free(tmp->value);
        my_free(tmp);
    }
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
