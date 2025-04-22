/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <string.h>
    #include <signal.h>
    #include <errno.h>
    #include <sys/types.h>
    #include <stdbool.h>
    #include <fcntl.h>

    #define ERROR 1

typedef struct linked_list_s {
    char *key;
    char *value;
    struct linked_list_s *next;
} linked_list_t;

typedef struct redirect_s {
    int statu;
    int i;
    char *file;
} redirect_t;

typedef struct color_s {
    char *name;
    char *code;
} color_t;

static const color_t colors[] = {
    {"black", "\033[0;30m"},
    {"red", "\033[0;31m"},
    {"green", "\033[0;32m"},
    {"yellow", "\033[0;33m"},
    {"blue", "\033[0;34m"},
    {"purple", "\033[0;35m"},
    {"cyan", "\033[0;36m"},
    {"white", "\033[0;37m"},
    {"reset", "\033[0m"},
    {NULL, NULL}
};

typedef struct args_s {
    redirect_t *redir;
    char **args;
    int count_red;
    int is_pipe;
    struct args_s *next;
} args_t;

typedef struct list_s {
    struct args_s *head;
} list_t;

typedef struct {
    char *line;
    char *path;
    char **env_cpy;
    char *save_old;
    size_t size;
    int res;
    int last_exit;
    int tmp_red;
    int index;
    int prev;
    int index_parse;
    int pipefd[2];
    list_t *list;
    char *prompt_color;
} info_shell_t;

// lib
char *my_strchr(char *, int);
char *my_strdup(char const *);
char *my_strcat(char *, char const *);
char *my_strcpy(char *, char const *);
char **my_str_to_word_array_sep(const char *, char *);
int my_put_nbr(int);
int my_getnbr(char *);
int my_strlen(char const *);
int my_putstr(char const *);
int mini_printf(const char *, ...);
int my_printerr(const char *, ...);
int my_strcmp(char const *, char const *);
list_t *create_list(void);
void my_putchar(char);

// utils
char **my_env_cpy(char **);
char *get_path(char *, char *, char *);
char **linked_list_to_array(linked_list_t *);
char *get_env_value(const char *, linked_list_t *);
linked_list_t *my_parse_env(char **);
linked_list_t *print_prompt(char **);
void print_env(linked_list_t *);
void free_all(char **, char **);
args_t *add_cmd(char **);
bool is_operator(const char *str);
int is_bulltins(char *);
int parse_args(info_shell_t *);
int null_message(info_shell_t *);
int message_error(info_shell_t *);
int create_pipe(int[2], args_t *);
int gest_fd(int, info_shell_t *, args_t *, int);
int handle_heredocs(args_t *, int, info_shell_t *);
int gest_redir(char **, info_shell_t *, args_t **, int *);
int my_unsetenv(char **, linked_list_t **, info_shell_t *);
int commands_env(char **, linked_list_t *, info_shell_t *);
int get_cur_pass(linked_list_t **, char **, info_shell_t *);
int gest_bef_signal(pid_t, info_shell_t *, int[2], args_t *);
int gest_first_cmd(int *i, args_t **, info_shell_t *, char **);
int my_gest_exec(info_shell_t *, args_t *tmp, linked_list_t **);
int gest_cur_commands(char **, linked_list_t *, info_shell_t *);
int pipe_w_bulltins(info_shell_t *, args_t *, linked_list_t **, int[2]);
int handle_builtins(info_shell_t *, char **, args_t *, linked_list_t **);
int handle_color_command(char **args, info_shell_t *shell_i);

//// commands
int handle_red(args_t *tmp, info_shell_t *shell_i);
int my_cd(char **, linked_list_t *, info_shell_t *);
int set_env(linked_list_t **, char **, info_shell_t *);
int my_print_env(char **, info_shell_t *, linked_list_t *);
void my_exit(char **);

#endif
