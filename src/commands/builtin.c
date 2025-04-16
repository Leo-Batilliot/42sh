/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin
*/

#include "my.h"

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

static int exec_builtin(char **array, linked_list_t *head, shell_t *shell)
{
    if (!strcmp(array[0], "env"))
        return my_env(array, shell, &head);
    if (!strcmp(array[0], "setenv"))
        return my_setenv(&head, array, shell);
    if (!strcmp(array[0], "unsetenv"))
        return my_unsetenv(array, &head, shell);
    if (!strcmp(array[0], "cd"))
        return my_cd(array, head, shell);
    if (!strcmp(array[0], "exit"))
        my_exit(array);
    return 0;
}

int builtin(shell_t *shell,
    args_t *tmp, linked_list_t **head, int fd[2])
{
    int save_stdin = -1;
    int save_stdout = -1;

    manage_fd(tmp, fd, &save_stdin, &save_stdout);
    redirection(tmp, shell);
    exec_builtin(tmp->args, (*head), shell);
    if (tmp->count_red > 0 || tmp->is_pipe == 1) {
        dup2(save_stdin, STDIN_FILENO);
        close(save_stdin);
        dup2(save_stdout, STDOUT_FILENO);
        close(save_stdout);
    }
    return 0;
}

int pipe_builtin(shell_t *shell, args_t *tmp,
    linked_list_t **head, int pipefd[2])
{
    pid_t pid = 0;

    if (is_builtin(tmp->args[0]) == 1 && tmp->is_pipe == 1) {
        pid = fork();
        if (pid == 0) {
            builtin(shell, tmp, head, pipefd);
            exit(0);
        }
        signal_error(pid, shell, pipefd, tmp);
        return 1;
    }
    return 0;
}
