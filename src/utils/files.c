/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** files
*/

#include "shell.h"
#include <unistd.h>
#include <sys/stat.h>

// name :   create_directory
// args :   directory name
// use :    S.E
static int create_directory(char *directory)
{
    struct stat st = {0};

    if (stat(directory, &st) == -1) {
        if (mkdir(directory, 0755) != 0) {
            mini_printf(1, "Could not create the directory : %s\n", directory);
            return 84;
        }
    }
    return 0;
}

// name :   load_file
// args :   shell main struct
// use :    create assets directory if it doesnt exist and load history-alias
int load_file(shell_t *shell)
{
    create_directory("assets");
    if (isatty(0) == 1) {
        load_alias(shell);
        load_history(shell);
    }
    return 0;
}

// name :   save_file
// args :   shell main struct
// use :    save alias and history in files
int save_file(shell_t *shell)
{
    if (isatty(0) == 1) {
        write_alias(shell);
        write_history(shell);
    }
    return 0;
}
