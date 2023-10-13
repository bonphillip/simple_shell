#include "shell.h"

/**
 * clear_info - Initializes the info_t struct to original default values.
 * @info: A pointer to the info_t struct to be initialized.
 */
void clear_info(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * set_info - Sets up the info_t struct with provided argment vector.
 * @info: A pointer to the info_t struct to be configured.
 * @av: The argument vector to initialize info_t.
 */
void set_info(info_t *info, char **av)
{
    int i = 0;

    info->fname = av[0];
    if (info->arg)
    {
        info->argv = strtow(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = _strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        replace_alias(info);
        replace_vars(info);
    }
}

/**
 * free_info - Frees allocated memory within the info_t struct.
 * @info: A pointer to the info_t struct to free memory from.
 * @all: If its true, frees all fields within the struct.
 */
void free_info(info_t *info, int all)
{
    ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;
    if (all)
    {
        if (!info->cmd_buf)
            free(info->arg);
        if (info->env)
            free_list(&(info->env));
        if (info->history)
            free_list(&(info->history));
        if (info->alias)
            free_list(&(info->alias));
        ffree(info->environ);
        info->environ = NULL;
        bfree((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        _putchar(BUF_FLUSH);
    }
}

