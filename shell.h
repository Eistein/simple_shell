#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int f_builtin(info_t *);
void f_cmd(info_t *);
void fo_cmd(info_t *);

/* toem_parser.c */
int _executable(info_t *, char *);
char *duplicate_c(char *, int, int);
char *find_cmd_path(info_t *, char *, char *);

/* toem_errors.c */
void _error(char *);
int _error_char(char);
int _filedescriptor(char c, int fd);
int _print_to_fd(char *str, int fd);

/* toem_string.c */
int string_length(char *);
int string_compare(char *, char *);
char *string_starts_with(const char *, const char *);
char *string_concatenate((char *, char *);

/* toem_string1.c */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void print_string(char *);
int _putchar(char);

/* toem_exits.c */
char *strn_copy(char *, char *, int);
char *strn_concat(char *, char *, int);
char *str_character((char *, char);

/* toem_tokenizer.c */
char **s_string(char *, char *);
char **str_tow(char *, char);

/* toem_realloc.c */
char *set_memo(char *, char, unsigned int);
void free_str(char **);
void *re_alloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int f-pointer(void **);

/* toem_atoi.c */
int interactive(info_t *);
int check_delim((char, char *);
int check_alpha(int);
int _atoi(char *);

/* toem_errors1.c */
int string_to_i(char *);
void display_error(info_t *, char *);
int p_decimal(int, int);
char *convert_num(long int, int, int);
void rm_comment(char *);

/* toem_builtin.c */
int my_exit(info_t *);
int now_dr(info_t *);
int m_help(info_t *);

/* toem_builtin1.c */
int my_story(info_t *);
int m_alias((info_t *);
int pr_alias(list_t *);
int set_as(info_t *, char *);
int un_alias(info_t *, char *);


/*toem_getline.c */
ssize_t _getput(info_t *);
int tk_line(info_t *, char **, size_t *);
void sig_int_Hler(int);
ssize_t _inbuf(info_t *, char **, size_t *);
ssize_t _rdbuf(info_t *, char *, size_t *);

/* toem_getinfo.c */
void shell_info(info_t *);
void _info(info_t *, char **);
void rel_info(info_t *, int);

/* toem_environ.c */
char *ge_to_env(info_t *, const char *);
int m_env(info_t *);
int my_set(info_t *);
int un_set(info_t *);
int pop_env_list(info_t *);

/* toem_getenv.c */
char **get_env(info_t *);
int rm_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/* toem_history.c */
char *get_hi_file(info_t *info);
int write_hi(info_t *info);
int read_hi(info_t *info);
int build_hi_list(info_t *info, char *buf, int linecount);
int renum_history(info_t *info);

/* toem_lists.c */
list_t *add_to(list_t **, const char *, int);
list_t *add_to_end(list_t **, const char *, int);
size_t print_str_l(const list_t *);
int del_node_at(list_t **, unsigned int);
void free_l(list_t **);

/* toem_lists1.c */
size_t list_lght(const list_t *);
char **list_to_strs(list_t *);
size_t print_list(const list_t *);
list_t *node_st_with(list_t *, char *, char);
ssize_t get_index(list_t *, list_t *);

/* toem_vars.c */
int is_delm(info_t *, char *, size_t *);
void _testch(info_t *, char *, size_t *, size_t, size_t);
int _repalias(info_t *);
int _repvars(info_t *);
int rep_string(char **, char *);

#endif
