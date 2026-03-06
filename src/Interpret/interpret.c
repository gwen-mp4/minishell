/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:43:54 by storck            #+#    #+#             */
/*   Updated: 2026/03/06 13:00:54 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_cmd *cmd, char **env)
{
	char	*path;

	if (!cmd || !cmd->av || !cmd->av[0])
		return ;
	signal_child();
	set_fds(cmd);
	path = get_path(cmd->av[0], env);
	if (!path)
	{
		ft_putendl_fd("ERROR PATH", 2);
		ft_putstr_fd(cmd->av[0], 2);
		ft_putendl_fd(": command not found", 2);
		//total free minishell
		exit(127);
	}
	if (execve(path, cmd->av, env) == -1)
	{
		ft_putendl_fd("ERROR EXEC", 2);
		//total free minishell
		exit(1);
	}
}

void	find_way(t_cmd *cmd, char **env, t_data *data)
{
	if (is_builtin(cmd->av[0]))
	{
		exec_builtin(cmd, cmd->av, data);
		exit(0);
	}
	else
		exec_cmd(cmd, env);
}

void	do_pipe(t_cmd *cmd, char **env, t_data *data)
{
	pid_t	pid;
	int		p_fd[2];

	pipe_process(p_fd);
	pid = fork_process();
	if (!pid)
	{
		close(p_fd[0]);
		redirect_fd(p_fd[1], STDOUT_FILENO);
		find_way(cmd, env, data);
	}
	else
	{
		close(p_fd[1]);
		redirect_fd(p_fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	prepare_heredoc(t_cmd *cmd)
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
				fd = file_heredoc_process(r);
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

void	execution(t_cmd *cmd, t_data *data)
{
	pid_t	pid;
	int		save_in;
	int		save_out;

	if (!cmd->av[0])
		return ;
	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (prepare_heredoc(cmd) == EXIT_FAILURE)
		return ;
	while (data->pipe_count > 0)
	{
		do_pipe(cmd, data->env, data);
		data->pipe_count--;
		cmd = cmd->next;
	}
	pid = fork_process();
	if (!pid)
		find_way(cmd, data->env, data);
	else
		waitpid(pid, NULL, 0);
	redirect_fd(save_in, STDIN_FILENO);
	redirect_fd(save_out, STDOUT_FILENO);
}
