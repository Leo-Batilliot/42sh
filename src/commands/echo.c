/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** echo.c
*/

#include "shell.h"
#include <stddef.h>

// name:    get_local_var
// args:    variable name, shell main struct
// use:     get the value of a local variable
static char *get_local_var(const char *name, shell_t *shell)
{
    for (list_t *node = shell->local_vars; node; node = node->next)
        if (!my_strcmp(node->key, name))
            return node->value;
    return NULL;
}

// name:    print_arg_with_expansion
// args:    argument, shell
// use:     print argument with variable expansion if needed
static void print_arg(char *arg, shell_t *shell)
{
    char *value = NULL;
    char *var_name = NULL;

    if (arg[0] == '$') {
        if (arg[1] == '?') {
            mini_printf(1, "%d", shell->last_exit);
            return;
        }
        var_name = arg + 1;
        value = get_local_var(var_name, shell);
        if (value)
            mini_printf(1, "%s", value);
        else
            mini_printf(2, "Variable %s non définie\n", var_name);
    } else
        mini_printf(1, "%s", arg);
}

// name:    my_echo
// args:    arguments, shell
// use:     implements echo command with local variable
int my_echo(char **args, shell_t *shell)
{
    if (!args[1]) {
        mini_printf(1, "\n");
        return 0;
    }
    for (int i = 1; args[i]; i++) {
        print_arg(args[i], shell);
        if (args[i + 1])
            mini_printf(1, " ");
    }
    mini_printf(1, "\n");
    return 0;
}
