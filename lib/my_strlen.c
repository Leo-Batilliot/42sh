/*
** EPITECH PROJECT, 2024
** my_str_len
** File description:
** count number of strings
*/

int my_strlen(char const *str)
{
    int count = 0;

    if (!str)
        return 0;
    for (; str[count] != '\0'; count++);
    return count;
}
