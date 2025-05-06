/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin
*/

#include "shell.h"
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// name :   builtins
// args :   N.A
// use :    ptr to function for builtin related functions
const builtin_t builtins[] = {
    {"env", my_env},
    {"setenv", my_setenv},
    {"unsetenv", my_unsetenv},
    {"cd", my_cd},
    {"history", my_history},
    {"exit", my_exit},
    {"alias", alias},
    {"clean", clean},
    {"color", color},
    {"set", set},
    {"unset", unset},
    {"echo", my_echo},
    {"which", which},
    {"where", where},
    {"repeat", repeat},
    {NULL, NULL}
};

// name :   is_builtin
// args :   command array
// use :    S.E
int is_builtin(char *cmds)
{
    for (int i = 0; builtins[i].name; i++) {
        if (!strcmp(builtins[i].name, cmds))
            return 1;
    }
    return 0;
}

// name :   exec_builtin
// args :   array, shell main struct
// use :    search for a corresponding builtin function and return it if found
int exec_builtin(char **array, shell_t *shell)
{
    for (int i = 0; builtins[i].name; i++)
        if (!my_strcmp(array[0], builtins[i].name))
            return builtins[i].func(array, shell);
    return 0;
}
