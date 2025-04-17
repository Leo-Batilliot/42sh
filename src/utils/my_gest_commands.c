/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_gest_commands
*/

#include "my.h"

static int get_count(args_t **new, char **array)
{
    (*new)->count_red = 0;
    for (int i = 0; array[i]; i++) {
        if (!my_strcmp(";", array[i]) || !my_strcmp("|", array[i]))
            break;
        if (!my_strcmp("<", array[i])
            || !my_strcmp(">", array[i])
            || !my_strcmp(">>", array[i])
            || !my_strcmp("<<", array[i]))
            (*new)->count_red++;
    }
    if ((*new)->count_red > 0) {
        (*new)->redir = malloc(sizeof(redirect_t) * (*new)->count_red);
        if (!(*new)->redir)
            (*new)->redir = NULL;
    }
    return 0;
}

args_t *add_cmd(char **array)
{
    args_t *new = NULL;

    new = malloc(sizeof(args_t));
    if (!new)
        return NULL;
    new->args = malloc(sizeof(char *) * 100);
    if (!new->args)
        return NULL;
    for (int i = 0; i < 100; i++)
        new->args[i] = NULL;
    get_count(&new, array);
    new->is_pipe = 0;
    new->next = NULL;
    return new;
}

int gest_cur_commands(char **array, linked_list_t *head, info_shell_t *shell_i)
{
    if (array[0] == NULL)
        return -1;
    if (handle_color_command(array, shell_i))
        return -1;
    if (is_bulltins(array[0]) == 0) {
        if (get_cur_pass(&head, array, shell_i) == 1) {
            free(shell_i->path);
            return -1;
        }
    }
    return 0;
}
