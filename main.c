#include "shell.h"

/**
 * main - Entry point
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: on success 0, on error 1
 */
int main(int argc, char **argv)
{
    info_t info[] = { INFO_INIT };
    int fd = 2;

    asm ( "mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd) );

    if (argc == 2)
{
    int file_desc = open(argv[1], O_RDONLY);
    if (file_desc == -1)
    {
        if (errno == EACCES)
            exit(126);
        if (errno == ENOENT)
        {
            _eputs(argv[0]);
            _eputs(": 0: Can't open ");
            _eputs(argv[1]);
            _eputchar('\n');
            _eputchar(BUF_FLUSH);
            exit(127);
        }
        return (EXIT_FAILURE);
    }
    info->readfd = file_desc;
}
populate_env_list(info);
read_history(info);
hsh(info, argv);
return (EXIT_SUCCESS);
