#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


#define WRITE_BUFFER_SIZE 1024
#define READ_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

#define CONVERT_TO_LOWERCASE 1
#define CONVERT_TO_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".simple_shell_history"
#define MAX_HISTORY_LINES 4096

extern char **environ;

typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
 * Struct passinfo - contains pseudo-arguments to pass into function, allowing
 * uniform prototypes for function pointer structs.
 *
 * @arg: A string generated from getline containing arguments.
 * @argv: An array of strings generated from arg.
 * @path: The string path for the current command.
 * @argc: The argument count.
 * @line_count: The error count.
 * @err_num: The error code for exit().
 * @linecount_flag: If on, count line of input.
 * @fname: Filename of the program.
 * @env: A linked list, local copy of environ.
 * @environ: A custom modified copy of environ from LL env.
 * @history: The history node.
 * @alias: The alias node.
 * @env_changed: Environ was changed if on.
 * @status: Last executed command return status.
 * @cmd_buf: Address of the pointer to cmd_buf that is used for chaining.
 * @cmd_buf_type: CMD_type (||, &&, ;).
 * @readfd: The file descriptor from which to read line input.
 * @histcount: Number count of the history line.
 */
typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int increment_line_count;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;
char **command_buffer;
int command_buffer_type;
int readfd;
int history_count;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;

/* toem_shloop.c */
int run_shell(info_t *, char **);
int identify_builtin(info_t *);
void locate_command(info_t *);
void spawn_command(info_t *);

/* toem_parser.c */
int validate_command(info_t *, char *);
char *duplicate_characters(char *, int, int);
char *find_executable_path(info_t *, char *, char *);

/* loophsh.c */
int main_loop(char **);

/* toem_errors.c */
void print_message(char *);
int print_character(int);
int write_character_to_fd(int c, int fd);
int write_string_to_fd(char *str, int fd);

/* toem_string.c */
int string_length(char *);
int string_compare(char *, char *);
char *start_of_substring(const char *, const char *);
char *concatenate_strings(char *, char *);

/* toem_string1.c */
char *copy_string(const char *);
char *duplicate_text(char *, char *);
void display_text(char *);
int print_character_to_console(char);

/* toem_exits.c */
char *copy_substring(char *, char *, int);
char *concatenate_substring(char *, char *, int);
char *find_character_in string(char *, char);

/* toem_tokenizer.c */
char **split_string(char *, char *);
char **split_string_with_delimiter(char *, char);

/* toem_realloc.c */
char *set_memory(char *, char, unsigned int);
void free_array_of_strings(char **);
void *reallocate_memory(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bulk_free(void **);

/* toem_atoi.c */
int is_interactive(info_t *);
int is_delimiter(char, char *);
int is_alphabetic(int);
int ascii_to_integer(char *);

/* toem_errors1.c */
int ascii_to_integer(char *);
void print_error_message(info_t *, char *);
int print_number(int, int);
char *convert_to_text(long int, int, int);
void remove_comments_in_text(char *);

/* toem_builtin.c */
int execute_exit(info_t *);
int execute_cd(info_t *);
int execute_help(info_t *);

/* toem_builtin1.c */
int execute_alias(info_t *);
int execute_history(info_t *);

/* toem_getline.c */
ssize_t get_user_input(info_t *);
int read_line(info_t *, char **, size_t *);
void signal_interrupt_handler(int);

/* toem_getinfo.c */
void reset_info(info_t *);
void set_info(info_t *, char **);
void release_info(info_t *, int);

/* toem_environ.c */
char *get_environment_variable(info_t *, const char *);
int run_environment(info_t *);
int set_environment_var(info_t *);
int remove_environment_var(info_t *);
int populate_environment_list(info_t *);

/* toem_getenv.c */
char **get_environ_variables(info_t *);
int unset_environment_variable(info_t *, char *);
int set_environment_variable(info_t *, char *, char *);

/* toem_history.c */
char *retrieve_history_file(info_t *info);
int write_history(info_t *info);
int load_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *insert_node(list_t **, const char *, int);
list_t *insert_node_end(list_t **, const char *, int);
size_t print_string_list(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void clear_list(list_t **);

/* toem_lists1.c */
size_t list_length(const list_t *);
char **linked_list_to_array_of_strings(list_t *);
size_t print_string_list(const list_t *);
list_t *find_node_starts_with(list_t *, char *, char);
ssize_t find_index_of_node(list_t *, list_t *);

/* toem_vars.c */
int is_cmd_chaining(info_t *, char *, size_t *);
void check_command_chaining(info_t *, char *, size_t *, size_t, size_t);
int resolve_alias(info_t *);
int process_variables(info_t *);
int update_string_value(char **, char *);

#endif
