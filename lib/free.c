/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** free_array
*/

#include <stdlib.h>

// name :   my_free
// args :   a pointer (void *)
// use :    free the ptr if it's not NULL, return 0
int my_free(void *ptr)
{
    if (!ptr)
        return 0;
    free(ptr);
    return 0;
}

// name :   free_array
// args :   an array (cast in (void **) if needed)
// use :    free the array elements until it finds NULL and return 0
int free_array(void **array)
{
    if (!array)
        return 0;
    for (int i = 0; array[i]; i++)
        my_free(array[i]);
    return my_free(array);
}
