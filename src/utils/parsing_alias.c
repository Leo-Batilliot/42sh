/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** alias_parsing
*/
#include "my.h"

static int append_array(char ***new_array, int *j, char *string)
{
    char **tmp = realloc((*new_array), sizeof(char *) * ((*j) + 2));

    if (!tmp) {
        free_array((void **)new_array);
        return -1;
    }
    (*new_array) = tmp;
    (*new_array)[(*j) + 1] = NULL;
    (*new_array)[(*j)] = strdup(string);
    if (!(*new_array)[(*j)]) {
        free_array((void **)(*new_array));
        return -1;
    }
    (*j)++;
    return 0;
}

static int add_alias(char **array_tmp, int *j, char ***new_array)
{
    int res = 0;

    for (int k = 0; array_tmp[k]; k++) {
        res = append_array(new_array, j, array_tmp[k]);
        if (res == -1)
            return 84;
    }
    return 0;
}

static int replace_new(int *j, char ***new_array,
    char *find_str, shell_t *shell)
{
    char *string = NULL;
    char **array_tmp = NULL;
    alias_t *to_cmp = find_node(shell, find_str);

    if (to_cmp) {
        string = array_to_str(to_cmp->cmd);
        if (!string)
            return 1;
        array_tmp = split_str(string, " \t");
        if (add_alias(array_tmp, j, new_array) == 84)
            return 84;
        return 1;
    }
    return 0;
}

char **replace_alias(shell_t *shell, char **array)
{
    int res = 0;
    char **new_array = NULL;
    int j = 0;

    if (!array || !strcmp("alias", array[0]))
        return array;
    for (int i = 0; array[i]; i++) {
        res = replace_new(&j, &new_array, array[i], shell);
        if (res == 1)
            continue;
        if (res == 84)
            return NULL;
        res = append_array(&new_array, &j, array[i]);
        if (res == -1)
            return NULL;
    }
    if (new_array)
        new_array[j] = NULL;
    return new_array;
}
