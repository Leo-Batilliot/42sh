/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** alias_parsing
*/
#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

// name :   append_array
// args :   address of new_array, address of size, string
// use :    add string to the end of new_array using realloc
static int append_array(char ***new_array, int *j, char *string)
{
    char **tmp = realloc((*new_array), sizeof(char *) * ((*j) + 2));

    if (!tmp) {
        free_array((void **)new_array);
        return -1;
    }
    (*new_array) = tmp;
    (*new_array)[(*j) + 1] = NULL;
    (*new_array)[(*j)] = my_strdup(string);
    if (!(*new_array)[(*j)]) {
        free_array((void **)(*new_array));
        return -1;
    }
    (*j)++;
    return 0;
}

// name :   add_alias
// args :   array, size, new_array
// use :    add every element of array_tmp at the end of new_array
static int add_alias(char **array_tmp, int *j, char ***new_array)
{
    if (!array_tmp)
        return free_array((void **)new_array) + 84;
    for (int k = 0; array_tmp[k]; k++)
        if (append_array(new_array, j, array_tmp[k]))
            return free_array((void **)array_tmp) + 84;
    return free_array((void **)array_tmp) + 1;
}

// name :   replace_new
// args :   adress of size, adress of new_array, str
// use :    replace alias info with the new one
static int replace_new(int *j, char ***new_array, char *name, shell_t *shell)
{
    char *string = NULL;
    char **array_tmp = NULL;
    alias_t *to_cmp = find_node(shell, name);

    if (!to_cmp)
        return 0;
    string = array_to_str(to_cmp->cmd);
    if (!string)
        return 1;
    array_tmp = split_str(string, " \t");
    my_free(string);
    return add_alias(array_tmp, j, new_array);
}

// name :   replace_alias
// args :   shell main struct, array
// use :    replace existing alias
char **replace_alias(shell_t *shell, char **array)
{
    int res = 0;
    char **new_array = NULL;
    int j = 0;

    if (!array || !my_strcmp("alias", array[0]))
        return array;
    for (int i = 0; array[i]; i++) {
        res = replace_new(&j, &new_array, array[i], shell);
        if (res == 1)
            continue;
        if (res == 84)
            return NULL;
        if (append_array(&new_array, &j, array[i]) == -1)
            return NULL;
    }
    if (new_array)
        new_array[j] = NULL;
    return new_array;
}
