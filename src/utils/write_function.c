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

    if (!fp)
        return;
    for (history_t *cur = shell->head; cur; cur = cur->next)
        fprintf(fp, "%s", cur->full_line);
    fclose(fp);
}
