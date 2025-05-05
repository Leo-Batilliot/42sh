/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include <sys/types.h>

/*--------------------*/
/* PROJECT STRUCTURES */
/*--------------------*/

typedef struct history_s {
    int index;
    char *time;
    char *cmd;
    struct history_s *next;
} history_t;

typedef struct list_s {
    char *key;
    char *value;
    struct list_s *next;
} list_t;

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
    int param;
    struct args_s *next;
} args_t;

typedef struct alias_s {
    char **cmd;
    char *name;
    struct alias_s *next;
} alias_t;

    #define NODE_CMD 1
    #define NODE_OP 2
    #define NODE_SUBSHELL 3
    #define NODE_REDIR 4

typedef struct node_s {
    int type;
    char *op;
    char **argv;
    struct node_s *left;
    struct node_s *right;
    char *redir_type;
    char *file;
} node_t;

typedef struct {
    char *path;
    char *line;
    char **env_cpy;
    char *previous_pwd;
    int last_exit;
    int param;
    int err;
    int tmp_red;
    int prev;
    int index_parse;
    node_t *root;
    alias_t *alias;
    list_t *env;
    list_t *local_vars;
    history_t *history;
    args_t *args;
    char *prompt_color;
} shell_t;

typedef int (*builtin_func_t)(char **, shell_t *);

typedef struct {
    char *name;
    builtin_func_t func;
} builtin_t;

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
    {((void *)0), ((void *)0)}
};

/*---------------------*/
/*    LIB FUNCTIONS    */
/*---------------------*/

/*    INIT    */

/*    FREE    */
int free_array(void **);
int my_free(void *);

/*    OTHERS    */
int spaces_count(int, int);
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
char *array_to_str(char **);
int mini_printf(int, char *, ...);
int my_strncmp(const char *, const char *, int);
int str_is_digits(const char *);
int my_atoi(const char *);

/*---------------------*/
/*   UTILS FUNCTIONS   */
/*---------------------*/

/*    INIT    */
char **list_to_array(list_t *);
int load_alias(shell_t *);
int load_history(shell_t *);
int load_file(shell_t *);
list_t *init_env(char **);

/*    FREE    */

/*    OTHERS    */
char **replace_alias(shell_t *, char **);
int add_node_to_history(shell_t *, char *, char *);
int save_file(shell_t *);
int add_node(shell_t *, char **);
int add_to_history(shell_t *, char *);
int is_operator(const char *);
char *get_env_value(const char *, list_t *);
int is_builtin(char **);
int print_error(shell_t *, int);
char **my_env_cpy(char **);
int write_alias(shell_t *);
alias_t *find_node(shell_t *, char *);
char **globbins(char **);

/*---------------------*/
/*  TERMIOS FUNCTIONS  */
/*---------------------*/

/*    INIT    */

/*    FREE    */

/*    OTHERS    */

/*---------------------*/
/*  PROJECT FUNCTIONS  */
/*---------------------*/

/*    INIT    */
args_t *init_cmd(char **);
shell_t *init_shell(char **);

/*    FREE    */
int free_args_list(args_t *list);
void free_and_exit(shell_t *shell, int return_value);
int free_history(shell_t *shell);

/*    OTHERS    */
int signal_error(pid_t, shell_t *, int[2], args_t *);
void print_env(list_t *);
void write_history(shell_t *);
void *null_cmd(shell_t *shell);
void *missing_name_message(shell_t *shell);

/*    MAIN FUNCTIONS    */
int execute_command_list(shell_t *);
int set_redirection_file(char **array, shell_t *shell, args_t **cur, int *);
int redirection(args_t *tmp, shell_t *shell);
int parse_args(shell_t *);
int pipe_builtin(shell_t *, args_t *, int[2]);
int builtin(shell_t *, args_t *, int[2]);
int execute_cmd(shell_t *, args_t *);
int exec_builtin(char **array, shell_t *shell);
void print_signal(shell_t *shell, int *status);
int is_operator(const char *str);
node_t *parse_tokens(char **tokens, int start, int end, shell_t *shell);
void execute_node(node_t *node, char **env_cpy, shell_t *shell);
int get_command_path(char **array, shell_t *shell);
node_t *parsing_redir(char **tokens, int start, int end, shell_t *shell);
void exec_node_op(node_t *node, shell_t *shell, char **env_cpy);
int exec_node_redir(node_t *node, char **env_cpy, shell_t *shell);
void exec_pipe(node_t *node, shell_t *shell, char **env_cpy);
int exec_node_cmd(node_t *node, shell_t *shell, int status, char **env_cpy);

/*    COMMANDS    */
int my_history(char **, shell_t *);
int alias(char **, shell_t *);
int my_cd(char **, shell_t *);
int my_env(char **, shell_t *);
int my_setenv(char **, shell_t *);
int my_unsetenv(char **, shell_t *);
int my_exit(char **, shell_t *);
int color(char **, shell_t *);
int clean(char **, shell_t *);
int unset(char **args, shell_t *shell);
int set(char **args, shell_t *shell);
int my_echo(char **args, shell_t *shell);

int termios_main(shell_t *shell);

#endif
