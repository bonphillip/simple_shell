#include "shell.h"

/**
* print_error_message - prints an error message to the standard error stream
* @str: The error message to be printed
*
* This function prints an error message to the standard error stream.
*/
void print_error_message(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
write_error_character(str[i]);
i++;
}
}

/**
* write_error_character - writes a character to the standard error stream
* @c: The character to be printed
*
* This function writes a character to the standard error stream.
* Return: On success, it returns 1. On error, -1 is returned, and errno is set appropriatly.
*/
int write_error_character(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(2, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
* write_to_fd - writes a character to the specified file descriptor
* @c: The character to print
* @fd: The file descriptor to write to
*
* This function writes a character to the specified file descriptors.
* Return: On success, it returns 1. On error, -1 is returned, and errno is set appropriately.
*/
int write_to_fd(char c, int fd)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fd, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
* print_to_fd - prints an input string to the specified file descriptor
* @str: The string to be printed
* @fd: The file descriptor to write to
*
* This function prints an input string to the specified file descriptor.
* Return: The number of characters written.
*/
int print_to_fd(char *str, int fd)
{
int i = 0;

if (!str)
return (0);
while (*str)
{
i += write_to_fd(*str++, fd);
}
return (i);
}
