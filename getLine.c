#include "shell.h"

/**
 * buffer_input - store chained commands in a buffer
 * @info: parameter structure
 * @buf: pointer to buffer
 * @len: pointer to length variable
 *
 * Return: number of bytes read
 */
ssize_t buffer_input(info_t *info, char **buf, size_t *len)
{
    ssize_t bytes_read = 0;
    size_t current_length = 0;

    if (!*len) {
        /* Clear the buffer if it's empty */
        free(*buf);
        *buf = NULL;
        signal(SIGINT, customSigintHandler);

        /* Read user input */
#if USE_GETLINE
        bytes_read = getline(buf, &current_length, stdin);
#else
        bytes_read = customGetline(info, buf, &current_length);
#endif

        if (bytes_read > 0) {
            if ((*buf)[bytes_read - 1] == '\n') {
                (*buf)[bytes_read - 1] = '\0'; /* Remove trailing newline */
                bytes_read--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
            /* Check for a command chain (e.g., if (_strchr(*buf, ';')) */
            {
                *len = bytes_read;
                info->cmd_buf = buf;
            }
        }
    }
    return bytes_read;
}

/**
 * To fetch_user_input - gets a line without the newline character
 * @info: parameter structure
 *
 * Return: number of bytes to read
 */
ssize_t fetch_user_input(info_t *info)
{
    static char *command_buf; /* Buffer for command chains separated by ';' */
    static size_t position_i, position_j, buffer_length;
    ssize_t bytesRead = 0;
    char **command_buffer_p = &(info->arg), *current_position;

    _putchar(BUF_FLUSH);
    bytesRead = buffer_input(info, &command_buf, &buffer_length);

    if (bytesRead == -1) /* End of file (EOF) */
        return -1;

    if (buffer_length) /* Commands are remaining in the chain buffer */
    {
        position_j = position_i; /* Initialize a new iterator to the current buffer position */
        current_position = command_buf + position_i; /* Get a pointer for return */

        check_chain(info, command_buf, &position_j, position_i, buffer_length);
        while (position_j < buffer_length) {
            if (is_chain(info, command_buf, &position_j))
                break;
            position_j++;
        }

        position_i = position_j + 1; /* Move past the nullified ';' character */
        if (position_i >= buffer_length) {
            position_i = buffer_length = 0; /* Reset the position and length if the end of the buffer is reached */
            info->cmd_buf_type = CMD_NORMAL;
        }

        *command_buffer_p = current_position; /* Pass back the pointer to the current command position */
        return _strlen(current_position); /* Return the length of the current command */
    }

    *command_buffer_p = command_buf; /* If it's not a chain, pass back the buffer from _getline() */
    return bytesRead; /* Return the length of the buffer from _getline() */
}

/**
 * read_buffer - read a buffer
 * @info: parameter structures
 * @buffer: buffer
 * @i: size
 *
 * Return:the bytesRead
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *i)
{
    ssize_t bytesRead = 0;

    if (*i)
        return 0;
    bytesRead = read(info->readfd, buffer, READ_BUF_SIZE);
    if (bytesRead >= 0)
        *i = bytesRead;
    return bytesRead;
}

/**
 * customGetline - get the next new line of input from STDIN
 * @info: parameter structures
 * @ptr: pointer to the buffer, preallocated or NULL
 * @length: sizes of the preallocated ptr buffer if not NULL
 *
 * Return: the bytesRead
 */
int customGetline(info_t *info, char **ptr, size_t *length)
{
    static char buffer[READ_BUF_SIZE];
    static size_t position_i, buffer_length;
    size_t k;
    ssize_t bytesRead = 0, bytesReadTotal = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        bytesReadTotal = *length;
    if (position_i == buffer_length)
        position_i = buffer_length = 0;

    bytesRead = read_buffer(info, buffer, &buffer_length);
    if (bytesRead == -1 || (bytesRead == 0 && buffer_length == 0))
        return -1;

    c = _strchr(buffer + position_i, '\n');
    k = c ? 1 + (unsigned int)(c - buffer) : buffer_length;
    new_p = _realloc(p, bytesReadTotal, bytesReadTotal ? bytesReadTotal + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return (p ? free(p), -1 : -1);

    if (bytesReadTotal)
        _strncat(new_p, buffer + position_i, k - position_i);
    else
        _strncpy(new_p, buffer + position_i, k - position_i + 1);

    bytesReadTotal += k - position_i;
    position_i = k;
    p = new_p;

    if (length)
        *length = bytesReadTotal;
    *ptr = p;
    return bytesReadTotal;
}

/**
 * customSigintHandler - block Ctrl-C
 * @sig_num: the only signal number
 *
 * Return: void
 */
void customSigintHandler(__attribute__((unused)) int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}

