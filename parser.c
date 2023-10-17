#include "shell.h"

/**
* is_cmd - determines if a file is an executable command
* @info: Information struct
* @path: Path to the file
*
* Returns: if it's an executable 1, otherwise 0
*/
int is_cmd(info_t *info, char *path)
{
struct stat file_stats;

(void)info;

if (!path || stat(path, &st))
return (0);

if (S_ISREG(file_stats.st_mode))
{
return (1);
}
return (0);
}

/**
* duplicate_substring - Duplicates characters in a substring
* @pathstr: The source string
* @start: The starting index
* @end: The ending index
*
* Returns: A pointer to a new buffer containing the duplicated substring
*/
char *duplicate_substring(char *pathstr, int start, int end)
{
static char buffer[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < end; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = '\0';
return (buf);
}

/**
* find_command_path - Finds the path to a command in the PATH string
* @info: Information struct
* @path_string: The PATH string
* @command: The cmd to find
*
* Returns: The full path of the cmd if found, or NULL
*/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!path_string)
return NULL;

if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_executable(info, command))
return (cmd);
}

while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = duplicate_substring(path_string, curr_pos, i);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
			if (is_executable(info, path))
				return path;
			if (!path_string[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return NULL;
}
