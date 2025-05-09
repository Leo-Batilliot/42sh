/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** which.c
*/

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// name :   get_paths
// args :   none
// use :    retrieve the PATH environment variable and split it into an array
static char **get_paths(void)
{
    char *path = getenv("PATH");
    char **paths = NULL;

    if (!path)
        return NULL;
    paths = split_str(path, ":");
    if (!paths)
        return NULL;
    return paths;
}

// name :   check_command_in_path
// args :   command, paths
// use :    check if a command exists in the given paths and print its location
static int check_command_in_path(char *command, char **paths)
{
    char *full_path = NULL;

    for (int j = 0; paths[j]; j++) {
        asprintf(&full_path, "%s/%s", paths[j], command);
        if (!my_strcmp("which", command)) {
            mini_printf(1, "which: shell built-in command.\n");
            free(full_path);
            return 1;
        }
        if (access(full_path, X_OK) == 0) {
            mini_printf(1, "%s\n", full_path);
            free(full_path);
            return 1;
        }
        free(full_path);
    }
    return 0;
}

// name :   handle_command
// args :   command
// use :    check if it is a built-in or exists in the PATH
static void handle_command(char *command)
{
    char **paths = get_paths();
    int found = 0;

    if (!paths) {
        mini_printf(1, "%s: Command not found.\n", command);
        return;
    }
    found = check_command_in_path(command, paths);
    if (!found && is_builtin(command))
        mini_printf(1, "%s: shell built-in command.\n", command);
    else if (!found)
        mini_printf(1, "%s: Command not found.\n", command);
    free_array((void **)paths);
}

// name :   which
// args :   array, shell
// use :    checking for commands in PATH or built-ins
int which(char **array, shell_t *shell)
{
    (void)shell;
    if (!array || !array[1]) {
        mini_printf(1, "which: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; array[i]; i++)
        handle_command(array[i]);
    return 0;
}
