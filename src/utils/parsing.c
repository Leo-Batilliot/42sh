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
        mini_printf(2, "Invalid null command.\n");
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
    if (shell->args)
        free_args_list(shell->args);
    shell->args = NULL;
    return 0;
}

static int parsing_loop(shell_t *shell, char **new_array)
{
    args_t *cur = NULL;
    int res = 0;

    for (int i = 0; new_array[i]; i++) {
        res = set_redirection_file(new_array, shell, &cur, &i);
        if (res == 1)
            return 1;
        if (res == 2)
            continue;
        res = parse_command_line(i, new_array, &cur, shell);
        if (res == 1)
            shell->tmp_red = 0;
        if (res == 84)
            return 1;
    }
    cur->args[shell->index_parse] = NULL;
    return 0;
}

int parse_args(shell_t *shell)
{
    char **array = split_str(shell->line, " \t\n");
    char **new_array = replace_alias(shell, array);

    if (array != new_array)
        free_array((void **)array);
    if (!new_array || reset_parsing_list(new_array, shell))
        return free_array((void **)new_array) + 1;
    if (parsing_loop(shell, new_array))
        return free_array((void **)new_array) + 1;
    return free_array((void **)new_array);
}
