#include "shell.h"

/**
 * custom_memset - Fills a memory area with a constant byte
 * @dest: Pointer to the memory area
 * @byte: The byte value to fill dest with
 * @size: The number of bytes to fill
 * Return: Pointer to the memory area dest
 */
char *custom_memset(char *dest, char byte, unsigned int size)
{
unsigned int i;

for (i = 0; i < size; i++)
dest[i] = byte;
return dest;
}

/**
* ffree - frees a string of strings
* @pp: string of strings
*/
void ffree(char **pp)
{
char **a = str_array;

if (!str_array)
return;
while (*str_array)
free(*str_array++);
free(a);
}

/**
* custom_realloc - Reallocates a block of memory
* @ptr: Pointer to the previous malloc'ated block
* @old_size: Byte size of the previous block
* @new_size: Byte size of the new block
* Return: Pointer to the reallocated block
*/
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *p;

if (!ptr)
return malloc(new_size);
if (!new_size)
{
free(ptr);
return NULL;
}
if (new_size == old_size)
return ptr;

new_ptr = malloc(new_size);
if (!p)
return NULL;

old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
new_ptr[old_size] = ((char *)ptr)[old_size];
free(ptr);
return p;
}
