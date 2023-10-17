#include "shell.h"

/**
 * copyString - copies a source string to a destination
 * @dest: The destination string
 * @src: The source string
 *
 * Return: A pointer to the destination string
 */
char *copyString(char *dest, char *src)
{
    int i = 0;

    if (dest == src || src == 0)
        return dest;

    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = 0;
    return dest;
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: A pointer to the duplicated string
 */
char *duplicateString(const char *str)
{
    int length = 0;
    char *ret;

    if (str == NULL)
        return NULL;

    while (*str++)
        length++;

    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return NULL;

    for (length++; length--;)
        ret[length] = *--str;

    return ret;
}

/**
 * printString - prints an input string
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void printString(char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
}

/**
 * _putchar- writes a character c to the standard output
 * @c: The character to print
 *
 * Return: On success, the return is 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writeCharacter(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;

    return 1;
}
