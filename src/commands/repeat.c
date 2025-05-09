/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** repeat.c
*/

#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

// name: repeat
// args: array, shell
// use: executes a command multiple times based on the given count
int repeat(char **array, shell_t *shell)
{
    int count = 0;

    if (!array[1] || !array[2]) {
        mini_printf(1, "repeat: Too few arguments.\n");
        return 1;
    }
    count = atoi(array[1]);
    if (count <= 0) {
        mini_printf(1, "repeat: Badly formed number.\n");
        return 1;
    }
    for (int i = 0; i < count; i++)
        if (is_builtin(array[2]))
            exec_builtin(array + 2, shell);
        else {
            shell->root = parse_tokens(array + 2, 0,
            array_len((const void **)array) - 2, shell);
            execute_node(shell->root, shell->env_cpy, shell);
        }
    return 0;
}
