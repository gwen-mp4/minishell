/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:49:54 by storck            #+#    #+#             */
/*   Updated: 2026/02/12 21:18:44 by marvin           ###   ########.fr       */
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

# include "../libft/libft/libft.h"

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
	struct s_token	*prev;
}	t_token;

typedef struct s_data
{
	char	*line;
	int		exit_code;
	t_token	*token;
	int		fd_in;
	int		fd_out;
	char	*infile;
	char	*outfile;
	char	**env;
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

/* parsing/parsing.c */
char	*parsing(char *cmd);

/* parsing/parsing-nod.c */
t_token  *create_token(t_type type, char *value);
void    add_back_token(t_token **list, t_token *new);
char	**gen_arg_list(char **arg_list, char *str);

/* parsing/parisng-utils.c*/
int		get_last_start(char *str, int i);
int		increment_i(int i, char *str, char c);
int		large_increment_i(int i, char *str);
int		increment_index(int i, char *str, char c);

/*lexing*/
char	*read_word(char *line, int *i);
t_token *lexer(char *input);

/*signal*/
void	sigint_handler(int sig);
void	setup_signal(void);

/* utils */
int		is_space(char c);
int		is_operator(char c);

/* init.c */
int		init_data(t_data *data, char **env);

/* error */
void	error_cleanup(t_token **tokens);

/* path_finding.c */
char	*get_path(char *cmd, char **envp);

/* path_split.c */
char	**path_split(const char *s, char c);

/* interpret.c */
void    interpret(t_token *list);

#endif
