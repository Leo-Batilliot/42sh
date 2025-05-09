/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-gabin.wilson
** File description:
** handle_redirections
*/

#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

// name :   is_redirect
// args :   to_cmp
// use :    for found possibly redirection
int is_redirect(char *to_cmp)
{
    char *array[] = {">", "<<", ">>", "<"};

    for (unsigned int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        if (!strcmp(to_cmp, array[i]))
            return 1;
    }
    return 0;
}

// name :   check_redir_conditions
// args :   i, tokens, start, shell
// use :    check stability of file redirection
static node_t *check_redir_conditions(int i, char **tokens,
    int start, shell_t *shell)
{
    if (!tokens[i + 1])
        return missing_name_message(shell);
    if (i == start)
        return null_cmd(shell);
    return NULL;
}

// name :   create_redirection_node
// args :   i, tokens, start, shell
// use :    create node of redirection for tree
static node_t *create_redirection_node(int i, char **tokens,
    int start, shell_t *shell)
{
    node_t *redir_node = malloc(sizeof(node_t));

    if (!redir_node)
        return NULL;
    redir_node->type = NODE_REDIR;
    redir_node->redir_type = strdup(tokens[i]);
    if (!redir_node->redir_type)
        return NULL;
    redir_node->left = parse_tokens(tokens, start, i, shell);
    if (!redir_node->left)
        return NULL;
    redir_node->file = strdup(tokens[i + 1]);
    if (!redir_node->file)
        return NULL;
    redir_node->right = NULL;
    redir_node->op = NULL;
    return redir_node;
}

// name :   create_redir
// args :   i, tokens, start, shell
// use :    create instance of redirection
node_t *create_redir(int i, char **tokens,
    int start, shell_t *shell)
{
    node_t *error = NULL;
    node_t *redir_node = NULL;

    if (is_redirect(tokens[i])) {
        error = check_redir_conditions(i, tokens, start, shell);
        if (shell->err == 1)
            return error;
        redir_node = create_redirection_node(i, tokens, start, shell);
        shell->err = 1;
        return redir_node;
    }
    return NULL;
}

// name :   parsing_redir
// args :   tokens, start, end, shell
// use :    parsing for redirection
node_t *parsing_redir(char **tokens, int start, int end, shell_t *shell)
{
    node_t *redir_node = NULL;

    for (int i = start; i < end; i++) {
        redir_node = create_redir(i, tokens, start, shell);
        if (shell->err == 1)
            return redir_node;
    }
    return NULL;
}

// name :   exec_redir
// args :   node, fd
// use :    exec redirection with file descriptor
static int exec_redir(node_t *node, int *fd)
{
    if (!strcmp(node->redir_type, ">")) {
        (*fd) = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2((*fd), STDOUT_FILENO);
    }
    if (!strcmp(node->redir_type, ">>")) {
        (*fd) = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2((*fd), STDOUT_FILENO);
    }
    if (!strcmp(node->redir_type, "<")) {
        (*fd) = open(node->file, O_RDONLY);
        dup2((*fd), STDIN_FILENO);
    }
    return 0;
}

// name :   restore_fd
// args :   saved_stdin, saved_stdout
// use :    restore file descriptor at state initialize
static void restore_fd(int saved_stdin, int saved_stdout)
{
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}

// name :   exec_node_redir
// args :   node, env_cpy,shell
// use :    exec redirection
int exec_node_redir(node_t *node, char **env_cpy, shell_t *shell)
{
    int fd = 0;
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    if (saved_stdin < 0 || saved_stdout < 0)
        return 0;
    exec_redir(node, &fd);
    if (fd < 0) {
        dup2(saved_stdin, STDIN_FILENO);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdin);
        close(saved_stdout);
        return 0;
    }
    close(fd);
    execute_node(node->left, env_cpy, shell);
    restore_fd(saved_stdin, saved_stdout);
    return 0;
}
