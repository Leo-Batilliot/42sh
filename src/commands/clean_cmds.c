/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** clear_history.c
*/

#include "my.h"

int clean_history(shell_t *shell)
{
    history_t *current = shell->head;
    history_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current->cmd);
        free(current);
        current = next;
    }
    shell->head = NULL;
    return 0;
}

int print_help_msg(void)
{
    mini_printf(1, "Usage: clean [options]\n\nOptions:\n");
    mini_printf(1, "\thistory: clean your commands history\n");
    return 0;
}

int clean(char **array, linked_list_t **head, shell_t *shell)
{
    (void)array;
    (void)head;
    if (!array[1])
        return print_help_msg();
    if (!strcmp(array[1], "history"))
        return clean_history(shell);
    return 0;
}
