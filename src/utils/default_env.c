/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** default_env.c
*/

#include "shell.h"
#include <sys/utsname.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <pwd.h>

// name :   fill_static_values
// args :   env array
// use :    fill the values of the env that are static
static int fill_static_values(char **env_cpy, int *index)
{
    char *values[] = {
        "NLSPATH=/usr/share/locale/%L/LC_MESSAGES/%N"
        ".cat:/usr/share/locale/%l/LC_MESSAGES/%N.cat",
        "HOSTTYPE=x86_64-linux",
        "VENDOR=unknown",
        "OSTYPE=linux",
        "MACHTYPE=x86_64",
        "SHLVL=1",
        NULL
    };

    for (int i = 0; values[i]; i++) {
        env_cpy[*index] = my_strdup(values[i]);
        if (!env_cpy[*index])
            return -1;
        (*index)++;
    }
    return 0;
}

// name :   fill_static_values
// args :   env array
// use :    fill the values of the env that are dynamic
static void fill_dynamic_values(char **env_cpy, int *index)
{
    char *user = getlogin();
    struct passwd *pw = getpwuid(getuid());
    char cwd[256] = "\0";
    struct utsname sysinfo;

    uname(&sysinfo);
    getcwd(cwd, sizeof(cwd));
    if (user)
        asprintf(&env_cpy[(*index)++], "USER=%s", user);
    if (user)
        asprintf(&env_cpy[(*index)++], "LOGNAME=%s", user);
    if (pw)
        asprintf(&env_cpy[(*index)++], "GROUP=%s", pw->pw_name);
    asprintf(&env_cpy[(*index)++], "PWD=%s", cwd);
    asprintf(&env_cpy[(*index)++], "HOST=%s", sysinfo.nodename);
}

// name :   create_default_env
// args :   env array
// use :    S.E
char **create_default_env(char **env_cpy)
{
    int count = 0;
    int index = 0;

    while (count < 6)
        count++;
    env_cpy = malloc(sizeof(char *) * (count + 6));
    if (!env_cpy)
        return NULL;
    if (fill_static_values(env_cpy, &index) == -1)
        return NULL;
    fill_dynamic_values(env_cpy, &index);
    env_cpy[index] = NULL;
    return env_cpy;
}
