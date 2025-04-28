/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** load_functions
*/

#include "shell.h"
#include <stddef.h>
#include <stdio.h>

// name :   load_alias
// args :   shell main struct
// use :    S.E
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
        if (line[my_strlen(line) - 1] == '\n')
            line[my_strlen(line) - 1] = '\0';
        array = split_str(line, " \t='");
        if (!array)
            continue;
        add_node(shell, array);
        free_array((void **)array);
    }
    my_free(line);
    return fclose(fd);
}

// name :   load_history
// args :   shell main struct
// use :    S.E
int load_history(shell_t *shell)
{
    FILE *fd = fopen("assets/history.txt", "r");
    char **array = NULL;
    char *line = NULL;
    size_t len = 0;

    if (!fd)
        return 1;
    while (getline(&line, &len, fd) != -1) {
        if (line[my_strlen(line) - 1] == '\n')
            line[my_strlen(line) - 1] = '\0';
        array = split_str(line, " ");
        if (!array || array_len((const void **) array) < 3)
            continue;
        add_node_to_history(shell, array[1], array_to_str(&(array[2])));
        free_array((void **)array);
    }
    my_free(line);
    return fclose(fd);
}
