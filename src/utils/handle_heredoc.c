/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-gabin.wilson
** File description:
** handle_heredoc
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

static int up_temp(char *line, int i, args_t *tmp, int index)
{
    char *temp_line = my_strdup(line);

    if (!temp_line)
        return -1;
    temp_line[my_strlen(temp_line) - 1] = '\0';
    if (!my_strcmp(temp_line, tmp->redir[i].file)) {
        free(temp_line);
        return 1;
    }
    free(temp_line);
    write(index, line, my_strlen(line));
    write(STDOUT_FILENO, "? ", 2);
    return 0;
}

int handle_heredocs(args_t *tmp, int i, info_shell_t *shell_i)
{
    int fd_h[2];
    size_t size = 0;
    char *line = NULL;

    if (pipe(fd_h) == -1)
        return 1;
    write(STDOUT_FILENO, "? ", 2);
    for (ssize_t read_size = getline(&line, &size, stdin); read_size != -1;
        read_size = getline(&line, &size, stdin)) {
        if (up_temp(line, i, tmp, fd_h[1]) == ERROR)
            break;
    }
    free(line);
    close(fd_h[1]);
    if (gest_fd(fd_h[0], shell_i, tmp, STDIN_FILENO) == -1)
        return -1;
    return 0;
}
