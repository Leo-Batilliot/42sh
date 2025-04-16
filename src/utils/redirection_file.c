/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-gabin.wilson
** File description:
** redirect
*/

#include "my.h"

static int redirect_file(int *i, shell_t *shell, args_t **cur, char **array)
{
    if (!array[*i + 1])
        return print_error(shell, 1);
    if (shell->index_parse == 0)
        return print_error(shell, 0);
    (*cur)->redir[shell->tmp_red].file = my_strdup(array[*i + 1]);
    if (!(*cur)->redir[shell->tmp_red].file)
        return print_error(shell, 1);
    return 2;
}

static int empty_cmd_list(args_t **cur, shell_t *shell, char **cmd)
{
    if (!shell->list->head) {
        shell->list->head = init_cmd(cmd);
        if (!shell->list->head) {
            free_args_list(shell->list, 1);
            shell->list = NULL;
            shell->last_exit = 1;
            return 1;
        }
        *cur = shell->list->head;
    }
    return 0;
}

int set_redirection_file(char **array, shell_t *shell, args_t **cur, int *i)
{
    char *operators[] = {"<", ">", ">>", "<<"};
    int res = 0;
    int index = 0;

    if (empty_cmd_list(cur, shell, &array[*i]))
        return 1;
    for (; index < 4; index++)
        if (!my_strcmp(array[*i], operators[index])) {
            res = redirect_file(i, shell, cur, array);
            break;
        }
    if (res == 2) {
        *i += 1;
        (*cur)->redir[shell->tmp_red].status = index + 1;
        shell->tmp_red++;
    }
    return res;
}
