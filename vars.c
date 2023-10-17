#include "shell.h"

/**
* isCommandChain - checks if the current character in the buffer is a command chain delimiter
* @info: the parameter struct
* @buf: Character buffer
* @p: Address of the current position in buf
*
* Return: 1 If it's a chain delimiter, 0 otherwise
*/
int isCommandChain(info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        info->cmdBufType = CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        info->cmdBufType = CMD_AND;
    }
    else if (buf[j] == ';') /* Found the end of this command */
    {
        buf[j] = 0; /* Replace semicolon with null */
        info->cmdBufType = CMD_CHAIN;
    }
    else
    {
        return (0);
    }

    *p = j;
    return (1);
}

/**
* checkChain - checks whether we should continue chaining based on the last status
* @info: Structure containing relevant information.
* @buf: Character buffer.
* @p: Address of the current position in buf.
* @i: Starting position in buf.
* @len: Length of buf.
*
* Return: Void.
*/
void checkChain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->cmdBufType == CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }
    if (info->cmdBufType == CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }

    *p = j;
}

/**
* replaceCommandAlias - replaces an alias in the tokenized string
* @info: Structure containing relevant information
*
* Return: 1 If replaced, 0 otherwise
*/
int replaceCommandAlias(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return (0);
        free(info->argv[0]);
        p = _strchr(node->str, '=');
        if (!p)
            return (0);
        p = _strdup(p + 1);
        if (!p)
        {
            return (0);
        info->argv[0] = p;
    }

    return (1);
}

/**
* replaceEnvironmentVars - replaces the environment variables in the tokenized string
* @info: Structure containing relevant information.
*
* Return: 1 if replaced, 0 otherwise.
*/
int replaceEnvironmentVars(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
        {
            continue;
        }

        if (!strcmp(info->argv[i], "$?"))
        {
            replaceString(&(info->argv[i]), _strdup(convertNumber(info->status, 10, 0)));
            continue;
        }

        if (!strcmp(info->argv[i], "$$"))
        {
            replaceString(&(info->argv[i]), _strdup(convertNumber(getpid(), 10, 0)));
            continue;
        }

        node = findNodeStartsWith(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replaceString(&(info->argv[i]), _strdup(strchr(node->str, '=') + 1));
            continue;
        }

        replaceString(&info->argv[i], _strdup(""));
    }

    return (0);
}

/**
* replaceString - Replaces a string
* @old: Address of the old string
* @new: New string
*
* Return: 1 If replaced, 0 otherwise.
*/
int replaceString(char **old, char *new)
{
    free(*old);
    *old = new;
    return 1;
}
