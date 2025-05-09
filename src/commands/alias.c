/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** alias
*/

#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

// name :   print_space_alias
// args :   current alias, index
// use :    prints a space if the current command arg is not the last
static void print_space_alias(alias_t *cur, int k)
{
    if (cur->cmd[k + 1])
        mini_printf(1, " ");
}

// name :   print_alias
// args :   shell main struct
// use :    print the alias list
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

// name :   find_node
// args :   shell main struct, alias name
// use :    return the alias using the given name if it exists
alias_t *find_node(shell_t *shell, char *name)
{
    for (alias_t *cur = shell->alias; cur; cur = cur->next)
        if (!my_strcmp(cur->name, name))
            return cur;
    return NULL;
}

// name :   cpy_node
// args :   an array, a node
// use :    cpy the array data in node
static int cpy_node(char **array, alias_t **node)
{
    int count = 0;

    (*node)->name = my_strdup(array[0]);
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
        (*node)->cmd[i] = my_strdup(array[i + 1]);
        if (!(*node)->cmd[i])
            return 84;
    }
    (*node)->cmd[count] = NULL;
    return 0;
}

// name :   add_node
// args :   shell main struct, array
// use :    look for duplicate and replace/init a new node according to it
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
        my_free(node->name);
        free_array((void **)node->cmd);
        cpy_node(array, &node);
    }
    return 0;
}

// name :   append_split_to_array
// args :   address of destination, adress of index, string
// use :    copy the split_str of the string in the destination after the index
static int append_split_to_array(char ***dest,
    int *j, char *to_split)
{
    char **split = simple_split_str(to_split, "= '\t");

    if (!split || !split[0])
        return free_array((void **)split) + 84;
    for (int k = 0; split[k]; k++) {
        (*dest)[*j] = my_strdup(split[k]);
        if (!(*dest)[*j])
            return free_array((void **)split) + 84;
        (*j)++;
    }
    return free_array((void **)split);
}

// name :   init_new_array
// args :   size
// use :    allocate an array according to given size
static char **init_new_array(int size)
{
    char **array = malloc(sizeof(char *) * (size + 1));

    if (array)
        array[0] = NULL;
    return array;
}

// name :   add_to_alias_list
// args :   shell main struct, an array
// use :    add/replace an alias using the given array
static int add_to_alias_list(shell_t *shell, char **array)
{
    int count = array_len((const void **)array) + 1;
    int j = 0;
    char **new_array = init_new_array(count);

    if (!new_array)
        return 84;
    for (int i = 1; array[i]; i++)
        if (append_split_to_array(&new_array, &j, array[i]) == 84)
            return free_array((void **)new_array) + 84;
    new_array[j] = NULL;
    if (add_node(shell, new_array) == 84)
        return free_array((void **)new_array) + 84;
    return free_array((void **)new_array);
}

// name :   alias
// args :   array, main shell struct
// use :    add/replace an alias or print the alias list
int alias(char **array, shell_t *shell)
{
    if (array[1])
        return add_to_alias_list(shell, array);
    else
        return print_alias(shell);
    return 0;
}
