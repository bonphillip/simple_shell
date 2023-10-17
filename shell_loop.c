<<<<<<< HEAD
=======
#include "shell.h"

/**
 * Main shell loop. Handles user input and command execution.
 *
 * @info - The parameter & return info struct.
 * @av - The argument vector from main().
*
 * @return 0 on success, 1 on error, or error code.
 */
int hsh(info_t *info, char **av)
{
ssize_t read_result = 0;
int builtin_result = 0;

while (read_result != -1 && builtin_result != -2)
{
clear_shell_info(info);

if (is_interactive(info))
print_shell_prompt("$ ");

flush_output_buffer();
read_result = get_user_input(info);

if (read_result != -1)
    {
prepare_shell_info(info, av);
builtin_result = execute_builtin(info);

if (builtin_result == -1)
	execute_command(info);
    }
else if (is_interactive(info))
        newline();
	
	clean_up_shell_info(info, 0);
}

write_command_history(info);
clean_up_shell_info(info, 1);

if (!is_interactive(info) && info->status)
    exit_shell(info->status);

if (builtin_result == -2)
{
    if (info->err_num == -1)
        exit_shell(info->status);
    exit_shell(info->err_num);
}

return builtin_result;
}

/**
 * Finds a builtin command and executes it if found.
 *
 * @param info - The parameter & return info struct.
 * @Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
		info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
}
return (built_in_ret);
}

/**
 * Finds and executes a command in PATH.
 *
 * @param info - The parameter & return info struct.
 * @return void
 */
void find_cmd(info_t *info)
{
char *binary_path = NULL;
int i,k;

info->binary_path = info->argv[0];

if (info->linecount_flag == 1)
{
	info->line_count++;
	info->linecount_flag = 0;
}

for (i = 0, k = 0; info->arguments[arg_index]; arg_index++)
{
	if (!is_delimiter(info->arguments[arg_index], " \t\n"))
	{
        k++;
    }
}

if (!k)
{
	return;
}
>>>>>>> cb2013f0e8a6cd29b4115bca6def3a04e963ad2f

binary_path = find_binary_path(info, _get_environment_variable(info, "PATH="), info->argv[0]);

if (binary_path)
{
	info->binary_path = binary_path;
	execute_command_in_child(info);
}
else
{
    if ((is_interactive(info) || _get_environment_variable(info, "PATH=")
        || info->argv[0][0] == '/') && is_valid_command(info, info->argv[0]))
    {
        execute_command_in_child(info);
    }
    else if (*(info->arguments) != '\n')
    {
        info->status = 127;
        print_error_message(info, "not found\n");
    }
}

/**
 * Forks a child process to execute a command.
 *
 * @info - The parameter & return info struct.
 * @return void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
		free_info(info, 1);
		if (errno == EACCES)
			exit(126);
		exit(1);
	}
	/* TODO: PUT ERROR FUNCTION */
}
else
{
	wait(&(info->status));
	if (WIFEXITED(info->status))
	{
		info->status = WEXITSTATUS(info->status);
		if (info->status == 126)
			print_error(info, "Permission denied\n");
		}
	}
}
