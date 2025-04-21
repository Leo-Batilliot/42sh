/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** alias
*/

#include "my.h"

static void print_space_alias(alias_t *cur, int k)
{
    if (cur->cmd[k + 1])
        mini_printf(1, " ");
}

static int print_alias(shell_t *shell)
{
    for (alias_t *cur = shell->alias; cur; cur = cur->next) {
        mini_printf(1, "%s='", cur->name);
        if (!cur->cmd) {
            mini_printf(1, "'\n");
            continue;
        }
        for (int k = 0; cur->cmd[k]; k++) {
            mini_printf(1, "%s", cur->cmd[k]);
            print_space_alias(cur, k);
        }
        mini_printf(1, "'\n");
    }
    return 0;
}

alias_t *find_node(shell_t *shell, char *name)
{
    for (alias_t *cur = shell->alias; cur; cur = cur->next) {
        if (!strcmp(cur->name, name))
            return cur;
    }
    return NULL;
}

static int cpy_node(char **array, alias_t **node)
{
    int count = 0;

    (*node)->name = strdup(array[0]);
    if (!(*node)->name)
        return 84;
    if (!array[1]) {
        (*node)->cmd = NULL;
        return 0;
    }
    count = array_len((const void **)&array[1]);
    (*node)->cmd = malloc(sizeof(char *) * (count + 1));
    if (!(*node)->cmd)
        return 84;
    for (int i = 0; i < count; i++) {
        (*node)->cmd[i] = strdup(array[i + 1]);
        if (!(*node)->cmd[i])
            return 84;
    }
    (*node)->cmd[count] = NULL;
    return 0;
}

int add_node(shell_t *shell, char **array)
{
    alias_t *node = find_node(shell, array[0]);

    if (!node) {
        node = malloc(sizeof(alias_t));
        if (!node)
            return 84;
        cpy_node(array, &node);
        node->next = shell->alias;
        shell->alias = node;
    } else {
        free(node->name);
        for (int i = 0; node->cmd && node->cmd[i]; i++)
            free(node->cmd[i]);
        free(node->cmd);
        cpy_node(array, &node);
    }
    return 0;
}

static int append_split_to_array(char ***dest,
    int *j, char *to_split)
{
    char **split = split_str(to_split, "= '\t");

    if (!split || !split[0]) {
        free_array((void **)split);
        return 84;
    }
    for (int k = 0; split[k]; k++) {
        (*dest)[*j] = my_strdup(split[k]);
        if (!(*dest)[*j]) {
            free_array((void **)split);
            return 84;
        }
        (*j)++;
    }
    free_array((void **)split);
    return 0;
}

static char **init_new_array(int size)
{
    char **array = malloc(sizeof(char *) * (size + 1));

    if (array)
        array[0] = NULL;
    return array;
}

static int add_to_alias_list(shell_t *shell, char **array)
{
    int count = array_len((const void **)array) + 1;
    int j = 0;
    char **new_array = init_new_array(count);

    if (!new_array)
        return 84;
    for (int i = 1; array[i]; i++) {
        if (append_split_to_array(&new_array, &j, array[i]) == 84) {
            free_array((void **)new_array);
            return 84;
        }
    }
    new_array[j] = NULL;
    if (add_node(shell, new_array) == 84)
        return 84;
    return 0;
}

int alias(char **array, linked_list_t **head, shell_t *shell)
{
    (void)head;
    if (array[1])
        return add_to_alias_list(shell, array);
    else
        return print_alias(shell);
    return 0;
}
