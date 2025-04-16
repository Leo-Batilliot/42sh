/*
** EPITECH PROJECT, 2025
** my gest exec
** File description:
** my_gest_exec
*/

#include "my.h"

static void print_signal(shell_t *shell, int *status)
{
    int term_signal = WTERMSIG(*status);

    fprintf(stderr, "%s", strsignal(term_signal));
    if (WCOREDUMP(*status))
        fprintf(stderr, " (core dumped)");
    fprintf(stderr, "\n");
    shell->last_exit = 128 + term_signal;
}

int signal_error(pid_t pid, shell_t *shell,
    int pipe_fd[2], args_t *tmp)
{
    int status = 0;

    if (shell->prev != 0) {
        close(shell->prev);
        shell->prev = 0;
    }
    if (tmp->is_pipe == 1) {
        close(pipe_fd[1]);
        shell->prev = pipe_fd[0];
    } else {
        if (waitpid(pid, &status, 0) == -1)
            return 1;
    }
    if (WIFEXITED(status))
        shell->last_exit = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        print_signal(shell, &status);
    return 0;
}

static int try_to_acces(char *path, shell_t *shell)
{
    struct stat file_stat;

    if (stat(path, &file_stat) == -1) {
        fprintf(stderr, "%s: Command not found.\n", path);
        shell->last_exit = 1;
        return -1;
    }
    if (S_ISDIR(file_stat.st_mode)) {
        fprintf(stderr, "%s: Permission denied.\n", path);
        shell->last_exit = 1;
        return -1;
    }
    if (access(path, X_OK)) {
        fprintf(stderr, "%s: %s.\n", path, strerror(errno));
        shell->last_exit = 1;
        return -1;
    }
    return 0;
}

static int child(shell_t *shell, char **array,
    args_t *tmp, int pipe_fd[2])
{
    if (isatty(0) == 0 && shell->last_exit != 0)
        return 1;
    if (shell->prev != 0) {
        dup2(shell->prev, STDIN_FILENO);
        close(shell->prev);
    }
    if (tmp->is_pipe == 1) {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }
    redirection(tmp, shell);
    if (execve(shell->path, array, shell->env_cpy) == -1) {
        write(2, shell->path, my_strlen(shell->path));
        write(2, ": Exec format error. Binary file not executable.\n", 49);
        shell->last_exit = 1;
        exit(1);
    }
    return 0;
}

static int execute(shell_t *shell, char **array,
    args_t *tmp, int pipefd[2])
{
    pid_t pid = fork();

    if (pid == 0) {
        if (child(shell, array, tmp, pipefd))
            return 1;
    } else
        if (signal_error(pid, shell, pipefd, tmp))
            return 1;
    return 0;
}

int execute_cmd(shell_t *shell,
    args_t *tmp, linked_list_t **head)
{
    int pipefd[2] = {0};
    int res = 0;

    if (is_builtin(tmp->args[0]) && !tmp->is_pipe)
        return builtin(shell, tmp, head, NULL);
    if (res != 0 || (is_builtin(tmp->args[0]) == 1 && tmp->is_pipe == 0))
        return res;
    if (tmp->is_pipe && pipe(pipefd) == - 1)
        return 1;
    if (pipe_builtin(shell, tmp, head, pipefd) == 1)
        return 0;
    if (try_to_acces(shell->path, shell) == -1)
        return 1;
    return execute(shell, tmp->args, tmp, pipefd);
}
