/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-gabin.wilson
** File description:
** parse
*/

#include "my.h"
#include <stdbool.h>

int null_message(info_shell_t *shell_i)
{
    fprintf(stderr, "Invalid null command.\n");
    shell_i->last_exit = ERROR;
    return ERROR;
}

int message_error(info_shell_t *shell_i)
{
    fprintf(stderr, "Missing name for redirect.\n");
    shell_i->last_exit = ERROR;
    return ERROR;
}

int gest_first_cmd(int *i, args_t **cur, info_shell_t *shell_i, char **array)
{
    if (!shell_i->list->head) {
        shell_i->list->head = add_cmd(&array[*i]);
        if (!shell_i->list->head) {
            shell_i->last_exit = 1;
            return 1;
        }
        *cur = shell_i->list->head;
    }
    return 0;
}

static int add_to(info_shell_t *shell_i, int i, char **array, args_t **cur)
{
    (*cur)->args[shell_i->index_parse] = NULL;
    (*cur)->next = add_cmd(&array[i + 1]);
    if (!(*cur)->next)
        return 84;
    (*cur) = (*cur)->next;
    shell_i->index_parse = 0;
    return 1;
}

static int add_pipe(int i, char **array,
    args_t **cur, info_shell_t *shell_i)
{
    if (shell_i->index_parse == 0 || array[i + 1] == NULL) {
        fprintf(stderr, "Invalid null command.\n");
        shell_i->last_exit = ERROR;
        return 84;
    }
    (*cur)->is_pipe = 1;
    return add_to(shell_i, i, array, cur);
}

bool is_operator(const char *str)
{
    const char *operators[] = {";", ">>", "<<", "<", "|", ">"};

    for (int j = 0; j < 6; j++) {
        if (!my_strcmp(str, operators[j]))
            return true;
    }
    return false;
}

static int fill_parse_v(int i, char **array,
    args_t **cur, info_shell_t *shell_i)
{
    if (my_strchr(array[i], '|') != NULL && my_strlen(array[i]) > 1) {
        null_message(shell_i);
        return 84;
    }
    if (!my_strcmp(array[i], ";"))
        return add_to(shell_i, i, array, cur);
    if (!my_strcmp(array[i], "|"))
        return add_pipe(i, array, cur, shell_i);
    if (!is_operator(array[i])) {
        (*cur)->args[shell_i->index_parse] = my_strdup(array[i]);
        if (!(*cur)->args)
            return 84;
        shell_i->index_parse++;
    }
    return 0;
}

static int reset_parse(char **array, info_shell_t *shell_i)
{
    shell_i->index_parse = 0;
    shell_i->tmp_red = 0;
    shell_i->list = create_list();
    if (!array || !shell_i->list)
        return ERROR;
    return 0;
}

int parse_args(info_shell_t *shell_i)
{
    char **array = split_str(shell_i->line, " \t\n");
    args_t *cur = NULL;

    if (reset_parse(array, shell_i) == ERROR)
        return ERROR;
    for (int i = 0; array[i] != NULL; i++) {
        shell_i->res = gest_redir(array, shell_i, &cur, &i);
        if (shell_i->res == ERROR)
            return ERROR;
        if (shell_i->res == 2)
            continue;
        shell_i->res = fill_parse_v(i, array, &cur, shell_i);
        if (shell_i->res == 1)
            shell_i->tmp_red = 0;
        if (shell_i->res == 84)
            return ERROR;
    }
    cur->args[shell_i->index_parse] = NULL;
    return 0;
}
