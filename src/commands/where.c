/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** where.c
*/

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// name: search_in_path
// args: command
// use: searches for the given command in the system PATH and prints all paths
void search_in_path(const char *command)
{
    char *path = getenv("PATH");
    char *full_path = NULL;
    char **paths = NULL;

    if (!path)
        return;
    paths = simple_split_str(path, ":");
    for (int i = 0; paths[i]; i++) {
        asprintf(&full_path, "%s/%s", paths[i], command);
        if (access(full_path, X_OK) == 0)
            printf("%s\n", full_path);
        free(paths[i]);
    }
    free(full_path);
    free(paths);
}

// name: where
// args: array, shell
// use: checks if commands are shell built-ins or available in the system PATH
int where(char **array, shell_t *shell)
{
    (void)shell;
    for (int i = 1; array[i]; i++) {
        if (is_builtin(array[i]))
            printf("%s is a shell built-in\n", array[i]);
        search_in_path(array[i]);
    }
    return 0;
}
