/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** write_function
*/

#include "my.h"

static void print_array(FILE *fd, alias_t *cur)
{
    for (int k = 0; cur->cmd[k]; k++) {
        fprintf(fd, "%s", cur->cmd[k]);
        if (cur->cmd[k + 1])
            fprintf(fd, " ");
    }
}

int write_alias(shell_t *shell)
{
    FILE *fd = fopen("assets/alias.txt", "w");

    if (!fd)
        return 84;
    for (alias_t *cur = shell->alias; cur; cur = cur->next) {
        fprintf(fd, "%s='", cur->name);
        if (!cur->cmd) {
            fprintf(fd, "'\n");
            continue;
        }
        print_array(fd, cur);
        fprintf(fd, "'\n");
    }
    fclose(fd);
    return 0;
}

void write_history(shell_t *shell)
{
    FILE *fd = fopen("assets/history.txt", "w");
    int last_index = 1;
    int i = 1;
    int spaces = 0;

    if (!fd)
        return;
    for (history_t *tmp = shell->history; tmp; tmp = tmp->next)
        last_index++;
    for (history_t *cur = shell->history; cur; cur = cur->next) {
        spaces = spaces_count(i, last_index - 1);
        for (int s = 0; s < spaces; s++)
            fprintf(fd, " ");
        fprintf(fd, "%i  %s  %s\n", i, cur->time, cur->cmd);
        i++;
    }
    fclose(fd);
}
