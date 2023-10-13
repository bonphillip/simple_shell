#include "shell.h"

/**
 * myenv_info - Prints the current working environment.
 * @info: Structures containing potential arguments for the function.
 * This function prints the current environment variables.
 * ReturnAlways 0.
 */
int myenv_info(info_t *info)
{
    print_list_str(info->env);
    return (0);
}

/**
* getenv_value -Gets the value of an environment variable.
* @info: Structure containing potential arguments for the function.
* @name: Name of the environment variable to retrieve.
* This function returns the value of the specified environment variable.
* Return: The value of the environment variable or NULL if not found.
*/
char *getenv_value(info_t *info, const char *name)
{
list_t *node = info->env;
char *value;

while (node)
{
value = starts_with(node->str, name);
if (value && *value)
return (value);
node = node->next;
}
return (NULL);
}

/**
* mysetenv_var - Initializes a new variable or modify a current one.
* @info: Structure contains potential arguments for the function.
*
* This function initializes a new environment variable or modifies an existing one.
* Return: Always 0.
*/
int mysetenv_var(info_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect number of arguments\n");
return (1);
}
if (setenv_var(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
* myunsetenv_var - Remove an environment variable.
* @info: Structure containing potential arguments for the function.
*
* This function removes an environment variable.
* Return: Always 0.
*/
int myunsetenv_var(info_t *info)
{
int i;

if (info->argc == 1)
{
_eputs("Too few arguments.\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
unsetenv_var(info, info->argv[i]);

return (0);
}

/**
* populate_env_list - Populates the environment linked list.
* @info: Structure containss potential arguments for the function.
*
* This function populates the environment linked list from the system's environment.
* Return: Always 0.
*/
int populate_env_list(info_t *info)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
info->env = node;
return (0);
}
