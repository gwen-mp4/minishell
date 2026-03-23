/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:43:54 by storck            #+#    #+#             */
/*   Updated: 2026/03/23 17:44:27 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		else if (WTERMSIG(status) == SIGQUIT)
			return (131);
	}
	return (1);
}

static void	wait_all(pid_t	*pids, int total, t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < total)
	{
		waitpid(pids[i], &status, 0);
		if (i == total - 1)
		{
			data->exit_code = get_exit_code(status);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				ft_putstr_fd("\n", STDERR_FILENO);
			else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		}
		i++;
	}
}

static pid_t	*run_pipes(t_cmd **cmd, t_data *data, int total)
{
	pid_t	*pids;
	int		i;

	pids = malloc(sizeof(pid_t) * total);
	if (!pids)
		return (NULL);
	i = 0;
	while (data->pipe_count > 0)
	{
		do_pipe(*cmd, data, pids, i++);
		data->pipe_count--;
		*cmd = (*cmd)->next;
	}
	return (pids);
}

static void	exec_last(t_cmd *cmd, t_data *data, int save_in, int save_out)
{
	pid_t	*pids;
	int		total;

	total = data->pipe_count + 1;
	pids = run_pipes(&cmd, data, total);
	if (!pids)
	{
		close(save_in);
		close(save_out);
		return ;
	}
	pids[total - 1] = fork_process();
	if (!pids[total - 1])
		find_way(cmd, data, pids);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	redirect_fd(save_in, STDIN_FILENO);
	redirect_fd(save_out, STDOUT_FILENO);
	wait_all(pids, total, data);
	setup_signal();
	free(pids);
}

void	execution(t_cmd *cmd, t_data *data)
{
	if (!cmd)
		return ;
	data->fd_in = dup_process(STDIN_FILENO, -1);
	data->fd_out = dup_process(STDOUT_FILENO, data->fd_in);
	if ((!cmd->av || !cmd->av[0]) && cmd->redirs != NULL && !cmd->next)
	{
		check_only_fds(cmd, data);
		reset_fds(data->fd_in, data->fd_out);
	}
	if ((prepare_heredoc(cmd, data) == EXIT_FAILURE || !cmd->av || !cmd->av[0])
		&& !cmd->next)
		return (close_all(data->fd_in, data->fd_out));
	if (data->pipe_count == 0 && is_builtin(cmd->av[0]))
	{
		if (!ft_strcmp(cmd->av[0], "echo") || !ft_strcmp(cmd->av[0], "pwd"))
		{
			if (set_fds(cmd) == EXIT_FAILURE)
				return (set_exit_1(data));
		}
		exec_builtin(cmd, cmd->av, data);
		return (reset_fds(data->fd_in, data->fd_out));
	}
	exec_last(cmd, data, data->fd_in, data->fd_out);
}
