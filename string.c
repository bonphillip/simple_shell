#include "shell.h"

/**
 * _strlen - calculates the length of a string
 * @s: the string whose length to check
 *
 * Returns: the length of the string
 */
int _strlen(char *s) 
{
    int len = 0;

    if (!s)
        return 0;

    while (*s++)
        len++;

    return len;
}

/**
 * _strcmp - comparison of two strings lexicographically
 * @s1: the first string
 * @s2: the second string
 *
 * Returns: zero if s1 is equal to s2, a positive value if s1 > s2, a negative value if s1 < s2
 */
int _strcmp(char *s1, char *s2)
 {
    while (*s1 && *s2)
 {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }
    
    if (*s1 == *s2)
        return 0;
    else
        return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with a specific substring
 * @haystack: the string to search
 * @needle: the substring to find
 *
 * Returns: the address of the next char in haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle) 
{
    while (*needle) 
        if (*needle++ != *haystack++)
            return NULL;
    return (char *)haystack;
}

/**
 * Custom implementation to concatenate two strings.
 *
 * @param dest - The destination buffer.
 * @param src - The source buffer.
 * 
 * @return A pointer to the destination buffer after concatenation.
 */
char *_strcat(char *dest, char *src) {
    char *result = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;

    return result;
}
