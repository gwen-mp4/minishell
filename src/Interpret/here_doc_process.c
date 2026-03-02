/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:58:17 by storck            #+#    #+#             */
/*   Updated: 2026/03/02 15:45:51 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

void    fill_doc(int fd, char *delim)
{
   char    *line;

   /* use simpler handlers while in heredoc */
   signal_heredoc();
   while (1)
   {
       g_sig = 0;
       line = readline("$>");
       if (!line)                /* EOF / ctrl-D */
           break ;
       if (g_sig == SIGINT)      /* ctrl-C pressed */
       {
           free(line);
           break ;
       }
       if (ft_strnstr(line, delim, ft_strlen(delim)))
       {
           free(line);
           break ;
       }
       ft_putendl_fd(line, fd);
       free(line);
   }
   setup_signal();
}

int file_heredoc_process(t_redir *heredoc, char *delim)
{
	int		fd;
    char    *doc_name;

    doc_name = get_heredoc_name();
    fd = open(doc_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fill_doc(fd, delim);
	free(heredoc->filename);
    heredoc->filename = doc_name;
	close(fd);
	fd = open(heredoc->filename, O_RDONLY, 0644);
	return (fd);
}
