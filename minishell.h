/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:06:23 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/10/26 13:56:44 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include "libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
#include <termios.h>

# define SIGF_INT
# define SIGF_QUIT
# define SIGF_REFRESH
# define SIGF_HDOC_INT

# ifndef HOST_NAME_MAX
#  define HOST_NAME_MAX _POSIX_HOST_NAME_MAX
# endif

extern volatile sig_atomic_t	g_sigflags;
typedef enum e_err
{
	ERR_NONE = 0,
	ERR_NOT_FOUND,
	ERR_IS_DIR,
	ERR_NO_PERM,
	ERR_EXECFMT
}								t_err;
typedef struct s_pipex
{
	int							pipe_fd[2];
	int							infile_fd;
	int							outfile_fd;
	char						**path_array;
	int							no_path_flag;
	int							last_status;
	int							status;
	int							heredoc_flag;
	t_err						err;
	pid_t						pid1;
	pid_t						pid2;
	pid_t						pid;
}								t_pipex;
typedef enum s_token_type
{
	TOK_UNDEF = 0,
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	AND
}							t_token_type;
typedef struct s_token_list
{
	t_token_type	type;
	char			*content;
	int				quoted;
	struct s_token_list *next;
}		t_token_list;

typedef enum e_node_type {
    NODE_CMD,      // 通常コマンド
    NODE_PIPE,     // |
    NODE_AND,      // &&
    NODE_OR,        // ||
	INIT
}   t_node_type;
typedef struct s_arg {
    char            *value;
    struct s_arg    *next;
} t_arg;

typedef struct s_redir {
    t_token_type     kind;
    char            *filename;
	char			*delim;
	int				 quoted;
    struct s_redir  *next;
} t_redir;
typedef struct s_ast
{
    t_node_type type;
    char        **argv;        // CMDなら実行内容
	t_arg		*arg_list;
	t_redir		*redirs;
    struct s_ast *left;        // 左のノード（左の式）
    struct s_ast *right;       // 右のノード（右の式）
}   t_ast;

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

void							ast_free_a(t_ast *n);
int 							get_exit_status(int stR);
int								exec_cmd_node(t_ast *node_list, char **envp, t_pipex *ps);
int								exec_cmd_pipe_node(t_ast *node_list, char **envp, t_pipex *ps,char *line);
int								execute_ast(t_ast *node_list,char **envp,t_pipex *ps,char *line);
void							init_history(void);
void							print_erro(char *err, char *msg);
char							**get_path_array(char **envp, t_pipex *px);
char							*find_command_path(char **path_array,
									char *cmd);
int								is_directory(const char *path);
int								execute_command(char *cmd_path, char **cmd_args,
									char **envp, t_pipex *ps);
char							**get_path_array(char **envp, t_pipex *px);
char							*resolve_command_path(char *cmd, t_pipex *ps);
void							execute(int argc, char **argv, char **envp,
									t_pipex *ps);
char							*ft_search_access(char **envp);
int								init_pipe(char *line, char **envp);
//void							on_signal(int s_num);
void							setup_signal(void);
void							set_echoctl(int enable);
void							on_signal_child(int s_num);
void							on_signal_parents(int s_num);
void							setup_signal_child(void);
void							setup_signal_parents(void);
//void							on_signal_child(int s_num);
t_token_list    				*create_token_list(char *line);
t_token_list					*create_new_token(char *line,size_t *index);
t_ast   						*parse_pipeline(t_token_list **cur);
void							free_splits(char **cmd_args);
int								apply_redirs(t_redir *list);
int								apply_one_redir(t_redir *node);
t_ast							*parse_command(t_token_list **cur);
char    						*ft_strjoin_g(char const *s1, char const *s2);
int								newline_or_not(char const *str);
char							*extract_line(char *stash);
char							*ft_strdup_g(const char *s1);
char							*update_stash(char *stash);
char							*get_next_line(int fd);
char							*process_backup(char **backup);
char							*read_to_backup(int fd, char *backup);


#endif