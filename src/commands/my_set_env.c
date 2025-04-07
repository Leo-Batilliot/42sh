/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_set_env
*/

#include "my.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

static int check_alpha(char *string)
{
    for (int i = 1; string[i] != '\0'; i++) {
        if (string[i] == '_' || (string[i] >= 'a' && string[i] <= 'z')
            || (string[i] >= 'A' && string[i] <= 'Z')
            || (string[i] >= '1' && string[i] <= '9'))
            continue;
        else
            return -1;
    }
    return 0;
}

int gest_wildcard(char **array, linked_list_t *list)
{
    if (!array[2]) {
        free(list->value);
        list->value = NULL;
    } else {
        if (list->value != NULL)
            free(list->value);
        list->value = my_strdup(array[2]);
        if (!list->value)
            return 1;
    }
    return 0;
}

void add_nodes(linked_list_t **head, linked_list_t *new_alloc)
{
    linked_list_t *cur = NULL;

    if ((*head) == NULL) {
        (*head) = new_alloc;
    } else {
        cur = (*head);
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = new_alloc;
    }
}

int check_collision(linked_list_t **head, char **array)
{
    linked_list_t *tmp = *head;

    while (tmp != NULL) {
        if (my_strcmp(tmp->key, array[1]) == 0)
            return gest_wildcard(array, tmp);
        tmp = tmp->next;
    }
    return 2;
}

static int gest_error_set(linked_list_t **head, char **array,
    info_shell_t *shell_i)
{
    linked_list_t *tmp = NULL;
    int count = 0;

    for (; array[count] != NULL; count++);
    if (count > 3) {
        my_printerr("setenv: Too many arguments.\n");
        shell_i->last_exit = 1;
        return 1;
    }
    if (count == 1) {
        tmp = *head;
        print_env(tmp);
        return 0;
    }
    return 2;
}

static int gest_case(linked_list_t *new_alloc, info_shell_t *shell_i)
{
    if ((new_alloc->key[0] < 'a' || new_alloc->key[0] > 'z')
            && (new_alloc->key[0] < 'A' || new_alloc->key[0] > 'Z')
            && (new_alloc->key[0] != '_')) {
        my_printerr("setenv: Variable name must begin with a letter.\n");
        shell_i->last_exit = 1;
        return -1;
    }
    if (check_alpha(new_alloc->key) == -1) {
        my_printerr("setenv: Variable name must ");
        my_printerr("contain alphanumeric characters.\n");
        shell_i->last_exit = 1;
        return -1;
    }
    return 0;
}

linked_list_t *push_list(char **array, info_shell_t *shell_i)
{
    linked_list_t *new_alloc = malloc(sizeof(linked_list_t));

    if (!new_alloc)
        return NULL;
    new_alloc->key = my_strdup(array[1]);
    if (!new_alloc->key)
        return NULL;
    if (gest_case(new_alloc, shell_i) == -1)
        return NULL;
    new_alloc->value = NULL;
    if (gest_wildcard(array, new_alloc) == 1)
        return NULL;
    new_alloc->next = NULL;
    return new_alloc;
}

int set_env(linked_list_t **head, char **array, info_shell_t *shell_i)
{
    linked_list_t *new_alloc = NULL;
    int value = 0;

    if (my_strcmp(array[0], "setenv") == 0) {
        value = gest_error_set(head, array, shell_i);
        if (value != 2)
            return (value == 1) ? 1 : 2;
        value = check_collision(head, array);
        if (value != 2)
            return (value == 1) ? 1 : 2;
        new_alloc = push_list(array, shell_i);
        if (!new_alloc)
            return 1;
        add_nodes(head, new_alloc);
        return 2;
    }
    return 0;
}
