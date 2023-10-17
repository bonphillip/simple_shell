#include "shell.h"

/**
* free_and_null - Frees a pointer and sets it to NULL
* @array: address of the pointer to be freed
*
* Returns: if freed 1, otherwise 0.
*/
int free_and_null(void **array)
{
	if (array && *array)
{
	free(*array);
	*array = NULL;
	return 1;
}
return 0;
}
