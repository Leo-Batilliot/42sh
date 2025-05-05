/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** pipe
*/

#include "shell.h"
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

// name :   close_pipe
// args :   pipefd[2]
// use :    close pipe
static void close_pipe(int pipefd[2], pid_t pid_left, pid_t pid_right)
{
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid_left, NULL, 0);
    waitpid(pid_right, NULL, 0);
}

// name :   exec_pid_right
// args :   node, env_cpy, shell, pipefd[2]
// use :    exec pid right
static void exec_pid_right(node_t *node, char **env_cpy,
    shell_t *shell, int pipefd[2])
{
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    execute_node(node->right, env_cpy, shell);
    exit(0);
}

// name :   exec_pid_left
// args :   node, env_cpy, shell, pipefd[2]
// use :    exec_pid_left
static void exec_pid_left(node_t *node, char **env_cpy,
    shell_t *shell, int pipefd[2])
{
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    execute_node(node->left, env_cpy, shell);
    exit(0);
}

// name :   exec_pipe
// args :   node, shell, env_cpy
// use :    executing pipe
void exec_pipe(node_t *node, shell_t *shell, char **env_cpy)
{
    int pipefd[2] = {0};
    pid_t pid_left = 0;
    pid_t pid_right = 0;

    exec_node_op(node, shell, env_cpy);
    if (strcmp(node->op, "|") == 0) {
        shell->param = 1;
        if (pipe(pipefd) == -1)
            return;
        pid_left = fork();
        if (pid_left == 0)
            exec_pid_left(node, env_cpy, shell, pipefd);
        pid_right = fork();
        if (pid_right == 0)
            exec_pid_right(node, env_cpy, shell, pipefd);
        close_pipe(pipefd, pid_left, pid_right);
    }
}
