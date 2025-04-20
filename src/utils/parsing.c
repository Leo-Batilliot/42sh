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
    if (shell->list)
        free_args_list(shell->list, 1);
    shell->list = init_list();
    if (!shell->list)
        return 1;
    return 0;
}

int appends_array(char ***new_array, int *j, char *string)
{
    char **tmp = realloc((*new_array), sizeof(char *) * ((*j) + 2));

    if (!tmp) {
        free_array((void **)new_array);
        return -1;
    }
    (*new_array) = tmp;
    (*new_array)[(*j) + 1] = NULL;
    (*new_array)[(*j)] = strdup(string);
    if (!(*new_array)[(*j)]) {
        free_array((void **)(*new_array));
        return -1;
    }
    (*j)++;
    return 0;
}

int add_alias(char **array_tmp, int *j, char ***new_array)
{
    int res = 0;

    for (int k = 0; array_tmp[k]; k++) {
        res = appends_array(new_array, j, array_tmp[k]);
        if (res == -1)
            return 84;
    }
    return 0;
}

static int replace_new(int *j, char ***new_array,
    char *find_str, shell_t *shell)
{
    char *string = NULL;
    char **array_tmp = NULL;
    alias_t *to_cmp = find_node(shell, find_str);

    if (to_cmp) {
        string = array_to_str(to_cmp->cmd);
        if (!string)
            return 1;
        array_tmp = split_str(string, " \t");
        if (add_alias(array_tmp, j, new_array) == 84)
            return 84;
        return 1;
    }
    return 0;
}

char **replace_alias(shell_t *shell, char **array)
{
    int res = 0;
    char **new_array = NULL;
    int j = 0;

    if (!array || !strcmp("alias", array[0]))
        return array;
    for (int i = 0; array[i]; i++) {
        res = replace_new(&j, &new_array, array[i], shell);
        if (res == 1)
            continue;
        if (res == 84)
            return NULL;
        res = appends_array(&new_array, &j, array[i]);
        if (res == -1)
            return NULL;
    }
    if (new_array)
        new_array[j] = NULL;
    return new_array;
}

int parse_args(shell_t *shell)
{
    char **array = split_str(shell->line, " \t\n");
    char **new_array = replace_alias(shell, array);
    args_t *cur = NULL;

    if (!new_array || reset_parsing_list(new_array, shell))
        return 1;
    for (int i = 0; new_array[i]; i++) {
        shell->res = set_redirection_file(new_array, shell, &cur, &i);
        if (shell->res == 1)
            return 1;
        if (shell->res == 2)
            continue;
        shell->res = parse_command_line(i, new_array, &cur, shell);
        if (shell->res == 1)
            shell->tmp_red = 0;
        if (shell->res == 84)
            return 1;
    }
    cur->args[shell->index_parse] = NULL;
    return 0;
}
