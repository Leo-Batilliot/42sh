/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin
*/

#include "shell.h"
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// name :   builtins
// args :   N.A
// use :    ptr to function for builtin related functions
const builtin_t builtins[] = {
    {"env", my_env},
    {"setenv", my_setenv},
    {"unsetenv", my_unsetenv},
    {"cd", my_cd},
    {"history", my_history},
    {"exit", my_exit},
    {"alias", alias},
    {"clean", clean},
    {"color", color},
    {"set", set},
    {"unset", unset},
    {"echo", my_echo},
    {NULL, NULL}
};

// name :   is_builtin
// args :   command array
// use :    S.E
int is_builtin(char **cmds)
{
    if (!my_strcmp(cmds[0], "env")
        || !my_strcmp(cmds[0], "setenv")
        || !my_strcmp(cmds[0], "unsetenv")
        || !my_strcmp(cmds[0], "exit")
        || !my_strcmp(cmds[0], "cd")
        || !my_strcmp(cmds[0], "alias")
        || !my_strcmp(cmds[0], "history")
        || !my_strcmp(cmds[0], "clean")
        || !my_strcmp(cmds[0], "color")
        || !my_strcmp(cmds[0], "set")
        || !my_strcmp(cmds[0], "unset")
        || !my_strcmp(cmds[0], "echo"))
        return 1;
    return 0;
}

// name :   manage_fd
// args :   argument, fd, saved stdin, saved stdout
// use :    prepare and manage redirection of file descriptors
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

// name :   exec_builtin
// args :   array, shell main struct
// use :    search for a corresponding builtin function and return it if found
static int exec_builtin(char **array, shell_t *shell)
{
    for (int i = 0; builtins[i].name; i++)
        if (!my_strcmp(array[0], builtins[i].name))
            return builtins[i].func(array, shell);
    return 0;
}

// name :   builtin
// args :   main shell struct, argument, fd
// use :    execute a builtin command with possible redirections
int builtin(shell_t *shell, args_t *tmp, int fd[2])
{
    int save_stdin = -1;
    int save_stdout = -1;

    manage_fd(tmp, fd, &save_stdin, &save_stdout);
    redirection(tmp, shell);
    exec_builtin(tmp->args, shell);
    if (tmp->count_red > 0 || tmp->is_pipe == 1) {
        dup2(save_stdin, STDIN_FILENO);
        close(save_stdin);
        dup2(save_stdout, STDOUT_FILENO);
        close(save_stdout);
    }
    return 0;
}

// name :   pipe_builtin
// args :   shell main struct, argument, fd
// use :    handle fork and execution of a builtin command in a pipeline
int pipe_builtin(shell_t *shell, args_t *tmp, int pipefd[2])
{
    pid_t pid = 0;

    if (is_builtin(tmp->args) == 1 && tmp->is_pipe == 1) {
        pid = fork();
        if (pid == 0) {
            builtin(shell, tmp, pipefd);
            exit(0);
        }
        signal_error(pid, shell, pipefd, tmp);
        return 1;
    }
    return 0;
}
