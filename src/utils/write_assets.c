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
    FILE *fp = fopen("assets/history.txt", "w");
    char *spaces = NULL;
    int last_index = 1;
    int i = 1;

    if (!fp)
        return;
    for (history_t *tmp = shell->history; tmp; tmp = tmp->next)
        last_index++;
    for (history_t *cur = shell->history; cur; cur = cur->next) {
        spaces = put_spaces(i, last_index);
        if (!spaces)
            return;
        fprintf(fp, "%s%i  %s  %s", spaces, i, cur->time, cur->cmd);
        i++;
    }
    fclose(fp);
}
