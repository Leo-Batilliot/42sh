/*
** EPITECH PROJECT, 2024
** my_strcmp
** File description:
** behavior of strcmp
*/

#include "shell.h"

// name :   my_strcmp
// args :   string 1, string 2
// use :    compares the strings and return the ascii difference if found
int my_strcmp(char const *s1, char const *s2)
{
    if (!s1 || !s2 || my_strlen(s1) != my_strlen(s2))
        return 84;
    for (int i = 0; s1[i] != '\0'; i++)
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
    return 0;
}

// name :   case_cmp
// args :   2 characters
// use :    compare two characters uppercase or lowercase doesn't matter
int case_cmp(char a, char b)
{
    if (a >= 'a' && a <= 'z')
        a += 'A' - 'a';
    if (b >= 'a' && b <= 'z')
        b += 'A' - 'a';
    if (b != a)
        return a - b;
    return 0;
}

// name :   my_case_strncmp
// args :   2 strings and a number
// use :    strncmp but uppercase or lowercase doesn't matter
int my_case_strncmp(char *str1, char *str2, int n)
{
    if (!str1 || !str2 || my_strlen(str1) < n || my_strlen(str2) < n)
        return 1;
    for (int i = 0; i < n; i++)
        if (case_cmp(str1[i], str2[i]))
            return case_cmp(str1[i], str2[i]);
    return 0;
}

// name :   rev_strncmp
// args :   str1, str2, number
// use :    strncmp from the end of the strings
int rev_case_strncmp(char *str1, char *str2, int n)
{
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);

    if (len1 < n || len2 < n || !str1 || !str2)
        return 1;
    for (int i = 1; i <= n; i++)
        if (case_cmp(str1[len1 - i], str2[len2 - i]))
            return case_cmp(str1[len1 - i], str2[len2 - i]);
    return 0;
}
