/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** input
*/
#include "line_edition.h"

static int move_cursor(termios_t *termios, int option)
{
    if (termios->pos < my_strlen(termios->line) && option)
        termios->pos++;
    if (termios->pos > 0 && !option)
        termios->pos--;
    return 0;
}

static int move_string(char *string, int start, int end, int option)
{
    if (start == end)
        return 0;
    for (int i = start; option == -1 && i < end; i++)
        string[i] = string[i + 1];
    for (int i = end; option == 1 && i > start; i--)
        string[i] = string[i - 1];
    return 0;
}

static int delete_character(termios_t *termios, int option)
{
    int len = my_strlen(termios->line);

    if (len == 0 || (!option && termios->pos == 0) ||
        (option && termios->pos >= len))
        return 0;
    if (!option) {
        termios->pos--;
        for (int i = termios->pos; i < len - 1; i++)
            termios->line[i] = termios->line[i + 1];
    } else
        for (int i = termios->pos; i < len - 1; i++)
            termios->line[i] = termios->line[i + 1];
    termios->line[len - 1] = '\0';
    return 0;
}

static int add_character(termios_t *termios)
{
    int len = my_strlen(termios->line);

    if (len == BUFFER_SIZE - 1)
        return 0;
    move_string(termios->line, termios->pos, len, 1);
    termios->line[termios->pos] = termios->input;
    termios->line[len + 1] = '\0';
    termios->pos++;
    return 0;
}

static int special_input(termios_t *termios)
{
    char code[3];

    if (read(0, &code[0], 1) <= 0 || read(0, &code[1], 1) <= 0)
        return 0;
    if (code[0] == CONTROL_SEQUENCE) {
        termios->input = code[1];
        if (termios->input == ARROW_UP || termios->input == ARROW_DOWN)
            return move_history(termios, termios->input == ARROW_UP);
        if (termios->input == ARROW_RIGHT || termios->input == ARROW_LEFT)
            return move_cursor(termios, termios->input == ARROW_RIGHT);
        if (read(0, &code[2], 1) <= 0)
            return 0;
        termios->input = code[2];
        if (code[1] == DELETE_TYPE && termios->input == DELETE_KEY)
            return delete_character(termios, 1);
    }
    return 0;
}

static int empty_string(char *str, int max_index)
{
    for (int i = 0; i < max_index; i++) {
        if (str[i] == '\0')
            return 1;
        if (str[i] != ' ' && str[i] != '\t')
            return 0;
    }
    return 1;
}

int handle_input(termios_t *termios)
{
    if (termios->input == '\n' || termios->input == '\r') {
        mini_printf(1, "\n");
        return 1;
    }
    if (termios->input == '\t' && !empty_string(termios->line, termios->pos))
        return auto_completion(termios);
    if (termios->input == BACKSPACE || termios->input == OLD_BACKSPACE)
        return delete_character(termios, 0);
    if (termios->input == SPECIAL)
        return special_input(termios);
    return add_character(termios);
}
