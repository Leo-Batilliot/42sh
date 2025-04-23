/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** line_edition
*/

#ifndef LINE_EDITION_H_
    #define LINE_EDITION_H_

    #include "my.h"

    #define SPECIAL 27
    #define CONTROL_SEQUENCE '['
    #define DELETE_TYPE '3'
    #define DELETE_KEY '~'
    #define ARROW_UP 'A'
    #define ARROW_DOWN 'B'
    #define ARROW_RIGHT 'C'
    #define ARROW_LEFT 'D'
    #define BACKSPACE 127
    #define OLD_BACKSPACE 8
    #define BUFFER_SIZE 1024

typedef struct termios_s {
    history_t *history;
    int history_index;
    char *history_line;
    int history_pos;
    list_t *env;
    char *prompt_color;
    char *line;
    char input;
    int pos;
} termios_t;

termios_t *init_termios(shell_t *shell);
int set_terminal_settings(int enable);
int free_termios(termios_t *termios);
int handle_input(termios_t *termios);
int auto_completion(termios_t *termios);
int move_history(termios_t *termios, int option);
void reset_termios_history(termios_t *termios, int *history);

#endif
