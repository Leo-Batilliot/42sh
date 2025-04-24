/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** handle_colors.c
*/

#include "shell.h"

// name :   check_color
// args :   shell main struct, color name, index
// use :    changes the prompt color if the current color is the name entered
static int check_color(shell_t *shell, char *color_name, int i)
{
    if (!my_strcmp(colors[i].name, color_name)) {
        my_free(shell->prompt_color);
        shell->prompt_color = my_strdup(colors[i].code);
        if (!shell->prompt_color)
            return -1;
        return 1;
    }
    return 0;
}

// name :   change_prompt_color
// args :   shell main struct, color name
// use :    loops through colors and changes the prompt color
static int change_prompt_color(shell_t *shell, char *color_name)
{
    int res = 0;

    for (int i = 0; colors[i].name; i++) {
        res = check_color(shell, color_name, i);
        if (res == 1)
            return 0;
        if (res == -1)
            return -1;
    }
    return -1;
}

// name :   print_all_color
// args :   N.A
// use :    S.E
static int print_all_color(void)
{
    for (int i = 0; colors[i].name; i++)
        mini_printf(1, "%s%s%s\n", colors[i].code, colors[i].name,
            colors[8].code);
    return 1;
}

// name :   handle_color_command
// args :   array, shell main_struct
// use :    print colors or change the color depending on the array's data
int color(char **args, shell_t *shell)
{
    if (!args[1])
        return print_all_color();
    if (change_prompt_color(shell, args[1]) == -1) {
        mini_printf(1, "Color not found. Available colors:\n");
        print_all_color();
    }
    return 1;
}
