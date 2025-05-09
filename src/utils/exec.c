/*
** EPITECH PROJECT, 2025
** my gest exec
** File description:
** my_gest_exec
*/

#include "shell.h"
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

// name :   print_signal
// args :   shell main struct
// use :    S.E
void print_signal(shell_t *shell, int *status)
{
    int term_signal = WTERMSIG(*status);

    if (term_signal == SIGFPE)
        mini_printf(2, "Floating exception");
    else
        mini_printf(2, "%s", strsignal(term_signal));
    if (WCOREDUMP(*status))
        mini_printf(2, " (core dumped)");
    mini_printf(2, "\n");
    shell->last_exit = 128 + term_signal;
}

// name :   exec_cmd
// args :   shell, node, status, env_cpy
// use :    exec cmd for all
void exec_cmd(shell_t *shell, node_t *node, int status, char **env_cpy)
{
    pid_t pid = fork();

    if (pid == 0) {
        if (execve(shell->path, node->argv, env_cpy) == -1) {
            mini_printf(2, "%s: ", shell->path);
            mini_printf(2, "Exec format error. Binary file not executable.\n");
            shell->last_exit = 1;
            exit(1);
        }
    } else {
        if (waitpid(pid, &status, 0) == -1)
            return;
        if (WIFEXITED(status))
            shell->last_exit = WEXITSTATUS(status);
        if (WIFSIGNALED(status))
            print_signal(shell, &status);
    }
}

// name :   try_to_access
// args :   command, shell main struct
// use :    S.E
static int try_to_access(char *path, shell_t *shell)
{
    struct stat file_stat;

    if (stat(path, &file_stat) == -1) {
        mini_printf(2, "%s: Command not found.\n", path);
        shell->last_exit = 1;
        return -1;
    }
    if (S_ISDIR(file_stat.st_mode)) {
        mini_printf(2, "%s: Permission denied.\n", path);
        shell->last_exit = 1;
        return -1;
    }
    if (access(path, X_OK)) {
        mini_printf(2, "%s: %s.\n", path, strerror(errno));
        shell->last_exit = 1;
        return -1;
    }
    return 0;
}

// name :   exec_node_cmd
// args :   node, shell, status, env_cpy
// use :    exec node cmd basics
int exec_node_cmd(node_t *node, shell_t *shell, int status, char **env_cpy)
{
    if (is_builtin(node->argv[0])) {
        exec_builtin(node->argv, shell);
        return 1;
    }
    if (get_command_path(node->argv, shell))
        return 1;
    if (try_to_access(shell->path, shell) == -1)
        return 1;
    exec_cmd(shell, node, status, env_cpy);
    return 0;
}

// name :   exec_node_op
// args :   node, shell, env_cpy
// use :    fonction for execute node who contain type op
void exec_node_op(node_t *node,
    shell_t *shell, char **env_cpy)
{
    if (strcmp(node->op, ";") == 0) {
        execute_node(node->left, env_cpy, shell);
        execute_node(node->right, env_cpy, shell);
    }
    if (strcmp(node->op, "&&") == 0) {
        shell->param = 1;
        execute_node(node->left, env_cpy, shell);
        if (shell->last_exit == 0) {
            execute_node(node->right, env_cpy, shell);
        }
    }
    if (strcmp(node->op, "||") == 0) {
        shell->param = 1;
        execute_node(node->left, env_cpy, shell);
        if (shell->last_exit != 0) {
            execute_node(node->right, env_cpy, shell);
        }
    }
}

// name :   exec_node_subshell
// args :   node, shell, status, env_coy
// use :    function for exec subshell
static int exec_node_subshell(node_t *node, shell_t *shell,
    int status, char **env_cpy)
{
    pid_t pid = fork();

    if (pid == 0) {
        execute_node(node->left, env_cpy, shell);
        exit(shell->last_exit);
    } else {
        if (waitpid(pid, &status, 0) == -1)
            return 1;
        if (WIFEXITED(status))
            shell->last_exit = WEXITSTATUS(status);
        if (WIFSIGNALED(status))
            print_signal(shell, &status);
    }
    return 0;
}

// name :   execute_node
// args :   node, env_cpy, shell
// use :    main fonction recursive for exec node
void execute_node(node_t *node, char **env_cpy, shell_t *shell)
{
    int status = 0;

    if (!node)
        return;
    if (isatty(0) == 0 && shell->last_exit != 0 && !shell->param)
        return;
    if (node->type == NODE_CMD)
        if (exec_node_cmd(node, shell, status, env_cpy))
            return;
    if (node->type == NODE_OP)
        exec_pipe(node, shell, env_cpy);
    if (node->type == NODE_SUBSHELL)
        if (exec_node_subshell(node, shell, status, env_cpy))
            return;
    if (node->type == NODE_REDIR)
        if (!exec_node_redir(node, env_cpy, shell))
            return;
}
