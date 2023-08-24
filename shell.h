#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024

#define CMD_AND		2
#define CMD_CHAIN	3
#define CMD_NORM	0
#define CMD_OR		1

#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1

#define USE_STRTOK 0
#define USE_GETLINE 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - sngly lnked lst
 * @num: the number fld
 * @str: a strng
 * @next: points next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	char **environ;
	int env_changed;
	int status;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	list_t *env;
	list_t *history;
	list_t *alias;
	char *fname;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains string and function
 * @type: builtin command flag
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* toem_vars.c */
int replace_vars(info_t *);
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);

/* toem_lists.c */
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);

/* toem_lists1.c */
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
size_t list_len(const list_t *);
ssize_t get_node_index(list_t *, list_t *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int renumber_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);

/* toem_getenv.c */
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);

/* toem_shloop.c */
void find_cmd(info_t *);
void fork_cmd(info_t *);
int hsh(info_t *, char **);
int find_builtin(info_t *);

/* toem_parser.c */
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_string.c */
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
int _strlen(char *);
char *_strcat(char *, char *);

/* toem_errors.c */
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);

/* toem_string1.c */
void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);
char *_strdup(const char *);

/* toem_exits.c */
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);

/* toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);


/* toem_realloc.c */
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);
int is_delim(char, char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_errors1.c */
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _erratoi(char *);
void print_error(info_t *, char *);

/* toem_builtin.c */
int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);

/* toem_environ.c */
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char *_getenv(info_t *, const char *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
ssize_t get_input(info_t *);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

#endif
