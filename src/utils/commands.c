/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_gest_commands
*/

#include "shell.h"
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

// name :   access_with_path
// args :   input str, result str, path array, index
// use :    try to access command with the path variables
static int access_with_path(char *input, char **res, char **array, int i)
{
    *res = malloc(sizeof(char) * my_strlen(array[i]) + my_strlen(input) + 2);
    if (!(*res))
        return 0;
    my_strcpy((*res), array[i]);
    my_strcat((*res), "/");
    my_strcat((*res), input);
    if (!access((*res), X_OK)) {
        free_array((void **)array);
        return 1;
    }
    return 0;
}

// name :   access_with_pwd
// args :   input str, result str, pwd
// use :    try to access command with the pwd variable
static int access_with_pwd(char *input, char **res, char *pwd)
{
    *res = malloc(sizeof(char) * (my_strlen(input) + my_strlen(pwd) + 2));
    if (!*res)
        return 0;
    my_strcpy(*res, pwd);
    my_strcat(*res, "/");
    my_strcat(*res, input);
    if (!access(*res, X_OK))
        return 1;
    return 0;
}

// name :   try_to_access
// args :   input str, pwd str, path str
// use :    try to acccess the input command using pwd and path variables
static char *try_to_access(char *input, char *pwd, char *path)
{
    char *res = NULL;
    char **array = simple_split_str(path, ":");

    if (!array)
        return NULL;
    for (int i = 0; array[i]; i++) {
        if (access_with_path(input, &res, array, i))
            return res;
        my_free(res);
        res = NULL;
    }
    free_array((void **)array);
    if (!pwd || pwd[0] == '\0')
        return NULL;
    if (access_with_pwd(input, &res, pwd))
        return res;
    my_free(res);
    return NULL;
}

// name :   get_path
// args :   input str, path str, pwd str
// use :    return the path to the input cmd or NULL
static char *get_path(char *input, char *path, char *pwd)
{
    if (!path || path[0] == '\0')
        return NULL;
    if (input[0] == '/' || (input[0] == '.' && input[1] == '/'))
        return my_strdup(input);
    return try_to_access(input, pwd, path);
}

// name :   get_command_path
// args :   array, shell main struct, adress of execute, argument
// use :    verify if the command can be executed and build its path
int get_command_path(char **array, shell_t *shell)
{
    if (!array[0])
        return -1;
    if (!is_builtin(array[0])) {
        if (shell->path)
            my_free(shell->path);
        shell->path = get_path(array[0],
            get_env_value("PATH", shell->env),
            get_env_value("PWD", shell->env));
        if (!shell->path) {
            mini_printf(2, "%s: Command not found.\n", array[0]);
            shell->last_exit = 1;
            my_free(shell->path);
            shell->path = NULL;
            return 1;
        }
    }
    return 0;
}
