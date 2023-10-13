#include "custom_lib.h"

/**
 * my_strncpy - Custom string copy function
 * @destination: The destination string to copy to
 * @source: The source string
 * @num_chars: The max no of characters to copy
 * Return: A pointer to the copied string
 */
char *my_strncpy(char *destination, char *source, int num_chars)
{
	int i, j;
	char *result = destination;

	i = 0;
	while (source[i] != '\0' && i < num_chars - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < num_chars)
	{
		j = i;
		while (j < num_chars)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return result;
}

/**
 * my_strncat - Custom string concatenation function
 * @dest: The first string
 * @src: The second string to be concatenated
 * @max_bytes: The maximum no of bytes to use
 * Return: A pointer to the concatenated string
 */
char *my_strncat(char *dest, char *src, int max_bytes)
{
	int i, j;
	char *result = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < max_bytes)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < max_bytes)
		dest[i] = '\0';
	return result;
}

/**
 * my_strchr - Custom character search in a string
 * @str: The string to search
 * @character: The character to search
 * Return:pointer to the memory area having the character or NULL if not found
 */
char *my_strchr(char *str, char character)
{
	do {
		if (*str == character)
			return str;
	} while (*str++ != '\0');

	return NULL;
}

