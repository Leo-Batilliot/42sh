/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** globbings.c
*/

#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <glob.h>


// name :   fill_globbed_values
// args :   argument string, new arguments array, current index
// use :    fill the new arguments array with values from globbing
static int fill_globbed_values(char *arg, char **new_args, int j)
{
    glob_t globbuf;

    glob(arg, GLOB_NOCHECK, NULL, &globbuf);
    for (int i = 0; i < (int)globbuf.gl_pathc; i++) {
        new_args[j] = strdup(globbuf.gl_pathv[i]);
        if (!new_args[j])
            return -1;
        j++;
    }
    globfree(&globbuf);
    return j;
}

// name :   fill_glob_args
// args :   arg, new args, j, i
// use :    fill the new arguments array with globbed values
static int fill_glob_args(char **array, char **new_args, int *j, int i)
{
    if (strstr(array[i], "*") || strstr(array[i], "?")) {
        (*j) = fill_globbed_values(array[i], new_args, (*j));
        if ((*j) == -1)
            return -1;
    } else {
        new_args[(*j)] = strdup(array[i]);
        if (!new_args[(*j)])
            return -1;
        (*j)++;
    }
    return 0;
}

// name :   set_new_args
// args :   arg, new args
// use :    loop to fill the new arguments array globbed values
static int set_new_args(char **array, char **new_args)
{
    int j = 0;

    for (int i = 0; array[i]; i++) {
        if (fill_glob_args(array, new_args, &j, i) == -1)
            return -1;
    }
    new_args[j] = NULL;
    return 0;
}

// name :   count_glob_matches
// args :   arg
// use :    count the number of arguments after globbing
static int count_glob_matches(char **array)
{
    glob_t globbuf;
    int new_args_count = 0;

    for (int i = 0; array[i]; i++) {
        if (strstr(array[i], "*") || strstr(array[i], "?")) {
            glob(array[i], GLOB_NOCHECK, NULL, &globbuf);
            new_args_count += globbuf.gl_pathc;
            globfree(&globbuf);
        } else {
            new_args_count++;
        }
    }
    return new_args_count;
}

// name :   globbings
// args :   arg
// use :    expand wildcard characters in arguments
char **globbings(char **array)
{
    int new_args_count = count_glob_matches(array);
    char **new_args = malloc(sizeof(char *) * (new_args_count + 1));

    if (!new_args)
        return NULL;
    if (set_new_args(array, new_args) == -1)
        return NULL;
    return new_args;
}
