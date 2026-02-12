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
	struct s_node	*next;
	struct s_node	*prev;
}	t_token;

typedef struct s_data
{
	char	*line;
	int		exit_code;
	t_token	*token;
}	t_data;

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

int		is_space(char c);
int		is_operator(char c);

#endif
