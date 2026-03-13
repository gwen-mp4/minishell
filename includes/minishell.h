/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:49:54 by storck            #+#    #+#             */
/*   Updated: 2026/03/13 12:39:18 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200112L
# define _XOPEN_SOURCE 600

# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <term.h>
# include <unistd.h>
# include <errno.h>

# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define HEREDOC_NAME "heredoc_"

extern volatile sig_atomic_t	g_sig;

typedef enum e_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_type;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE,
	DOUBLE
}	t_quote_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	t_type			type;
	t_quote_type	quote_type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_quote
{
	int				sq;
	int				dq;
	t_quote_type	type;
}	t_quote;

typedef struct s_redir
{
	t_type			type;
	char			*filename;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**av;
	t_quote_type	*quote_type;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_var
{
	char			*name;
	char			*content;
	struct s_var	*next;
}	t_var;

typedef struct s_data
{
	char	*line;
	int		exit_code;
	int		fd_in;
	int		fd_out;
	char	*infile;
	char	*outfile;
	char	**env;
	pid_t	last_pid;
	int		pipe_count;
	t_token	*token;
	t_quote	*quote;
	t_cmd	*cmd;
	t_list	*envlst;
	t_list	*trash;
	t_var	*vars;
}	t_data;

/* parsing*/
t_cmd	*parsing(t_token *token, t_data *data);
t_cmd	*new_cmd(void);
int		add_arg_to_cmd(char *word, t_quote_type quote, t_cmd *cmd);
int		add_redir_to_cmd(t_type type, char *filename, t_cmd *cmd);

/*lexing*/
char	*read_word(char *line, int *i, t_quote_type *type);
t_token	*lexer(char *input);

/* utils */
int		is_space(char c);
int		is_operator(char c);
int		is_redir(t_type type);
int		is_number(char *num);
void	clean_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmd);
void	free_data(t_data *data);
char	**get_args(t_token *token);
void	signal_heredoc(void);
void	setup_signal(void);
void	signal_child(void);

/* init.c */
int		init_data(t_data *data, int ac, char **av, char **env);

/* error */
int		error_cleanup_lexing(t_token *tokens, int status);
int		error_cleanup_parsing(t_cmd *cmds, const char *error, t_token *token);
void	error_command_not_found(const char *cmd);
void	error_permission_denied(const char *file);
void	error_no_such_file(const char *file);

/* error2.c */
void	error_too_many_arguments(const char *cmd);

/* path_finding.c */
char	*get_path(char *cmd, char **envp);

/* path_split.c */
char	**path_split(const char *s, char c);

/* interpret.c */
void	exec_cmd(t_cmd *cmd, char **env, t_data *data);
void	execution(t_cmd *cmd, t_data *data);

/* pipe_process.c */
void	redirect_fd(int old_fd, int new_fd);
int		file_read_process(char *infile);
int		file_write_process(char *outfile);

/* utils_process.c*/
pid_t	fork_process(void);
void	pipe_process(int p_fd[2]);
int		dup_process(int fd, int save_in);

/* create_tokens.c */
void	add_back_token(t_token **list, t_token *new);
t_token	*create_token(t_type type, char *value, t_quote_type quote);

/* here_doc_process.c */
int		file_heredoc_process(t_redir *heredoc);
int		prepare_heredoc(t_cmd *cmd);

/* append_file_process.c */
int		file_append_process(char *outfile);

/* fd_redirection.c */
int		input_redirection(t_redir *redir);
int		output_redirection(t_redir *redir);
void	find_way(t_cmd *cmd, t_data *data, pid_t *pids);
void	set_fds(t_cmd *cmd);

/* exec_builtin */
int		is_builtin(char *str);
void	exec_builtin(t_cmd *cmd, char **args, t_data *data);

/* builtin_utils */
int		check_key(char *str);

/* builtins */
int		exec_cd(t_data *data, char **args);
int		exec_echo(char **arg, t_quote_type *quote, t_data *data);
int		exec_env(t_list *env);
void	exec_exit(char **args, t_data *data);
bool	export_ex(char *str, t_list **env);
int		exec_export(char **args, t_list **env);
int		exec_pwd(char **arg);
bool	unset(char *str, t_list **env);
int		exec_unset(char **args, t_list **env);

/* env_utils */
void	free_env(char **env, int end);
char	**regen_env(t_list *envlst);
int		free_list(t_list **list);
char	*extract_value(char *str);
char	*extract_key(char *str);
int		init_envlst(t_data *data, char **env);
int		list_new_elem_str(t_list **new, char *elem);
bool	env_entry_exists(char *key, t_data *data);
t_env	*envlst_new(char *key, char *value);
void	envlst_back(t_env *new, t_data *data);
int		append(t_list **list, char *elem);
void	update_envlst(char *key, char *value, t_data *data, bool create);
int		len_list(t_list *lst);
void	sort_array(char **arr, int len);
char	**lst_to_arr(t_list *env);
bool	null_env(t_data *data);

/* variable.c */
void	filter_var(t_cmd *cmd, t_data *data);

/* var_utils.c */
char	*exit_code_to_str(int code, char *rest);
void	replace_var(char **var, t_data *data);
char	*get_var_content(char *var, t_data *data);
void	add_var(t_data *data, char *name, char *content);

#endif
