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

typedef struct {
    int i;
    int x;
    int y;
    int add;
    int must;
} parser_t;

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
    char *prompt_color;
    int ignoreeof;
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

typedef struct script_ctx_s {
    char **if_block;
    int if_mode;
    int block_index;
} script_ctx_t;

typedef struct expansion_ctx_s {
    size_t *i;
    size_t *j;
    char **buffer;
} expansion_ctx_t;

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
char *my_strndup(char const *, int);
int rev_case_strncmp(char *, char *, int);
int my_case_strncmp(char *, char *, int);
char *strcpy_from(char *, char *, int);
char *my_null_strdup(char *);
int spaces_count(int, int);
int array_len(const void **);
char **array_dup(char **);
char *my_strchr(char *, int);
char *my_strdup(char const *);
char *my_strcpy(char *, char const *);
char *my_strcat(char *, char const *);
char **split_str(const char *, char *);
char **simple_split_str(char *, char *);
int my_strlen(char const *);
int my_strcmp(char const *, char const *);
int is_delim(const char);
int is_separator(const char, char *);
char *array_to_str(char **);
int mini_printf(int, char *, ...);
int my_strncmp(const char *, const char *, int);
int str_is_digits(const char *);
int my_atoi(const char *);
int is_delim(const char c);
int is_keep_delim(char c);
int is_keep_alone(char c);
int is_separator(const char c, char *ope);
char **my_str_to_word_array(char const *str, char const *sep);

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
int free_list(list_t *);

/*    OTHERS    */
void handle_signals(void);
char **replace_alias(shell_t *, char **);
int add_node_to_history(shell_t *, char *, char *);
int save_file(shell_t *);
int add_node(shell_t *, char **);
int add_to_history(shell_t *, char *);
int is_operator(const char *);
char *get_env_value(const char *, list_t *);
int is_builtin(char *);
int print_error(shell_t *, int);
char **my_env_cpy(char **);
int write_alias(shell_t *);
alias_t *find_node(shell_t *, char *);
char **create_default_env(char **);
char **globbings(char **);

/*---------------------*/
/*  PROJECT FUNCTIONS  */
/*---------------------*/

/*    INIT    */
shell_t *init_shell(char **);
node_t *init_node(void);

/*    FREE    */
void free_and_exit(shell_t *, int);
int free_history(shell_t *);
void free_nodes(node_t *);
int clear_all_alias(shell_t *);

/*    OTHERS    */
void print_env(list_t *);
void write_history(shell_t *);
void *null_cmd(shell_t *);
void *missing_name_message(shell_t *);

/*    MAIN FUNCTIONS    */
int execute_command_list(shell_t *);
int parse_args(shell_t *);
int exec_builtin(char **, shell_t *);
void print_signal(shell_t *, int *);
int is_operator(const char *);
node_t *parse_tokens(char **, int, int, shell_t *);
void execute_node(node_t *, char **, shell_t *);
int get_command_path(char **, shell_t *);
node_t *parsing_redir(char **, int, int, shell_t *);
void exec_node_op(node_t *, shell_t *, char **);
int exec_node_redir(node_t *, char **, shell_t *);
void exec_pipe(node_t *, shell_t *, char **);
int exec_node_cmd(node_t *, shell_t *, int, char **);

/*    COMMANDS    */
int my_history(char **, shell_t *);
int alias(char **, shell_t *);
int unalias(char **array, shell_t *shell);
int my_cd(char **, shell_t *);
int my_env(char **, shell_t *);
int my_setenv(char **, shell_t *);
int my_unsetenv(char **, shell_t *);
int my_exit(char **, shell_t *);
int color(char **, shell_t *);
int clean(char **, shell_t *);
int unset(char **, shell_t *);
int set(char **, shell_t *);
int my_echo(char **, shell_t *);
int which(char **, shell_t *);
int where(char **, shell_t *);
int repeat(char **, shell_t *);

int termios_main(shell_t *);

/*---------------------*/
/* SCRIPTING FUNCTIONS */
/*---------------------*/
int is_script(const char *filename);
int execute_script(const char *path, shell_t *shell, node_t *node);
char *extract_condition(char *line);
char *expand_variables(char *line, shell_t *shell);
char *get_variable_value(shell_t *shell, const char *var_name);
int evaluate_condition(const char *condition, shell_t *shell);
void trim_line(char *line);

#endif
