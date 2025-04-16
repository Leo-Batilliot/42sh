/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-gabin.wilson
** File description:
** parse
*/

#include "my.h"

static int add_new_cmd(shell_t *shell, int i, char **array, args_t **cur)
{
    (*cur)->args[shell->index_parse] = NULL;
    (*cur)->next = init_cmd(&array[i + 1]);
    if (!(*cur)->next)
        return 84;
    (*cur) = (*cur)->next;
    shell->index_parse = 0;
    return 1;
}

static int add_pipe_cmd(int i, char **array,
    args_t **cur, shell_t *shell)
{
    if (shell->index_parse == 0 || array[i + 1] == NULL) {
        fprintf(stderr, "Invalid null command.\n");
        shell->last_exit = 1;
        return 84;
    }
    (*cur)->is_pipe = 1;
    return add_new_cmd(shell, i, array, cur);
}

static int parse_command_line(int i, char **array,
    args_t **cur, shell_t *shell)
{
    if (my_strchr(array[i], '|') && my_strlen(array[i]) > 1) {
        print_error(shell, 0);
        return 84;
    }
    if (!my_strcmp(array[i], ";"))
        return add_new_cmd(shell, i, array, cur);
    if (!my_strcmp(array[i], "|"))
        return add_pipe_cmd(i, array, cur, shell);
    if (!is_operator(array[i])) {
        (*cur)->args[shell->index_parse] = my_strdup(array[i]);
        if (!(*cur)->args)
            return 84;
        shell->index_parse++;
    }
    return 0;
}

static int reset_parsing_list(char **array, shell_t *shell)
{
    if (!array)
        return 1;
    shell->index_parse = 0;
    shell->tmp_red = 0;
    if (shell->list)
        free_args_list(shell->list, 1);
    shell->list = init_list();
    if (!shell->list)
        return 1;
    return 0;
}

int parse_args(shell_t *shell)
{
    char **array = split_str(shell->line, " \t\n");
    args_t *cur = NULL;

    if (reset_parsing_list(array, shell))
        return 1;
    for (int i = 0; array[i]; i++) {
        shell->res = set_redirection_file(array, shell, &cur, &i);
        if (shell->res == 1)
            return 1;
        if (shell->res == 2)
            continue;
        shell->res = parse_command_line(i, array, &cur, shell);
        if (shell->res == 1)
            shell->tmp_red = 0;
        if (shell->res == 84)
            return 1;
    }
    cur->args[shell->index_parse] = NULL;
    return 0;
}
