#include "shell.h"

/**
 * tokenizeString - splits a string into words using delimiters
 * @str: Input string
 * @delimiters: The delimiter string
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **tokenizeString(char *str, char *delimiters)
{
 	int i, j, k, m, numTokens = 0;
	char **tokens;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";

    for (i = 0; str[i] != '\0'; i++)
    {
        if (!isDelimiter(str[i], delimiters) && (isDelimiter(str[i + 1], delimiters) || !str[i + 1]))
            numTokens++;
    }

    if (numTokens == 0)
        return NULL;

    tokens = malloc((1 + numTokens) * sizeof(char *));
    if (!tokens)
        return NULL;

    for (i = 0, j = 0; j < numTokens; j++)
    {
        while (is_delim(str[i], delimiters))
            i++;

        k = 0;
        while (!is_delim(str[i + k], delimiters) && str[i + k])
            k++;

        tokens[j] = malloc((k + 1) * sizeof(character));
        if (!tokens[j])
        {
            for (k = 0; k < j; k++)
                free(tokens[k]);
            free(tokens);
            return NULL;
        }

        for (m = 0; m < k; m++)
            tokens[j][m] = str[i++];
        tokens[j][m] = 0;
    }

    tokens[j] = NULL;
    return tokens;
}

/**
 * tokenizeString2 - splits a string into words using a single delimiter
 * @str: the input string
 * @delimiter: the delimiter character
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **tokenizeString2(char *str, char delimiter)
{
    int i, j, k, m, numTokens = 0;
    char **tokens;

    if (str == NULL || str[0] == 0)
        return NULL;

    for (i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)

            numTokens++;
    }

    if (numTokens == 0)
        return NULL;

    tokens = malloc((1 + numTokens) * sizeof(char *));
    if (!tokens)
        return NULL;

    for (i = 0, j = 0; j < numTokens; j++)
    {
        while (str[i] == d && str[i] != d)
            i++;

        k = 0;
        while (str[i + k] != d && str[i + k] && str[i + k] != d)
            k++;

        tokens[j] = malloc((k + 1) * sizeof(char));
        if (!tokens[j])
        {
            for (k = 0; k < j; k++)
                free(tokens[k]);
            free(tokens);
            return NULL;
        }

        for (m = 0; m < k; m++)
            tokens[j][m] = str[i++];
        tokens[j][m] = 0;
    }

    tokens[j] = NULL;
    return tokens;
}
