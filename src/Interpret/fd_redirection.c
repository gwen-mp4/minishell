/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:31:45 by storck            #+#    #+#             */
/*   Updated: 2026/03/13 12:17:29 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input_redirection(t_redir *redir)
{
	int	fd;

	fd = 0;
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

void	find_way(t_cmd *cmd, t_data *data, pid_t *pids)
{
	char	**env;
	
	if (is_builtin(cmd->av[0]))
	{
		exec_builtin(cmd, cmd->av, data);
		if (ft_strcmp(cmd->av[0], "exit"))
		{
			free_data(data);
			free(pids);
		}
		exit(0);
	}
	env = regen_env(data->envlst);
	if (!env)
		return (perror("malloc: "));
	else
		exec_cmd(cmd, env);
	free_env(env, -1);
	free_data(data);
	free(pids);
	exit(data->exit_code);
}

void	set_fds(t_cmd *cmd)
{
	t_redir	*tmp;

	tmp = cmd->redirs;
	while (tmp)
	{
		if (tmp->type == INPUT || tmp->type == HEREDOC)
		{
			if (input_redirection(tmp) == EXIT_FAILURE)
				exit (1);
		}
		if (tmp->type == OUTPUT || tmp->type == APPEND)
		{
			if (output_redirection(tmp) == EXIT_FAILURE)
				exit (1);
		}
		tmp = tmp->next;
	}
}
