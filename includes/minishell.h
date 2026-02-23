/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:49:54 by storck            #+#    #+#             */
/*   Updated: 2026/02/20 14:58:18 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200112L
# define _XOPEN_SOURCE 600

# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
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

# include "../libft/libft.h"

# define HEREDOC_NAME "heredoc_"

typedef enum e_type
{
	WORD,
	PIPE,
	INPUT,	// <
	OUTPUT,	// >
	APPEND,	// >>
	HEREDOC	// <<
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*value; //pour word seulement
	struct s_token	*next;
	//struct s_token	*prev;
}	t_token;

typedef struct s_quote
{
	int	sq;
	int	dq;
}	t_quote;

typedef struct s_redir // for <, <<, >>, >
{
	t_type			type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd // av for WORD and redirs for operator except pipe
{
	char			**av;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

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
}	t_data;

//typedef struct s_pipe
//{
//	int		fd_in;
//	int		fd_out;
//	char	*infile;
//	char	*outfile;
//	char	**envp;
//	pid_t	last_pid;
//	t_cmd	*cmd;
//	int		size;
//}	t_pipe;

/* parsing*/
t_cmd	*parsing(t_token *token);
t_cmd	*new_cmd(void);
int		add_arg_to_cmd(char *word, t_cmd *cmd);
int		add_redir_to_cmd(t_type type, char *filename, t_cmd *cmd);

/*lexing*/
char	*read_word(char *line, int *i);
t_token *lexer(char *input);

/*signal*/
void	sigint_handler(int sig);
void	setup_signal(void);

/* utils */
int		is_space(char c);
int		is_operator(char c);
int		is_redir(t_type type);
void    clean_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmd);
void	free_data(t_data *data);
char	**get_args(t_token *token);

/* init.c */
int		init_data(t_data *data, char **env);

/* error */
int		error_cleanup_lexing(t_token *tokens, int status);
int		error_cleanup_parsing(t_cmd *cmds, const char *error);

/* path_finding.c */
char	*get_path(char *cmd, char **envp);

/* path_split.c */
char	**path_split(const char *s, char c);

/* interpret.c */
void    execution(t_cmd *cmd, t_data *data);

/* interpret_pipe.c */
int		pipe_exec_process(t_data *data, t_token *token);

/* pipe_process.c */
pid_t	fork_process(void);
void	pipe_process(int p_fd[2]);
void	redirect_fd(int old_fd, int new_fd);
int		file_read_process(char *infile);
int		file_write_process(char *outfile);

/* create_tokens.c */
void    add_back_token(t_token **list, t_token *new);
t_token	*create_token(t_type type, char *value);

/* here_doc_process.c */
int 	file_heredoc_process(t_redir *heredoc, char *delim);

/* append_file_process.c */
int		file_append_process(char *outfile);

#endif
