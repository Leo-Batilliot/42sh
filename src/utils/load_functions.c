/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** load_functions
*/

#include "my.h"

int load_alias(shell_t *shell)
{
    FILE *fd = fopen("assets/alias.txt", "r");
    char *line = NULL;
    size_t size = 0;
    char **array = NULL;

    if (!fd) {
        shell->alias = NULL;
        return 0;
    }
    while (getline(&line, &size, fd) != -1) {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        array = split_str(line, " \t='");
        if (!array)
            continue;
        add_node(shell, array);
        free(array);
    }
    free(line);
    return fclose(fd);
}

int load_history(shell_t *shell)
{
    FILE *fp = fopen("assets/history.txt", "r");
    char **array = NULL;
    char *line = NULL;
    size_t len = 0;

    if (!fd)
        return 1;
    while (getline(&line, &len, fp) != -1) {
        array = split_str(line, " ");
        if (!array)
            return 1;
        add_node_to_history(shell, array[2]);
    }
    free(line);
    return fclose(fd);
}
