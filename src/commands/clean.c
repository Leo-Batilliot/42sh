/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** clear_history.c
*/

#include "my.h"


int free_history(shell_t *shell)
{
    history_t *next = NULL;

    for (history_t *history = shell->history; history; history = next) {
        next = history->next;
        free(history->cmd);
        free(history->time);
        free(history);
    }
    shell->history = NULL;
    return 0;
}

int print_help_msg(void)
{
    mini_printf(1, "Usage: clean [options]\n\nOptions:\n");
    mini_printf(1, "\thistory: clean your commands history\n");
    return 0;
}

int clean(char **array, shell_t *shell)
{
    (void)array;
    if (!array[1])
        return print_help_msg();
    if (!strcmp(array[1], "history") && shell->history)
        return free_history(shell);
    return print_help_msg();
}
