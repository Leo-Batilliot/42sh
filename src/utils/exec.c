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
#include <string.h>

// name :   print_signal
// args :   shell main struct
// use :    S.E
static void print_signal(shell_t *shell, int *status)
{
    int term_signal = WTERMSIG(*status);

    mini_printf(2, "%s", strsignal(term_signal));
    if (WCOREDUMP(*status))
        mini_printf(2, " (core dumped)");
    mini_printf(2, "\n");
    shell->last_exit = 128 + term_signal;
}

// name :   signal_error
// args :   pid, shell main struct, fd, arg
// use :    handle signal errors
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

// name :   child
// args :   shell main struct, array, arg, fd
// use :    handle redirection and execute command
static int child(shell_t *shell, char **array,
    args_t *tmp, int pipe_fd[2])
{
    if (isatty(0) == 0 && shell->last_exit != 0 && tmp->param == 0)
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

// name :   execute
// args :   shell main struct, array, arg, fd
// use :    fork and handle error in case of pid != 0
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

// name :   execute_script_or_builtin
// args :   shell, tmp
// use :    handles script and non-piped builtin execution
static int execute_script_or_builtin(shell_t *shell, args_t *tmp)
{
    if (is_script(tmp->args[0]))
        return execute_script(tmp->args[0], shell, tmp);
    if (is_builtin(tmp->args) && !tmp->is_pipe)
        return builtin(shell, tmp, NULL);
    return -1;
}

// name :   execute_cmd
// args :   shell, tmp
// use :    executes commands (scripts, builtins, external commands)
int execute_cmd(shell_t *shell, args_t *tmp)
{
    char **new_args = NULL;
    int pipefd[2] = {0};
    int res = 0;

    res = execute_script_or_builtin(shell, tmp);
    if (res != -1)
        return res;
    if (tmp->is_pipe && pipe(pipefd) == -1)
        return 1;
    if (pipe_builtin(shell, tmp, pipefd) == 1)
        return 0;
    if (try_to_access(shell->path, shell) == -1)
        return 1;
    new_args = globbing(tmp);
    if (!new_args)
        return res;
    res = execute(shell, new_args, tmp, pipefd);
    free_array((void **)new_args);
    return res;
}
