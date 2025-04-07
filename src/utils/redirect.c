/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-gabin.wilson
** File description:
** redirect
*/

#include "my.h"

static int output_redirection(int *i, info_shell_t *shell_i,
    args_t **cur, char **array)
{
    if (!my_strcmp(array[*i], ">")) {
        if (array[*i + 1] == NULL)
            return message_error(shell_i);
        if (shell_i->index_parse == 0)
            return null_message(shell_i);
        (*cur)->redir[shell_i->tmp_red].file = my_strdup(array[(*i) + 1]);
        if (!(*cur)->redir[shell_i->tmp_red].file)
            return message_error(shell_i);
        (*cur)->redir[shell_i->tmp_red].statu = 2;
        (*i)++;
        shell_i->tmp_red++;
        return 2;
    }
    return 0;
}

static int input_redirection(int *i, info_shell_t *shell_i,
    args_t **cur, char **array)
{
    if (!my_strcmp(array[*i], "<")) {
        if (array[*i + 1] == NULL)
            return message_error(shell_i);
        if (shell_i->index_parse == 0)
            return null_message(shell_i);
        (*cur)->redir[shell_i->tmp_red].file = my_strdup(array[(*i) + 1]);
        if (!(*cur)->redir[shell_i->tmp_red].file)
            return message_error(shell_i);
        (*cur)->redir[shell_i->tmp_red].statu = 1;
        (*i)++;
        shell_i->tmp_red++;
        return 2;
    }
    return 0;
}

static int append_redirection(int *i, info_shell_t *shell_i,
    args_t **cur, char **array)
{
    if (!my_strcmp(array[*i], ">>")) {
        if (array[*i + 1] == NULL)
            return message_error(shell_i);
        if (shell_i->index_parse == 0)
            return null_message(shell_i);
        (*cur)->redir[shell_i->tmp_red].file = my_strdup(array[*i + 1]);
        if (!(*cur)->redir[shell_i->tmp_red].file)
            return message_error(shell_i);
        (*cur)->redir[shell_i->tmp_red].statu = 3;
        (*i)++;
        shell_i->tmp_red++;
        return 2;
    }
    return 0;
}

static int heredoc_redirection(int *i, info_shell_t *shell_i,
    args_t **cur, char **array)
{
    if (!my_strcmp(array[*i], "<<")) {
        if (array[*i + 1] == NULL)
            return message_error(shell_i);
        if (shell_i->index_parse == 0)
            return null_message(shell_i);
        (*cur)->redir[shell_i->tmp_red].file = my_strdup(array[*i + 1]);
        if (!(*cur)->redir[shell_i->tmp_red].file)
            return message_error(shell_i);
        (*cur)->redir[shell_i->tmp_red].statu = 4;
        (*i)++;
        shell_i->tmp_red++;
        return 2;
    }
    return 0;
}

int gest_redir(char **array, info_shell_t
    *shell_i, args_t **cur, int *i)
{
    int value = 0;

    if (gest_first_cmd(i, cur, shell_i, array) == 1)
        return ERROR;
    value = input_redirection(i, shell_i, cur, array);
    if (value != 0)
        return (value == 2) ? 2 : ERROR;
    value = output_redirection(i, shell_i, cur, array);
    if (value != 0)
        return (value == 2) ? 2 : ERROR;
    value = append_redirection(i, shell_i, cur, array);
    if (value != 0)
        return (value == 2) ? 2 : ERROR;
    value = heredoc_redirection(i, shell_i, cur, array);
    if (value != 0)
        return (value == 2) ? 2 : ERROR;
    return 0;
}
