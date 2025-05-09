/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** line_edition
*/

#ifndef LINE_EDITION_H_
    #define LINE_EDITION_H_

    #include "shell.h"

    /*    INPUTS    */
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

    /*    OTHERS    */
    #define BUFFER_SIZE 1024
    #define COMMAND 1
    #define ELEMENTS 2
    #define COLOR_RESET "\033[0m"
    #define COLOR_HIGHLIGHT "\033[7m"
    #define CLEAR_BELOW "\033[J"

typedef struct completion_s {
    char *line;
    int index;
    list_t *list;
    int len;
    char *start;
    char *end;
    char *before;
    char *after;
    char *directory;
    int cols;
    int rows;
    int max_len;
    int printed;
    int type;
} completion_t;

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
    int ignoreeof;
} termios_t;

termios_t *init_termios(shell_t *shell);
int set_terminal_settings(int enable);
int free_termios(termios_t *termios);
int handle_input(termios_t *termios);
int auto_completion(termios_t *termios);
int move_history(termios_t *termios, int option);
int print_prompt(list_t *env, char *color);
void reset_termios_history(termios_t *termios, int *history);

// Auto COmpletion

int str_contain(char *, char);
char *add_slash_to_dir(char *, char *);
int not_in(char *, completion_t *);
int get_max_length(completion_t *);
int replace(termios_t *, completion_t *);
int refresh_window_size(completion_t *);
int auto_completion_input(termios_t *, completion_t *);
int delete_print(completion_t *);
void update_command_line(termios_t *, completion_t *);
int display_completion_options(completion_t *);
completion_t *init_completion(termios_t *);
int free_completion(completion_t *);
int refresh_completion_line(completion_t *);
int get_directory(completion_t *);
int type(char *, int, char *, char *);
char *get_str(char *, int, int *, char *);
int fill_completion_list(completion_t *, termios_t *);

#endif
