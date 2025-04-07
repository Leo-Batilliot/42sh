/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-gabin.wilson
** File description:
** update_pipe
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>

static int manage_fd(args_t *tmp, int fd[2],
    int *save_stdin, int *save_stdout)
{
    if (tmp->count_red > 0 || tmp->is_pipe == 1) {
        *save_stdin = dup(STDIN_FILENO);
        *save_stdout = dup(STDOUT_FILENO);
    }
    if (tmp->is_pipe == 1) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
    }
    return 0;
}

static int exec_bulltins(info_shell_t *shell_i,
    args_t *tmp, linked_list_t **head, int fd[2])
{
    int save_stdin = -1;
    int save_stdout = -1;

    manage_fd(tmp, fd, &save_stdin, &save_stdout);
    handle_red(tmp, shell_i);
    commands_env(tmp->args, (*head), shell_i);
    if (tmp->count_red > 0 || tmp->is_pipe == 1) {
        dup2(save_stdin, STDIN_FILENO);
        close(save_stdin);
        dup2(save_stdout, STDOUT_FILENO);
        close(save_stdout);
    }
    return 0;
}

int handle_builtins(info_shell_t *shell_i, char **array,
    args_t *tmp, linked_list_t **head)
{
    if (is_bulltins(array[0]) == 1 && tmp->is_pipe == 0)
        return exec_bulltins(shell_i, tmp, head, NULL);
    return 0;
}

int create_pipe(int pipefd[2], args_t *tmp)
{
    if (tmp->is_pipe == 1) {
        if (pipe(pipefd) == -1)
            return ERROR;
    }
    return 0;
}

int pipe_w_bulltins(info_shell_t *shell_i, args_t *tmp,
    linked_list_t **head, int pipefd[2])
{
    pid_t pid = 0;

    if (is_bulltins(tmp->args[0]) == 1 && tmp->is_pipe == 1) {
        pid = fork();
        if (pid == 0) {
            exec_bulltins(shell_i, tmp, head, pipefd);
            exit(0);
        }
        if (gest_bef_signal(pid, shell_i, pipefd, tmp) == 1)
                return ERROR;
        return 1;
    }
    return 0;
}
