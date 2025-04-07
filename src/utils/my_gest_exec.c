/*
** EPITECH PROJECT, 2025
** my gest exec
** File description:
** my_gest_exec
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

void gest_signal(info_shell_t *shell_i, int *statu)
{
    int term_signal = WTERMSIG(*statu);

    write(2, strsignal(term_signal), my_strlen(strsignal(term_signal)));
    if (WCOREDUMP(*statu))
        write(2, " (core dumped)", 14);
    write(2, "\n", 1);
    shell_i->last_exit = 128 + term_signal;
}

int gest_acces(char *path, info_shell_t *shell_i)
{
    struct stat file_stat;

    if (stat(path, &file_stat) == -1) {
        my_printerr("%s: Command not found.\n", path);
        shell_i->last_exit = ERROR;
        return -1;
    }
    if (S_ISDIR(file_stat.st_mode)) {
        my_printerr("%s: Permission denied.\n", path);
        shell_i->last_exit = ERROR;
        return -1;
    }
    if (access(path, X_OK)) {
        my_printerr("%s: %s.\n", path, strerror(errno));
        shell_i->last_exit = ERROR;
        return -1;
    }
    return 0;
}

int gest_bef_signal(pid_t pid, info_shell_t *shell_i,
    int pipe_fd[2], args_t *tmp)
{
    int statu = 0;

    if (shell_i->prev != 0) {
        close(shell_i->prev);
        shell_i->prev = 0;
    }
    if (tmp->is_pipe == 1) {
        close(pipe_fd[1]);
        shell_i->prev = pipe_fd[0];
    } else {
        if (waitpid(pid, &statu, 0) == -1)
            return 1;
    }
    if (WIFEXITED(statu))
        shell_i->last_exit = WEXITSTATUS(statu);
    else if (WIFSIGNALED(statu))
        gest_signal(shell_i, &statu);
    return 0;
}

static int gest_child(info_shell_t *shell_i, char **array,
    args_t *tmp, int pipe_fd[2])
{
    if (isatty(0) == 0 && shell_i->last_exit != 0)
        return 1;
    if (shell_i->prev != 0) {
        dup2(shell_i->prev, STDIN_FILENO);
        close(shell_i->prev);
    }
    if (tmp->is_pipe == 1) {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }
    handle_red(tmp, shell_i);
    if (execve(shell_i->path, array, shell_i->env_cpy) == -1) {
        write(2, shell_i->path, my_strlen(shell_i->path));
        write(2, ": Exec format error. Binary file not executable.\n", 49);
        shell_i->last_exit = ERROR;
        exit(1);
    }
    return 0;
}

int is_bulltins(char *cmd)
{
    if (!my_strcmp(cmd, "env")
        || !my_strcmp(cmd, "setenv")
        || !my_strcmp(cmd, "unsetenv")
        || !my_strcmp(cmd, "exit")
        || !my_strcmp(cmd, "cd")) {
        return 1;
    }
    return 0;
}

static int execute_cmd(info_shell_t *shell_i, char **array,
    args_t *tmp, int pipefd[2])
{
    pid_t pid = 0;

    pid = fork();
    if (pid == 0) {
        if (gest_child(shell_i, array, tmp, pipefd) == 1)
            return ERROR;
    } else {
        if (gest_bef_signal(pid, shell_i, pipefd, tmp) == 1)
            return ERROR;
    }
    return 0;
}

int my_gest_exec(info_shell_t *shell_i,
    args_t *tmp, linked_list_t **head)
{
    int pipefd[2] = {0};
    int res = 0;

    res = handle_builtins(shell_i, tmp->args, tmp, head);
    if (res != 0 || (is_bulltins(tmp->args[0]) == 1 && tmp->is_pipe == 0))
        return res;
    if (create_pipe(pipefd, tmp) == ERROR)
        return ERROR;
    if (pipe_w_bulltins(shell_i, tmp, head, pipefd) == 1)
        return 0;
    if (gest_acces(shell_i->path, shell_i) == -1)
        return 1;
    return execute_cmd(shell_i, tmp->args, tmp, pipefd);
}
