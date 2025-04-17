/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** handle_colors.c
*/

#include "my.h"

int change_prompt_color(info_shell_t *shell, char *color_name)
{
    for (int i = 0; colors[i].name != NULL; i++) {
        if (my_strcmp(colors[i].name, color_name) == 0) {
            free(shell->prompt_color);
            shell->prompt_color = my_strdup(colors[i].code);
            return 0;
        }
    }
    return -1;
}

void print_all_color(void)
{
    for (int i = 0; colors[i].name != NULL; i++) {
        mini_printf("%s%s%s\n", colors[i].code, colors[i].name,
            colors[8].code);
    }
}

int handle_color_command(char **args, info_shell_t *shell_i)
{
    if (my_strcmp(args[0], "color") != 0)
        return 0;
    if (args[1] == NULL) {
        print_all_color();
    } else {
        if (change_prompt_color(shell_i, args[1]) == -1) {
            my_printerr("Color not found. Available colors:\n");
            print_all_color();
        }
    }
    return 1;
}
