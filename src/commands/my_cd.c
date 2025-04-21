/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_cd
*/

#include "my.h"

static int compare_and_replace(char *name, char *value, linked_list_t **tmp)
{
    if (!my_strcmp((*tmp)->key, name)) {
        free((*tmp)->value);
        (*tmp)->value = my_strdup(value);
        return 1;
    }
    return 0;
}

static int update_value(linked_list_t **head, char *name, char *value)
{
    for (linked_list_t *tmp = *head; tmp; tmp = tmp->next)
        if (compare_and_replace(name, value, &tmp))
            return 0;
    return 1;
}

int home_path(linked_list_t **head, char **path,
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

static char *get_path(int *to_free, linked_list_t **head, char *str)
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

int change_directory(char *str, linked_list_t **head,
    shell_t *shell, char **oldpwd)
{
    char *path = NULL;
    char newpwd[256] = {0};
    int to_free = 0;

    *oldpwd = my_strdup(getcwd(NULL, 0));
    path = get_path(&to_free, head, str);
    if (invalid_path(path, str, shell))
        return 1;
    if (to_free == 1)
        free(path);
    if (!getcwd(newpwd, 256))
        return 1;
    update_value((head), "PWD", newpwd);
    return 2;
}

int previous_path(linked_list_t **head, shell_t *shell, char **old)
{
    char *save_old = getcwd(NULL, 0);
    char newpwd[256] = {0};

    if (!(*old))
        return 1;
    if (chdir((*old)) == -1) {
        mini_printf(2, "%s: %s\n", (*old), strerror(errno));
        shell->last_exit = 1;
        return 1;
    }
    if (!getcwd(newpwd, sizeof(char) * 256))
        return 1;
    *old = save_old;
    update_value((head), "PWD", newpwd);
    return 2;
}

int my_cd(char **array, linked_list_t *head, shell_t *shell)
{
    static char *old = NULL;

    if (array_len((const void **) array) >= 3) {
        mini_printf(2, "cd: Too many arguments.\n");
        shell->last_exit = 1;
        return 1;
    }
    if (array[1] && !my_strcmp(array[1], "-"))
        return previous_path(&head, shell, &old);
    return change_directory(array[1], &head, shell, &old);
}
