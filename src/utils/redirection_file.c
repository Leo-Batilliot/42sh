/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-gabin.wilson
** File description:
** redirect
*/

#include "shell.h"
#include <stddef.h>

// name :   redirect_file
// args :   address of index, shell main struct, current arg, array
// use :    set the redirection file in the current command and handle errors
static int redirect_file(int *i, shell_t *shell, args_t **cur, char **array)
{
    if (!array[*i + 1]) {
        (*cur)->redir[shell->tmp_red].file = NULL;
        return print_error(shell, 1);
    }
    if (shell->index_parse == 0) {
        (*cur)->redir[shell->tmp_red].file = NULL;
        return print_error(shell, 0);
    }
    (*cur)->redir[shell->tmp_red].file = my_strdup(array[*i + 1]);
    if (!(*cur)->redir[shell->tmp_red].file)
        return print_error(shell, 1);
    return 2;
}

// name :   empty_cmd_list
// args :   current arg, shell main struct, array
// use :    initialize command list if it’s empty
static int empty_cmd_list(args_t **cur, shell_t *shell, char **cmd)
{
    if (!shell->args) {
        shell->args = init_cmd(cmd);
        if (!shell->args) {
            shell->last_exit = 1;
            return 1;
        }
        *cur = shell->args;
    }
    return 0;
}

// name :   set_redirection_file
// args :   array, shell main struct, current arg, address of index
// use :    handle redirection tokens and update redirection info in arg
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
