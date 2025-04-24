/*
** EPITECH PROJECT, 2024
** my_str_len
** File description:
** count number of strings
*/

// name :   my_strlen
// args :   a string
// use :    return the lenght of the given string (nbr of characters before \0)
int my_strlen(char const *str)
{
    int count = 0;

    if (!str)
        return 0;
    for (; str[count] != '\0'; count++);
    return count;
}
