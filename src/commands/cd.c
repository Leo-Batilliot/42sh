/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_cd
*/

#include "shell.h"
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// name :   update_value
// args :   env list, name, value
// use :    parse the env list to find the node and replace its value if found
static int update_value(list_t **head, char *name, char *value)
{
    for (list_t *tmp = *head; tmp; tmp = tmp->next) {
        if (!my_strcmp((tmp)->key, name)) {
            my_free((tmp)->value);
            (tmp)->value = my_strdup(value);
            return 0;
        }
    }
    return 1;
}

// name :   home_path
// args :   env list, adress of path, string, adress of to_free value
// use :    create the cd path if it contains a '~' (home)
static int home_path(list_t **head, char **path,
    char *str, int *to_free)
{
    char *home = get_env_value("HOME", (*head));

    if (!home)
        return 1;
    (*path) = malloc(sizeof(char) * my_strlen(home) + my_strlen(str) + 1);
    if (!(*path))
        return 1;
    my_strcpy((*path), home);
    my_strcat((*path), str + 1);
    (*to_free) = 1;
    return 0;
}

// name :   get_path
// args :   adress of to_free value, env list, string
// use :    computes the path contained in the string
static char *get_path(int *to_free, list_t **head, char *str)
{
    char *path = NULL;

    if (str)
        path = str;
    if (!path || (path[0] == '~' && path[1] == '\0'))
        path = get_env_value("HOME", (*head));
    if (!path)
        return NULL;
    if (path[0] == '~' && path[1] != '\0')
        if (home_path(head, &path, str, to_free))
            return NULL;
    return path;
}

// name :   invalid_path
// args :   path, string, shell
// use :    check if the built path is a correct path for cd, print errors
static int invalid_path(char *path, char *str, shell_t *shell)
{
    if (!path)
        return 1;
    if (chdir(path) == -1) {
        mini_printf(2, "%s: %s.\n", str, strerror(errno));
        shell->last_exit = 1;
        return 1;
    }
    return 0;
}

// name :   change_directory
// args :   string, shell main struct
// use :    build the path and try to access it, replace old pwd
static int change_directory(char *str, shell_t *shell)
{
    char *path = NULL;
    char newpwd[256];
    int to_free = 0;

    if (shell->previous_pwd)
        my_free(shell->previous_pwd);
    shell->previous_pwd = getcwd(NULL, 0);
    path = get_path(&to_free, &(shell->env), str);
    if (invalid_path(path, str, shell))
        return str != path ? my_free(path) + 1 : 1;
    if (to_free)
        my_free(path);
    if (!getcwd(newpwd, 256))
        return 1;
    update_value(&(shell->env), "PWD", newpwd);
    return 2;
}

// name :   previous_path
// args :   shell main struct
// use :    reverse current and old pwd in case of "cd -"
static int previous_path(shell_t *shell)
{
    char *save_old = getcwd(NULL, 0);
    char newpwd[256] = {0};

    if (!(shell->previous_pwd))
        return 1;
    if (chdir((shell->previous_pwd)) == -1) {
        mini_printf(2, "%s: %s\n", (shell->previous_pwd), strerror(errno));
        shell->last_exit = 1;
        return 1;
    }
    if (!getcwd(newpwd, sizeof(char) * 256))
        return 1;
    if (shell->previous_pwd)
        my_free(shell->previous_pwd);
    shell->previous_pwd = save_old;
    update_value(&(shell->env), "PWD", newpwd);
    return 2;
}

// name :   my_cd
// args :   array, shell main struct
// use :    call change_directory/previous depending on the given array
int my_cd(char **array, shell_t *shell)
{
    if (array_len((const void **) array) >= 3) {
        mini_printf(2, "cd: Too many arguments.\n");
        shell->last_exit = 1;
        return 1;
    }
    if (array[1] && !my_strcmp(array[1], "-"))
        return previous_path(shell);
    return change_directory(array[1], shell);
}
