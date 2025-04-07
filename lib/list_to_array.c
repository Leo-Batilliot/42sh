/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** list_to_array
*/
#include "my.h"

char **fill_array(char **array, node_t *current)
{
    int count = 0;

    for (int i = 0; current; i++) {
        array[i] = malloc(sizeof(char) * (my_strlen(current->name) +
            my_strlen(current->value) + 2));
        if (!array[i])
            return NULL;
        for (count = 0; current->name[count] != '\0'; count++)
            array[i][count] = current->name[count];
        array[i][count] = '=';
        count++;
        for (int j = 0; current->value && current->value[j] != '\0'; j++) {
            array[i][count] = current->value[j];
            count++;
        }
        array[i][count] = '\0';
        current = current->next;
    }
    return array;
}

char **list_to_array(list_t *list)
{
    node_t *current;
    int count = 0;
    char **array;

    if (!list || !list->head)
        return NULL;
    current = list->head;
    for (; current; count++)
        current = current->next;
    array = malloc(sizeof(char *) * (count + 1));
    if (!array)
        return NULL;
    array[count] = NULL;
    return fill_array(array, list->head);
}

void create_and_add_node(char **line, list_t *list)
{
    char *value = NULL;

    if (!list || !line || !line[0])
        return;
    if (!line[1])
        return add_node(line[0], NULL, list);
    add_node(line[0], line[1], list);
    free(value);
}

static char **fill_env(char **array, char *str)
{
    int count = 0;
    int i = 0;

    for (; str[count] != '=' && str[count] != '\0'; count++)
        array[0][count] = str[count];
    array[0][count] = '\0';
    if (str[count] == '\0' || str[count + 1] == '\0') {
        free(array[1]);
        array[1] = NULL;
        return array;
    }
    count++;
    for (; str[count + i] != '\0'; i++)
        array[1][i] = str[count + i];
    array[1][i] = '\0';
    array[2] = NULL;
    return array;
}

char **split_env(char *line)
{
    char **array = NULL;
    int count = 0;
    int value_len = 0;

    if (!line)
        return NULL;
    array = malloc(sizeof(char *) * 3);
    if (!array)
        return NULL;
    for (; line[count] != '=' && line[count] != '\0'; count++);
    array[0] = malloc(sizeof(char) * (count + 1));
    if (!array[0])
        return NULL;
    for (int i = count + 1; line[i] != '\0'; i++)
        value_len++;
    array[1] = malloc(sizeof(char) * (value_len + 1));
    if (!array[1])
        return NULL;
    return fill_env(array, line);
}

list_t *array_to_list(char **array)
{
    list_t *list = NULL;
    char **line = NULL;

    if (!array || !array[0])
        return NULL;
    list = create_list();
    if (!list)
        return NULL;
    for (int i = 0; array[i] != NULL; i++) {
        line = split_env(array[i]);
        if (!line)
            break;
        create_and_add_node(line, list);
        free_array((void **) line);
    }
    return list;
}
