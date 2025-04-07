/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_cd
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

static int check_insides(char *to_cmp, char *to_up, linked_list_t **tmp)
{
    if (my_strcmp((*tmp)->key, to_cmp) == 0) {
        free((*tmp)->value);
        (*tmp)->value = my_strdup(to_up);
        if (!(*tmp)->value)
            return -1;
        return 1;
    }
    return 0;
}

linked_list_t *up_env(linked_list_t *head, char *to_cmp, char *to_up)
{
    linked_list_t *tmp = head;
    int value = 0;

    while (tmp != NULL) {
        value = check_insides(to_cmp, to_up, &tmp);
        if (value == -1)
            return NULL;
        tmp = tmp->next;
    }
    return head;
}

int gest_build_path(linked_list_t **head, char **path,
    char **array, int *to_free)
{
    char *home = get_env_value("HOME", (*head));
    int len = 0;

    if (!home)
        return -1;
    len = my_strlen(home) + my_strlen(array[1]) + 1;
    (*path) = malloc(sizeof(char) * len);
    if (!(*path))
        return -1;
    my_strcpy((*path), home);
    my_strcat((*path), array[1] + 1);
    (*to_free) = 1;
    return 0;
}

static char *getc_path(int *to_free, linked_list_t **head, char **array)
{
    char *path = NULL;

    if (array[1] != NULL)
        path = array[1];
    if (path == NULL || (path[0] == '~' && path[1] == '\0')) {
        path = get_env_value("HOME", (*head));
        if (!path)
            return NULL;
    }
    if (path[0] == '~' && path[1] != '\0') {
        if (gest_build_path(head, &path, array, to_free) == -1)
            return NULL;
    }
    return path;
}

static int verif_cd_path(char *path, char **array, info_shell_t *shell_i)
{
    if (!path)
        return 1;
    if (chdir(path) == -1) {
        my_printerr("%s: %s.\n", array[1], strerror(errno));
        shell_i->last_exit = ERROR;
        return 1;
    }
    return 0;
}

int not_inv(char **array, linked_list_t **head,
    info_shell_t *shell_i, char **oldpwd)
{
    char *path = NULL;
    char newpwd[256] = {0};
    int to_free = 0;

    *oldpwd = my_strdup(getcwd(NULL, 0));
    path = getc_path(&to_free, head, array);
    if (verif_cd_path(path, array, shell_i) == 1)
        return 1;
    if (getcwd(newpwd, 256) == NULL)
        return 1;
    if (to_free == 1)
        free(path);
    (*head) = up_env((*head), "PWD", newpwd);
    return 2;
}

int inv(linked_list_t **head, char *newpwd, info_shell_t *shell_i, char **old)
{
    char *save_old = getcwd(NULL, 0);

    if (!(*old))
        return 1;
    if (chdir((*old)) == -1) {
        my_printerr("%s: %s\n", (*old), strerror(errno));
        shell_i->last_exit = ERROR;
        return 1;
    }
    if (getcwd(newpwd, 256) == NULL)
        return 1;
    *old = save_old;
    (*head) = up_env((*head), "PWD", newpwd);
    return 2;
}

int my_cd(char **array, linked_list_t *head, info_shell_t *shell_i)
{
    char newpwd[256] = {0};
    int count = 0;
    static char *old = NULL;

    if (my_strcmp(array[0], "cd") == 0) {
        for (; array[count] != NULL; count++);
        if (count >= 3) {
            my_printerr("cd: Too many arguments.\n");
            shell_i->last_exit = ERROR;
            return 1;
        }
        if (array[1] == NULL || my_strcmp(array[1], "-") != 0) {
            return not_inv(array, &head, shell_i, &old);
        }
        if (my_strcmp(array[1], "-") == 0 && array[1][1] == '\0')
            return inv(&head, newpwd, shell_i, &old);
    }
    return 0;
}
