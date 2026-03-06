/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:31:45 by storck            #+#    #+#             */
/*   Updated: 2026/03/06 14:01:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input_redirection(t_redir *redir)
{
	int	fd;

	if (redir->type == INPUT)
		fd = file_read_process(redir->filename);
	else if (redir->type == HEREDOC)
		fd = redir->fd;
	if (fd < 0)
		return (EXIT_FAILURE);
	redirect_fd(fd, STDIN_FILENO);
	return (fd);
}

int	output_redirection(t_redir *redir)
{
	int	fd;

	if (redir->type == OUTPUT)
		fd = file_write_process(redir->filename);
	else
		fd = file_append_process(redir->filename);
	if (fd < 0)
		return (EXIT_FAILURE);
	redirect_fd(fd, STDOUT_FILENO);
	return (fd);
}

void	set_fds(t_cmd *cmd)
{
	t_redir	*tmp;

	tmp = cmd->redirs;
	while (tmp)
	{
		if (tmp->type == INPUT || tmp->type == HEREDOC)
			input_redirection(tmp);
		if (tmp->type == OUTPUT || tmp->type == APPEND)
			output_redirection(tmp);
		tmp = tmp->next;
	}
}
