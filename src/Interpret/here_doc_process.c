/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:58:17 by storck            #+#    #+#             */
/*   Updated: 2026/03/04 15:59:46 by gwen             ###   ########.fr       */
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

int	fill_doc(int fd, char *delim)
{
	char	*line;

	if (!*delim || !delim)
		return (perror("heredoc delimiter missing"), close(fd), EXIT_FAILURE);
	while (1)
	{
		line = readline("heredoc>");
		if (!line || g_sig == SIGINT)
			return (free(line), close(fd), EXIT_FAILURE);
		if ((ft_strlen(line) == ft_strlen(delim))
			&& ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (close(fd), EXIT_SUCCESS);
}

int	heredoc_parent(pid_t pid, char *doc_name, int fd)
{
	int	status;

	if (pid < 0)
		return (unlink(doc_name), free(doc_name), -1);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signal();
	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
		return (unlink(doc_name), free(doc_name), -1);
	fd = open(doc_name, O_RDONLY);
	unlink(doc_name);
	free(doc_name);
	close(fd);
	return (fd);
}

int	file_heredoc_process(t_redir *heredoc)
{
	int		fd;
	char	*doc_name;
	pid_t	pid;

	g_sig = 0;
	doc_name = get_heredoc_name();
	if (!doc_name)
		return (-1);
	fd = open(doc_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (free(doc_name), -1);
	pid = fork();
	if (!pid)
	{
		signal_heredoc();
		if (fill_doc(fd, heredoc->filename) == EXIT_FAILURE)
			exit(1);
		exit(0);
	}
	close(fd);
	if (heredoc_parent(pid, doc_name, fd) < 0)
		return (-1);
	return (fd);
}
