/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** clear_history.c
*/

#include "shell.h"
#include "stddef.h"

// name :   free_history
// args :   shell main struct
// use :    S.E
int free_history(shell_t *shell)
{
    history_t *next = NULL;

    for (history_t *history = shell->history; history; history = next) {
        next = history->next;
        my_free(history->cmd);
        my_free(history->time);
        my_free(history);
    }
    shell->history = NULL;
    return 0;
}

// name :   print_help_msg
// args :   N.A
// use :    print a help message if clean is used without a proper argument
static int print_help_msg(void)
{
    mini_printf(1, "Usage: clean [options]\n\nOptions:\n");
    mini_printf(1, "\thistory: clean your commands history\n");
    return 0;
}

// name :   clean
// args :   array, shell main struct
// use :    clean differents builtin datas according to the array's content
int clean(char **array, shell_t *shell)
{
    (void)array;
    if (!array[1])
        return print_help_msg();
    if (!my_strcmp(array[1], "history") && shell->history)
        return free_history(shell);
    if (!my_strcmp(array[1], "alias") && shell->alias)
        return clear_all_alias(shell);
    return print_help_msg();
}
