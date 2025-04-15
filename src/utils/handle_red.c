/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-gabin.wilson
** File description:
** handle_red
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

int gest_fd(int fd, info_shell_t *shell_i, args_t *tmp, int std_fd)
{
    if (fd == -1) {
        fprintf(stderr, "%s: %s.\n",
            tmp->redir[tmp->redir->i].file, strerror(errno));
        shell_i->last_exit = ERROR;
        return -1;
    }
    if (dup2(fd, std_fd) == -1) {
        return -1;
    }
    close(fd);
    return 0;
}

int handle_red(args_t *tmp, info_shell_t *shell_i)
{
    int fd = 0;

    for (int i = 0; i < tmp->count_red; i++) {
        tmp->redir->i = 0;
        if (tmp->redir[i].statu == 1) {
            fd = open(tmp->redir[i].file, O_RDONLY);
            return (gest_fd(fd, shell_i, tmp, STDIN_FILENO) == -1) ? 1 : 0;
        }
        if (tmp->redir[i].statu == 2) {
            fd = open(tmp->redir[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            return (gest_fd(fd, shell_i, tmp, STDOUT_FILENO) == -1) ? 1 : 0;
        }
        if (tmp->redir[i].statu == 3) {
            fd = open(tmp->redir[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            return (gest_fd(fd, shell_i, tmp, STDOUT_FILENO) == -1) ? 1 : 0;
        }
        if (tmp->redir[i].statu == 4)
            return (handle_heredocs(tmp, i, shell_i) == 1) ? 1 : 0;
    }
    return 0;
}
