/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_get_curpath
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

int check_path(char *input, char **path, char *str)
{
    int len = my_strlen(str) + my_strlen(input) + 2;

    *path = malloc(sizeof(char) * len);
    if (!(*path))
        return 2;
    my_strcpy((*path), str);
    my_strcat((*path), "/");
    my_strcat((*path), input);
    if (access((*path), X_OK) == 0) {
        free(str);
        return 1;
    }
    return 0;
}

static int build_pwd(char *string_pwd, char *input, char **path)
{
    int len = my_strlen(input) + my_strlen(string_pwd) + 2;

    *path = malloc(sizeof(char) * len);
    if (!*path)
        return 0;
    my_strcpy(*path, string_pwd);
    my_strcat(*path, "/");
    my_strcat(*path, input);
    if (access(*path, X_OK) == 0) {
        return 1;
    }
    return 0;
}

char *get_path(char *input, char *string_path, char *string_pwd)
{
    char *path = NULL;
    char **array = NULL;
    int res = 0;

    if (!string_path || string_path[0] == '\0')
        return NULL;
    if (input[0] == '/' || (input[0] == '.' && input[1] == '/'))
        return my_strdup(input);
    array = my_str_to_word_array_sep(string_path, ":");
    for (int i = 0; array[i] != NULL; i++) {
        res = check_path(input, &path, array[i]);
        if (res != 0)
            return (res == 2) ? NULL : path;
        free(path);
    }
    free_array(array);
    if (!string_pwd || string_pwd[0] == '\0')
        return NULL;
    res = build_pwd(string_pwd, input, &path);
    return (res == 1) ? path : NULL;
}
