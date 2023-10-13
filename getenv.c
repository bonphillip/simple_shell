#include "shell.h"

/**
 * get_environment - Returns a copy of the environmental variables as a string array.
 * @info: A structure that may contain relevant argument, ensuring consistency in function prototype.
 * Return: Always returns 0.
 */
char **get_environment(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * remove_environment_var - Delete an environment variable
 * @info: A structure that might contain relevant arguments, ensuring a consistent function prototype.
 * @var: The name of the environmental variable to be removed.
 * Return: Returns 1 on successful removal, otherwise 0.
 */
int remove_environment_var(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t index = 0;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), index);
            index = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        index++;
    }

    return (info->env_changed);
}

/**
 * set_environment_var - Create new environment variable or modify a current existing one.
 * @info: A structure that may contain relevant arguments, ensuring a consistency function prototype.
 * @var: The current name of the environment variable.
 * @value: The values of the environment variable.
 * Return: Always returns 0.
 */
int set_environment_var(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return (0);

    buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return (1);

    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);

    node = info->env;

    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return (0);
}

