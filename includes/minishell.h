/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:49:54 by storck            #+#    #+#             */
/*   Updated: 2026/02/11 14:06:07 by storck           ###   ########.fr       */
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

typedef struct s_node
{
	int				type;
	char			*value;
	char			*arg;
	struct s_node	*next;
	struct s_node	*previous;
}	t_node;

/* parsing/parsing.c */
char	*parsing(char *cmd);

/* parsing/parsing-nod.c */
t_node  *create_node(char *str, int len, t_node *list);
char	**gen_arg_list(char **arg_list, int count_total, char *str);

/* parsing/parisng-utils.c*/
int		increment_index(int i, char *str, char c);

#endif
