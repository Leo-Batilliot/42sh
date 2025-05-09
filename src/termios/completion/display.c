/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** display
*/

#include "line_edition.h"
#include <sys/ioctl.h>
#include <unistd.h>

// name :   refresh_window_size
// args :   completion struct
// use :    refresh the number of rows and cols according to the terminal size
int refresh_window_size(completion_t *completion)
{
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    completion->cols = w.ws_col / completion->max_len;
    if (completion->cols == 0)
        completion->cols = 1;
    completion->rows = (completion->len + completion->cols - 1) /
        completion->cols;
    if (completion->max_len > w.ws_col || completion->rows + 1 > w.ws_row)
        return 1;
    return 0;
}

// name :   refresh_completion_line
// args :   completion main struct
// use :    swaps the current line with the auto completing value at index
int refresh_completion_line(completion_t *completion)
{
    list_t *node = completion->list;

    for (int i = 0; node; i++) {
        if (i == completion->index) {
            my_free(completion->line);
            completion->line = my_strdup(node->value);
        }
        node = node->next;
    }
    return 0;
}

// name :   display_completion_options
// args :   completion struct
// use :    S.E
int display_completion_options(completion_t *completion)
{
    list_t *node = completion->list;

    for (int i = 0; i < completion->len && node; i++) {
        if (i % completion->cols == 0 && i != completion->len)
            mini_printf(1, "\n");
        if (i == completion->index)
            mini_printf(1, "%s%s%s", COLOR_HIGHLIGHT, node->value,
                COLOR_RESET);
        else
            mini_printf(1, "%s", node->value);
        for (int k = 0; k < completion->max_len - my_strlen(node->value); k++)
            mini_printf(1, " ");
        node = node->next;
    }
    completion->printed = 1;
    return 0;
}

// name :   update_command_line
// args :   termios struct, completion struct
// use :    print the current completed line
void update_command_line(termios_t *termios, completion_t *completion)
{
    print_prompt(termios->env, termios->prompt_color);
    if (completion->before)
        mini_printf(1, "%s", completion->before);
    if (completion->directory)
        mini_printf(1, "%s", completion->directory);
    if (completion->line)
        mini_printf(1, "%s", completion->line);
    if (completion->after)
        mini_printf(1, "%s", completion->after);
}

// name :   delete_print
// args :   completion struct
// use :    cleans the auto completion proposals from the terminal
int delete_print(completion_t *completion)
{
    mini_printf(1, "\r");
    if (completion->printed) {
        mini_printf(1, "\033[%dA", completion->rows);
        completion->printed = 0;
    }
    mini_printf(1, "%s", CLEAR_BELOW);
    return 0;
}
