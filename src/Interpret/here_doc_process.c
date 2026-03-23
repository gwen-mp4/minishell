/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:58:17 by storck            #+#    #+#             */
/*   Updated: 2026/03/23 16:02:17 by gwen             ###   ########.fr       */
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
	if (!name)
		return (free(number), NULL);
	free(number);
	i++;
	return (name);
}

int	fill_doc(int fd, char *delim, char *doc_name, t_data *data)
{
	char	*line;

	if (!delim || !*delim)
		return (perror("heredoc delimiter missing"), close(fd), EXIT_FAILURE);
	while (1)
	{
		line = readline("heredoc>");
		if (!line || g_sig == SIGINT)
		{
			free_heredoc(line, fd, data, doc_name);
			signal(SIGINT, SIG_DFL);
			kill(getpid(), SIGINT);
			exit(1);
		}
		if ((ft_strlen(line) == ft_strlen(delim))
			&& ft_strcmp(line, delim) == 0)
			return (free_heredoc(line, fd, data, doc_name), EXIT_SUCCESS);
		ft_putendl_fd(line, fd);
		free(line);
	}
	rl_done = 0;
	return (close(fd), EXIT_SUCCESS);
}

int	heredoc_parent(pid_t pid, char *doc_name, t_data *data)
{
	int	status;
	int	fd;

	if (pid < 0)
		return (unlink(doc_name), free(doc_name), -1);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signal();
	rl_done = 0;
	rl_event_hook = NULL;
	g_sig = 0;
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		data->exit_code = 130;
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (unlink(doc_name), free(doc_name), -1);
	fd = open(doc_name, O_RDONLY);
	unlink(doc_name);
	free(doc_name);
	return (fd);
}

int	file_heredoc_process(t_redir *heredoc, t_data *data)
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
		close_all(data->fd_in, data->fd_out);
		if (fill_doc(fd, heredoc->filename, doc_name, data) == EXIT_FAILURE)
			exit(1);
		exit(0);
	}
	close(fd);
	return (heredoc_parent(pid, doc_name, data));
}

int	prepare_heredoc(t_cmd *cmd, t_data *data)
{
	t_cmd	*c;
	t_redir	*r;
	int		fd;

	c = cmd;
	while (c)
	{
		r = c->redirs;
		while (r)
		{
			if (r->type == HEREDOC)
			{
				fd = file_heredoc_process(r, data);
				if (fd < 0)
					return (EXIT_FAILURE);
				r->fd = fd;
			}
			r = r->next;
		}
		c = c->next;
	}
	return (EXIT_SUCCESS);
}
