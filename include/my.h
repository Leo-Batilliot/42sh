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
    #include <time.h>
    #include <fcntl.h>

    #define ERROR 1

/*--------------------*/
/* PROJECT STRUCTURES */
/*--------------------*/

typedef struct history_s {
    int index;
    char *time;
    char *cmd;
    char *full_line;
    struct history_s *next;
} history_t;

typedef struct linked_list_s {
    char *key;
    char *value;
    struct linked_list_s *next;
} linked_list_t;

typedef struct redirect_s {
    int status;
    int i;
    char *file;
} redirect_t;

typedef struct args_s {
    redirect_t *redir;
    char **args;
    int count_red;
    int is_pipe;
    struct args_s *next;
} args_t;

typedef struct alias_s {
    char **cmd;
    char *name;
    struct alias_s *next;
} alias_t;

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
    int count;
    alias_t *alias;
    history_t *head;
    list_t *list;
} shell_t;

typedef int (*builtin_func_t)(char **, linked_list_t **, shell_t *);

typedef struct {
    char *name;
    builtin_func_t func;
} builtin_t;

/*---------------------*/
/*    LIB FUNCTIONS    */
/*---------------------*/

/*    INIT    */
list_t *init_list(void);

/*    FREE    */
int free_array(void **);
int my_free(void *);

/*    OTHERS    */
char *put_spaces(int, int);
int array_len(const void **);
char *my_strchr(char *, int);
char *my_strdup(char const *);
char *my_strcpy(char *, char const *);
char *my_strcat(char *, char const *);
int count_word(const char *, char *);
char **split_str(const char *, char *);
int my_strlen(char const *);
int my_strcmp(char const *, char const *);
int is_delim(const char);
int is_separator(const char, char *);
char *array_to_str(char **array);
int mini_printf(int output, char *format, ...);

/*---------------------*/
/*   UTILS FUNCTIONS   */
/*---------------------*/

/*    INIT    */
char **linked_list_to_array(linked_list_t *);
int load_alias(shell_t *);
int load_history(shell_t *);
linked_list_t *init_env(char **);

/*    FREE    */
int free_list(linked_list_t *);

/*    OTHERS    */
int add_node_to_history(shell_t *, char *);
int save_file(shell_t *);
int add_node(shell_t *shell, char **);
int add_to_history(shell_t *, char *);
int is_operator(const char *);
int is_builtin(char **);
char *get_env_value(const char *, linked_list_t *);
int print_error(shell_t *, int);
char **my_env_cpy(char **);
int write_alias(shell_t *);
alias_t *find_node(shell_t *, char *);

/*---------------------*/
/*  PROJECT FUNCTIONS  */
/*---------------------*/

/*    INIT    */
args_t *init_cmd(char **);
shell_t *init_shell(char **);

/*    FREE    */
int free_shell(shell_t *shell);
int free_args_list(list_t *list, int opt);

/*    OTHERS    */
int signal_error(pid_t, shell_t *, int[2], args_t *);
void print_env(linked_list_t **);
void write_history(shell_t *);

/*    MAIN FUNCTIONS    */
int execute_command_list(shell_t *, linked_list_t *);
int set_redirection_file(char **, shell_t *, args_t **, int *);
int redirection(args_t *tmp, shell_t *shell);
int parse_args(shell_t *);
int pipe_builtin(shell_t *, args_t *, linked_list_t **, int[2]);
int builtin(shell_t *, args_t *, linked_list_t **, int[2]);
int execute_cmd(shell_t *, args_t *, linked_list_t **);

/*    COMMANDS    */
int my_history(char **, linked_list_t **, shell_t *);
int alias(char **, linked_list_t **, shell_t *);
int my_cd(char **, linked_list_t **, shell_t *);
int my_env(char **, linked_list_t **, shell_t *);
int my_setenv(char **, linked_list_t **, shell_t *);
int my_unsetenv(char **, linked_list_t **, shell_t *);
int my_exit(char **, linked_list_t **, shell_t *);
int clean(char **, linked_list_t **, shell_t *);

#endif
