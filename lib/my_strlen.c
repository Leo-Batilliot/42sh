/*
** EPITECH PROJECT, 2024
** my_str_len
** File description:
** count number of strings
*/

int my_strlen(char const *str)
{
    int count = 0;

    while (*str != '\0') {
        str = str + 1;
        count = count + 1;
    }
    return count;
}
