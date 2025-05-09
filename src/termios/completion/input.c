/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** input
*/

#include "line_edition.h"
#include <unistd.h>

// name :   column
// args :   completion struct, option : up(1) or down(0)
// use :    find the next completion index in the current column
int column(completion_t *completion, int direction)
{
    if (!direction) {
        if (completion->index + completion->cols >= completion->len)
            completion->index = ((completion->index + 1) % completion->cols);
        else
            completion->index += completion->cols;
        return refresh_completion_line(completion);
    }
    if (completion->index - completion->cols < 0) {
        completion->index = completion->index - 1 < 0 ?
            completion->cols - 1 : completion->index - 1;
        for (; completion->index + completion->cols < completion->len;)
            completion->index += completion->cols;
    } else
        completion->index -= completion->cols;
    return refresh_completion_line(completion);
}

// name :   line
// args :   completion struct, option : right(1) or left(0)
// use :    find the next completion index in the current line
int line(completion_t *completion, int direction)
{
    if (direction)
        completion->index++;
    else
        completion->index--;
    if (completion->index < 0)
        completion->index = completion->len - 1;
    if (completion->index >= completion->len)
        completion->index = 0;
    return refresh_completion_line(completion);
}

// name :   arrow_input
// args :   completion struct
// use :    S.E
int arrow_input(completion_t *completion)
{
    char code[2];
    char input;

    if (read(0, &code[0], 1) <= 0 || read(0, &code[1], 1) <= 0)
        return 0;
    if (code[0] == CONTROL_SEQUENCE) {
        input = code[1];
        if (input == ARROW_UP || input == ARROW_DOWN)
            return column(completion, input == ARROW_UP);
        if (input == ARROW_RIGHT || input == ARROW_LEFT)
            return line(completion, input == ARROW_RIGHT);
    }
    return 0;
}

// name :   auto_completion_input
// args :   termios struct, completion struct
// use :    S.E
int auto_completion_input(termios_t *termios, completion_t *completion)
{
    if (termios->input == '\n' || termios->input == '\r' ||
        termios->input == BACKSPACE || termios->input == OLD_BACKSPACE)
        return replace(termios, completion);
    if (termios->input == '\t') {
        completion->index = (completion->index + 1) % completion->len;
        refresh_completion_line(completion);
        return 0;
    }
    if (termios->input == SPECIAL) {
        arrow_input(completion);
        refresh_completion_line(completion);
        return 0;
    }
    replace(termios, completion);
    handle_input(termios);
    return 1;
}
